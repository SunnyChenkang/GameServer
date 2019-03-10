<?php




class AopClient {

	
	//应用ID

	public $appId;
	

	//私钥文件路径

	public $rsaPrivateKeyFilePath;


	//私钥值
	public $rsaPrivateKey;


	//网关

	public $gatewayUrl = "https://openapi.alipaydev.com/gateway.do";

	//返回数据格式

	public $format = "json";

	//api版本
	public $apiVersion = "1.0";


	// 表单提交字符集编码
	
	public $postCharset = "UTF-8";


	//使用文件读取文件格式，请只传递该值
	
	public $alipayPublicKey = null;


	//使用读取字符串格式，请只传递该值

	public $alipayrsaPublicKey;



	public $debugInfo = false;


	private $fileCharset = "UTF-8";


	private $RESPONSE_SUFFIX = "_response";


	private $ERROR_RESPONSE = "error_response";


	private $SIGN_NODE_NAME = "sign";



	//加密XML节点名称

	private $ENCRYPT_XML_NODE_NAME = "response_encrypted";


	private $needEncrypt = false;



	//签名类型

	public $signType = "RSA";


	
	//加密密钥和类型

	public $encryptKey;


	public $encryptType = "AES";


	protected $alipaySdkVersion = "alipay-sdk-php-20161101";



	public function generateSign($params, $signType = "RSA") {

		return $this->sign($this->getSignContent($params), $signType);

	}



	public function getSignContent($params) {

		ksort($params);


		$stringToBeSigned = "";

		$i = 0;

		foreach ($params as $k => $v) {

			if (false === $this->checkEmpty($v) && "@" != substr($v, 0, 1)) {


				// 转换成目标字符集

				$v = $this->characet($v, $this->postCharset);


				if ($i == 0) {

					$stringToBeSigned .= "$k" . "=" . "$v";

				} else {

					$stringToBeSigned .= "&" . "$k" . "=" . "$v";

				}

				$i++;

			}

		}


		unset ($k, $v);

		return $stringToBeSigned;

	}

	protected function sign($data, $signType = "RSA") {

		if($this->checkEmpty($this->rsaPrivateKeyFilePath)){

			$priKey=$this->rsaPrivateKey;

			$res = "-----BEGIN RSA PRIVATE KEY-----\n" .

				wordwrap($priKey, 64, "\n", true) .

				"\n-----END RSA PRIVATE KEY-----";

		}else {

			$priKey = file_get_contents($this->rsaPrivateKeyFilePath);

			$res = openssl_get_privatekey($priKey);

		}


		($res) or die('您使用的私钥格式错误，请检查RSA私钥配置');
 

		if ("RSA2" == $signType) {

			openssl_sign($data, $sign, $res, OPENSSL_ALGO_SHA256);

		} else {

			openssl_sign($data, $sign, $res);

		}


		if(!$this->checkEmpty($this->rsaPrivateKeyFilePath)){

			openssl_free_key($res);

		}

		$sign = base64_encode($sign);

		return $sign;

	}

   

    /**

     * 生成用于调用收银台SDK的字符串

     * @param $request SDK接口的请求参数对象

     * @return string
 
    * @author guofa.tgf

     */

	public function sdkExecute($request) {

		
$this->setupCharsets($request);


		$params['app_id'] = $this->appId;

		$params['method'] = $request->getApiMethodName();

		$params['format'] = $this->format;
 
		$params['sign_type'] = $this->signType;

		$params['timestamp'] = date("Y-m-d H:i:s");

		$params['alipay_sdk'] = $this->alipaySdkVersion;

		$params['charset'] = $this->postCharset;


		$version = $request->getApiVersion();

		$params['version'] = $this->checkEmpty($version) ? $this->apiVersion : $version;


		if ($notify_url = $request->getNotifyUrl()) {

			$params['notify_url'] = $notify_url;

		}


		$dict = $request->getApiParas();

		$params['biz_content'] = $dict['biz_content'];


		ksort($params);


		$params['sign'] = $this->generateSign($params, $this->signType);


		foreach ($params as &$value) {

			$value = $this->characet($value, $params['charset']);

		}

		
return http_build_query($params);

	}



	/**

	 * 转换字符集编码

	 * @param $data

	 * @param $targetCharset

	 * @return string

	 */

	function characet($data, $targetCharset) {

		
if (!empty($data)) {

			$fileType = $this->fileCharset;

			if (strcasecmp($fileType, $targetCharset) != 0) {

				$data = mb_convert_encoding($data, $targetCharset, $fileType);

				//				$data = iconv($fileType, $targetCharset.'//IGNORE', $data);

			}

		}



		return $data;

	}



	/**

	 * 校验$value是否非空

	 *  if not set ,return true;

	 *    if is null , return true;

	 **/

	protected function checkEmpty($value) {

		if (!isset($value))

			return true;

		if ($value === null)

			return true;

		if (trim($value) === "")

			return true;


		return false;

	}



	/** rsaCheckV1 & rsaCheckV2

	 *  验证签名

	 *  在使用本方法前，必须初始化AopClient且传入公钥参数。

	 *  公钥是否是读取字符串还是读取文件，是根据初始化传入的值判断的。

	 **/

	public function rsaCheckV1($params, $rsaPublicKeyFilePath,$signType='RSA') {

		$sign = $params['sign'];

		$params['sign_type'] = null;

		$params['sign'] = null;

		return $this->verify($this->getSignContent($params), $sign, $rsaPublicKeyFilePath,$signType);

	}


	public function rsaCheckV2($params, $rsaPublicKeyFilePath, $signType='RSA') {

		$sign = $params['sign'];

		$params['sign'] = null;

		return $this->verify($this->getSignContent($params), $sign, $rsaPublicKeyFilePath, $signType);

	}



	function verify($data, $sign, $rsaPublicKeyFilePath, $signType = 'RSA2') {


		$res = "-----BEGIN PUBLIC KEY-----\n" .

			wordwrap($rsaPublicKeyFilePath, 64, "\n", true) .

			"\n-----END PUBLIC KEY-----";


		($res) or die('支付宝RSA公钥错误。请检查公钥文件格式是否正确');
  

		//调用openssl内置方法验签，返回bool值


		if ("RSA2" == $signType) {

			$result = (bool)openssl_verify($data, base64_decode($sign), $res, OPENSSL_ALGO_SHA256);

		} else {

			$result = (bool)openssl_verify($data, base64_decode($sign), $res);

		}


		if(!$this->checkEmpty($this->alipayPublicKey)) {

			//释放资源

			openssl_free_key($res);

		}


		return $result;

	}



	private function setupCharsets($request) {

		if ($this->checkEmpty($this->postCharset)) {

			$this->postCharset = 'UTF-8';

		}

		$str = preg_match('/[\x80-\xff]/', $this->appId) ? $this->appId : print_r($request, true);

		$this->fileCharset = mb_detect_encoding($str, "UTF-8, GBK") == 'UTF-8' ? 'UTF-8' : 'GBK';

	}


}
