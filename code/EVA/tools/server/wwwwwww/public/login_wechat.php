<?php

	include_once('public_func.php');
	include_once('hostconfig.php');
	
	error_reporting(E_ERROR | E_PARSE);
	set_error_handler('err_callback');

	// For error handling, buffer all output
	ob_start('ob_callback_r2login');

	include_once('config.php');
	include_once('login_translations.php');
	include_once('../tools/nel_message.php');
	include_once('login_service_itf.php');
	
	if (!isset($_POST['cmd']))
	{
		die (errorMsgBlock(3002));
	}
	if (!isset($_POST['time']))
	{
		die (errorMsgBlock(3002));
	}
	
	$json_arr = array();
	
	// 检查客户端版本
	$client_version	 = $_POST['ver'];
	if ( $client_version < $ClientMinVersion )
	{
		$json_arr['ver'] = $DownLoadUrl;
		$json_text = json_encode($json_arr, JSON_UNESCAPED_UNICODE);
		echo $json_text;
		die();
	}
	
	switch($_POST['cmd'])
	{
	case 'login':

		$username   	= $_POST['usr'];
		$client_ip  	= getIP();
		$is_login   	= FALSE;
		$is_wx_refresh	= FALSE;
		
		$actIdDb = mysqli_connect($DBHost, $DBUserName, $DBPassword) or die(errorMsgBlock(3004, 'Login', $DBHost, $DBUserName));
		mysqli_select_db ($actIdDb, $DBName) or die(errorMsgBlock(3005, 'Login', $DBName, $DBHost, $DBUserName));
		$login_usr = mysqli_real_escape_string($actIdDb, $username);
			
		$deviceid            = $_POST['deviceid'];
		$APP_NAME            = mysqli_real_escape_string($actIdDb, $_POST['app_name']);
		$login_type          = $_POST['login_type'];
		$login_token         = $_POST['login_token'];
		$login_time          = $_POST['time'];
		$login_data_sig      = $_POST['sig'];

		is_numeric( $login_type ) or die();

		$login_base64_rsa    = $SIG_KEY[$APP_NAME];
		$login_sig_data      = $login_usr . $deviceid . $APP_NAME . $login_type . $login_time;
		$public_key = "-----BEGIN PUBLIC KEY-----" . PHP_EOL . chunk_split($login_base64_rsa, 64, PHP_EOL) . "-----END PUBLIC KEY-----";
		$public_key_handle = openssl_get_publickey($public_key);
		$result = openssl_verify( $login_sig_data, base64_decode($login_data_sig), $public_key_handle, OPENSSL_ALGO_SHA1 );
		if( $result === 1 )
		{
			$wx_dejson = '{}';

			switch($login_type)
			{
			case 0:
				$is_login = TRUE;
				break;
			case 4:		/// 微信登录

				if ( !isset($_POST['openid']) )
				{
					mysqli_close( $actIdDb );
					return;
				}

				$openid       = $_POST['openid'];				
				$login_usr = $openid;
				mysqli_query($actIdDb, "SET NAMES utf8mb4");
				$query = "SELECT f_account_id,f_freeze_to FROM t_account_id WHERE f_name='$login_usr' AND f_game_type='$APP_NAME' AND f_type='$login_type'";
				$result = mysqli_query ($actIdDb, $query) or die(errorMsgBlock(3006, $query, 'Login', $DBName, $DBHost, $DBUserName, mysqli_error($actIdDb)));

				if (mysqli_num_rows($result) == 1)
				{
					$is_login = TRUE;
				}

				$RequestURL   = "https://api.weixin.qq.com/sns/userinfo?access_token=$login_token&openid=$openid&lang=zh_CN";
				$wx_dejson    = RequestJson($RequestURL);
				if( !isset($wx_dejson['errcode']) )
				{
					$is_login = TRUE;
					$is_wx_refresh = TRUE;
				}

				break;
			default:
				mysqli_close( $actIdDb );
				die();
			}

			///  登录成功  -  获取userid
			if( $is_login )
			{
				///  get user info
				mysqli_query($actIdDb, "SET NAMES utf8mb4");
				$query = "SELECT f_account_id,f_freeze_to FROM t_account_id WHERE f_name='$login_usr' AND f_game_type='$APP_NAME' AND f_type='$login_type'";
				$result = mysqli_query ($actIdDb, $query) or die(errorMsgBlock(3007, $query, 'Login', $DBName, $DBHost, $DBUserName, mysqli_error($actIdDb)));
				$user_id = 0;
				
				if (mysqli_num_rows($result) == 0)
				{
					// no user id record, build one
					$query = "INSERT INTO t_account_id (f_name,f_type,f_game_type) VALUES ('$login_usr','$login_type','$APP_NAME')";
					mysqli_query ($actIdDb, $query) or die(errorMsgBlock(3008, $query, 'Login', $DBName, $DBHost, $DBUserName, mysqli_error($actIdDb)));
					
					// re get
					$query = "SELECT f_account_id,f_freeze_to FROM t_account_id WHERE f_name='$login_usr' AND f_game_type='$APP_NAME' AND f_type='$login_type'";
					$result = mysqli_query ($actIdDb, $query) or die(errorMsgBlock(3009, $query, 'Login', $DBName, $DBHost, $DBUserName, mysqli_error($actIdDb)));
				}
				
				if (mysqli_num_rows($result) == 1)
				{
					$row = mysqli_fetch_array($result);
					$user_id = $row["f_account_id"];
					$freeze_to = $row["f_freeze_to"];
					
					if( time() >= $freeze_to )
					{
						/// 如果是微信登录
						switch($login_type)
						{
							case 4:		/// 微信登录
							
							if ( $is_wx_refresh )
							{
								$query = "SELECT f_account_id , f_sex , f_nickname , f_headimgurl FROM t_account_info_wx WHERE f_account_id=$user_id";
								$result = mysqli_query ($actIdDb, $query) or die(errorMsgBlock(3010, $query, 'LoginWX', $DBName, $DBHost, $DBUserName, mysqli_error($actIdDb)));
								$nickname = $wx_dejson['nickname'];
								$sex      = $wx_dejson['sex'];
								$headimgurl = $wx_dejson['headimgurl'];
							
								/// 保存微信账号数据
								if (mysqli_num_rows($result) == 0)
								{
									$openid   = $wx_dejson['openid'];
									$province = $wx_dejson['province'];
									$city     = $wx_dejson['city'];
									$country  = $wx_dejson['country'];
									$unionid  = $wx_dejson['unionid'];

									$query = "INSERT INTO t_account_info_wx (f_account_id,f_game_type,f_openid,f_nickname,f_unionid,f_sex,f_province,f_city,f_country,f_headimgurl) VALUES ('$user_id','$APP_NAME','$openid','$nickname','$unionid','$sex','$province','$city','$country','$headimgurl')";
									mysqli_query ($actIdDb, $query) or die(errorMsgBlock(3011, $query, 'LoginWX', $DBName, $DBHost, $DBUserName, mysqli_error($actIdDb)));
								}
								else
								{
									$row = mysqli_fetch_array($result);
									if ( $sex != $row["f_sex"] || $nickname != $row["f_nickname"] || $headimgurl != $row["f_headimgurl"] )
									{
										$query = "UPDATE t_account_info_wx SET f_sex = '$sex' , f_nickname = '$nickname' , f_headimgurl = '$headimgurl' where f_account_id = '$user_id'";
										mysqli_query ($actIdDb, $query) or die(errorMsgBlock(3012, $query, 'LoginWX', $DBName, $DBHost, $DBUserName, mysqli_error($actIdDb)));
									}
								}
							}

							break;
						}
												
						/// 登录游戏
						$login = new CLoginServiceWeb;
						$res = "";
						$login->connect($LoginModuleIP, $LoginModulePort, $res);
						$token = randomkeys(32);
						$login->login($user_id, $token, $login_usr, $login_type, $APP_NAME);
						if (!$login->waitCallback())
						{
							$json_arr['faile'] = 1;
							$json_text = json_encode($json_arr, JSON_UNESCAPED_UNICODE);
							echo $json_text;
							die();
						}
						$query     = "SELECT f_area_code FROM t_area WHERE f_end_host >= INET_ATON('$client_ip') AND f_start_host <= INET_ATON('$client_ip')";
						$result    = mysqli_query ($actIdDb, $query) or die(errorMsgBlock(3013, $query, 'LoginWX', $DBName, $DBHost, $DBUserName, mysqli_error($actIdDb)));
						if ( mysqli_num_rows($result) == 1 )
						{
							$row = mysqli_fetch_array($result);
							$json_arr['areacode'] = $row['f_area_code'];																				
						}
						mysqli_close( $actIdDb );
						$area_len = count($HOST_['default']);
						$rand_idx = mt_rand(0, $area_len - 1);
						$host_fes = $HOST_['default'][$rand_idx];
						$json_arr['token'] = $token;
						$json_arr['host']  = $host_fes;	
						$json_text = json_encode($json_arr, JSON_UNESCAPED_UNICODE);
						echo $json_text;
					}
					else
					{
						mysqli_close( $actIdDb );
						$restime = $freeze_to-time();
						$json_arr['fz2'] = $restime;
						$json_text = json_encode($json_arr, JSON_UNESCAPED_UNICODE);
						echo $json_text;
					}
				}
			}
			else
			{
				mysqli_close( $actIdDb );
				$json_arr['faile'] = 2;
				$json_text = json_encode($json_arr, JSON_UNESCAPED_UNICODE);
				echo $json_text;
			}
		}
	}

	// no more to do (other global statement are old garbage)
	die();

// ----------------------------------------------------------------------------------------
// Functions
// ----------------------------------------------------------------------------------------



?>
