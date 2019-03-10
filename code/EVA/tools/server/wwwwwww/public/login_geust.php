<?php
	include_once('public_func.php');
	include_once('hostconfig.php');
	
	error_reporting(E_ERROR | E_PARSE);
	set_error_handler('err_callback');

	// For error handling, buffer all output
	ob_start('ob_callback_r2login');

	include_once('config.php');
	include_once('login_translations.php');
	
	$device_name  = $_POST['device_name'];
	$device_id    = $_POST['device_id'];
	$curr_time	  = $_POST['time'];
	$sig		  = $_POST['sig'];
	$login_type   = 1;

	$json_array = array();		
	$wait_sig = $curr_time . $device_id . 'FSDF4F4AKE44343';
	$wait_sig  = md5($wait_sig);
	if ( $wait_sig != $sig )
	{
		$json_array['faile'] = 100;
		$json_text = json_encode($json_array, JSON_UNESCAPED_UNICODE);
		echo $json_text;
		die();
	}
	
	$db_connect = mysqli_connect( $db_account_host , $db_account_username , $db_account_password ) or die( errorMsgBlock(3004 , 'guest_login' , $db_account_host , $db_account_username ) );
	mysqli_select_db( $db_connect , $db_account_name ) or die( errorMsgBlock( 3005 , 'guest_login' , $db_account_name, $db_account_host, $db_account_username ));
	$device_id = mysqli_real_escape_string( $db_connect , $device_id );
	
	mysqli_query( $db_connect, "SET NAMES utf8mb4" );
	$query = "SELECT f_account_id,f_freeze_time FROM t_account_info WHERE f_name='$device_id' AND f_type='$login_type'";
	$result = mysqli_query ($db_connect, $query) or die(errorMsgBlock(3007, $query, 'guest_login', $db_account_name, $db_account_host, $db_account_username, mysqli_error($db_connect)));
	if ( mysqli_num_rows($result) == 0 )
	{
		// insert;
		$query = "INSERT INTO t_account_info (f_name,f_type) VALUES ('$device_id','$login_type')";
		mysqli_query ($db_connect, $query) or die(errorMsgBlock(3008, $query, 'guest_login', $db_account_name, $db_account_host, $db_account_username, mysqli_error($db_connect)));
		// select;
		$query = "SELECT f_account_id,f_freeze_time FROM t_account_info WHERE f_name='$device_id' AND f_type='$login_type'";
		$result = mysqli_query ($db_connect, $query) or die(errorMsgBlock(3007, $query, 'guest_login', $db_account_name, $db_account_host, $db_account_username, mysqli_error($db_connect)));
	}
	if ( mysqli_num_rows( $result ) != 1 )
	{
		$json_array['faile'] = 2;
		$json_text = json_encode($json_array, JSON_UNESCAPED_UNICODE);
		echo $json_text;
		die();
	}
	
	$row_data 	= mysqli_fetch_array($result);
	$account_id = $row_data['f_account_id'];
	$freeze_time= $row_data['f_freeze_time'];
		
	// freeze time;
	if ( time() < $freeze_time )
	{
		mysqli_close( $db_connect );
		$json_array['freeze_time'] = $freeze_time;
		$json_text = json_encode($json_array, JSON_UNESCAPED_UNICODE);
		echo $json_text;
		die();
	}
		
	// select area code;
	$client_host = getIP();
	$query       = "SELECT f_area_code FROM t_area WHERE f_end_host >= INET_ATON('$client_host') AND f_start_host <= INET_ATON('$client_host')";
	$result      = mysqli_query ($db_connect, $query) or die(errorMsgBlock(3013, $query, 'guest_login', $db_account_name, $db_account_host, $db_account_username, mysqli_error($db_connect)));
	if ( mysqli_num_rows($result) == 1 )
	{
		$row = mysqli_fetch_array($result);
		$json_array['areacode'] = $row['f_area_code'];																				
	}
	mysqli_close( $db_connect );
	$client_token = $account_id . $client_host . $AuthSecret;
	$client_token = strtoupper( md5($client_token) );
	
	$area_len = count($HOST_['default']);
	$rand_idx = mt_rand(0, $area_len - 1);
	$host_url = $HOST_['default'][$rand_idx];
	$json_array['fes_host']		= $host_url;
	$json_array['account_id']	= $account_id;
	$json_array['client_host']	= $client_host;	
	$json_array['client_token']	= $client_token;	
	$json_text = json_encode($json_array, JSON_UNESCAPED_UNICODE);
	echo $json_text;				
	die();
?>