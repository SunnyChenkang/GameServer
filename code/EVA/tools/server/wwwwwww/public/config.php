<?php

// This file contains all variables needed by other php scripts

$LogRelativePath = 'logs/';

$EGSModuleIP     = "localhost";
$EGSModulePort   = 30002;

$MailModuleIP    = "localhost";
$MailModulePort   = 30003;

// ----------------------------------------------------------------------------------------
// Variables for nel database access
// ----------------------------------------------------------------------------------------

// db account info
$db_account_host		= "127.0.0.1";
$db_account_username	= "root";
$db_account_password	= "";
$db_account_name		= "d_jj_account";

// 客户端最小版本号
$ClientMinVersion  = 100;
$DownLoadUrl 	   = "http://xqdp.zhiwa-game.com/WebXQ/GameDownload/html/download.html";

// If true, the server will add automatically unknown user in the database
// (in nel.user, nel.permission, ring.ring_user and ring.characters
$AcceptUnknownUser = false;
// if true, the login service automaticaly create a user if needed
$AutoCreateUserInfo = false;

// 服务器验证秘钥
$AuthSecret     = "FAF3FC3DS2KWKS2";

$SIG_KEY['ZW_XQ']          = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDFK6ysi6MTm90Z0LMQyd3LngOHyCyVCgsh8t484Cr6bXCUD0Ie/T2HWoCqqFWRCP2od27FiNP9l+I6yLaBySWE3ULhvg1BwDXVN4j+zz4u2/RZboUOQ0+SqElStrEYtgBRYbINCISQT5zvN+1DdzD6Com0IFWo77rxH9ttPFh+rwIDAQAB";
$WX_APPID['ZW_XQ']         = "wxd0e361872a1fb499";						//	appid
$WX_SECRET['ZW_XQ']        = "23F43KBFbk75HSh3e3jd232ed2hkfbsd";		//	商户api秘钥
$WX_MCHID['ZW_XQ']		   = "1498477742"; //商户号
$WX_NOTIFY_URL['ZW_XQ']	   = "http://login.jj.zhiwa-game.com/www/login/pay_wx_cb.php"; // 微信支付回调地址

$ALIPAY_APPID['ZW_XQ']	   	 = "2016091500520435";
$ALIPAY_RSA_PRIVATE['ZW_XQ'] = "MIIEogIBAAKCAQEApWDHoJZ/O7Nh6HNJKf9a4mFP9+PvhmtfTkiAuyj7t6QBohFzyZ7VzMhADyM5qk87eq0SSLXstcfNn+r9BQ3aKhQc86ob/dMzRpka00Qi3E+PgjrqLx0N4QWFUu9UKk5xJlYhOdad04n4eYzFUlN9J+sOwISDJacC1M0bXC3BGjib1+I4Dz99ESaqfLpL4tpydgFhxGaIN8Wf/U2GIKe0v3/cAw2X5arDLQMotslciwQ94CKFVXcK787XO3zcz7u9Rq5TyvHXgm5GodjVG5qcJGR94DI6MXGqk5wwCIzBkH/RcW5hzAvbRkkSaIHItxXCZJ4Dr9OIoHjvD/EY8A4PcQIDAQABAoIBAEtpAh5cAdB7T53rU+Vup0arEQf8S/CDbYYI0YqGeaGXi5cXVjEN2Hf0qCE+8sCSOJEL8lZtfm61mTHeuVlgo6akXT9OxkzLzYnXrr+/RhYnwUylCLxLB1Uga1cSAtL3yeitRaFWF8mqFD94zVFo+J0HNkbbJeI5cbUPgfZadr85bU6wvW204zSqUAjiTRY3Uao1k05f6Fs7ankU3LeR9YD+lFXc2wtwhptd0e8tIUVZAlbyzX5+5dxp6nL1YYD/B2kwjcZ5/1kg+M/B653oubklstkq9NyUnkTZ5vcdVk1ZZtQRJNp4WxxIfdrIJ4NNoj4tKq1AkFyOIV5h1yyOREECgYEAz5Jgj97qe5dAy4kgBKTTYqZqTMz4SrbQ+lhFnEofKcmQEBkTWNA+68vazs2w9x0vQA6YlhW7TZLUQsGBjfH8ZZ0nvZ/Z0rB/oMQ3k5Kxc4505iXiPotpWqHYB0v8vVX4nCU0BqWgWx0paYoUiLBceklUXpqBCqXwa/8irBOiEz0CgYEAy/ZM9IMZND6sb3UbgxmrBlcm/ELkBdRCATLc5Pf0MmR6QNwFaMhccD2EexsHU/dsjUo2mKXpI4y/T1IQPZNrl9/fI2ueSn1uEN8mAdYKS/dbzeCj839MpfBk5tWtRHQ7/kEXf/RzMmfvtBR7JHJpU4TMFmn3ICYzaddzvplIYEUCgYA3lC4e18VZSmqjFRhppeij5YNZBRkGiGT0Y2ZgLsihW8MjTFON2FTAtljkPtc/k6TvNflNVoxMfSAwr7eM1lqKqsXVVFPywieqWF+5N/IjyuUqKsKllJalGejKK2KFH9vtk1iW3wpM20YXaE2PPAnHBJN+sUgUHdJ+WFZkVO100QKBgEJurM4PTUxJBZ0gBaAD4kKkbFxJ5T9IzV7alDw3zuAC/hbWEyT37bPZNadrPE3LDx5OB85ca71agI1zazrDI45KKsG8scgNZqY0KIr8jkoD/XDnND+BPRPnYtYUzuS2/ztnNCJHGqZWWCrNaPaMFWZQoLDEPuvHxYM528c+4eYJAoGAZC0hhG31dhBSf362QteWwcKGFGYtfqy8Vpsong40jjIguYpf3L6vZLo/nR2/YBrvA23SuPGm5cEYt3C9sUF0WGt7kuHzE97xVDTSMYYwEKXitYqWQoh4jGhzUIuLoiMpgr2sc4StaeTr5ldkPlqvnosxy7fna0Wj71m5g83imqk=";//支付宝 RSA私钥
$ALIPAY_RSA_PUBLIC['ZW_XQ']	 = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEApWDHoJZ/O7Nh6HNJKf9a4mFP9+PvhmtfTkiAuyj7t6QBohFzyZ7VzMhADyM5qk87eq0SSLXstcfNn+r9BQ3aKhQc86ob/dMzRpka00Qi3E+PgjrqLx0N4QWFUu9UKk5xJlYhOdad04n4eYzFUlN9J+sOwISDJacC1M0bXC3BGjib1+I4Dz99ESaqfLpL4tpydgFhxGaIN8Wf/U2GIKe0v3/cAw2X5arDLQMotslciwQ94CKFVXcK787XO3zcz7u9Rq5TyvHXgm5GodjVG5qcJGR94DI6MXGqk5wwCIzBkH/RcW5hzAvbRkkSaIHItxXCZJ4Dr9OIoHjvD/EY8A4PcQIDAQAB";//支付宝RSA 公钥
$ALIPAY_ID['ZW_XQ']		   	 = "2088102175806905"; //支付宝商户ID
$ALIPAY_NOTIFY_URL['ZW_XQ']  = "http://login.jj.zhiwa-game.com/www/login/pay_ali_cb.php"; //回调地址
$ALIPAY_GATEWAY_URL['ZW_XQ'] = "https://openapi.alipaydev.com/gateway.do"; //支付宝网关地址
$ALIPAY_PUBLIC_KEY['ZW_XQ']  = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAsNHyJqy39GKjY9VepT9rjEgF7ximVwPQXH6cKGEn8tPTXoZTxfFnyqLcqpT4eDUKDbKJZP5mMQ35jLpTBT5+u0Kp5nnKlBzmR67PvYfFiXYuIDHJAhUnEvPFtNnTW35vUBTEgDcG7/ez1fwky0KF0f/XRqewWNVL0RoFN4yGnQ3eDXxJ20n9WySkkcvVANpyAkkHZ6TfNrrhpxnHbUOc4WKEI6Awxi29fTV/zaGiq8SdpnfVzmRN2jC6dUfPVIejJE7NSlL0zy0+DzBW9Txix7Gmcrl82WaknMUN1Gr1YkbOfSIDeuNSGcYqHT0rY4Fb5q80ZqrX52vivoKnwEHVGQIDAQAB";//支付宝公钥

?>
