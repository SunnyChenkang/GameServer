/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50611
Source Host           : localhost:3306
Source Database       : d_jj_log

Target Server Type    : MYSQL
Target Server Version : 50611
File Encoding         : 65001

Date: 2015-11-28 15:32:46
*/

drop database if exists d_jj_log;
create database d_jj_log default character set utf8mb4;
use d_jj_log;


SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_daily_statistics`
-- ----------------------------
DROP TABLE IF EXISTS `t_daily_statistics`;
CREATE TABLE `t_daily_statistics` (
  `f_sampling_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '采样时间',
  `f_add_money` bigint(20) unsigned NOT NULL DEFAULT 0,
  `f_sub_money` bigint(20) unsigned NOT NULL DEFAULT 0,
  `f_add_rmb` bigint(20) unsigned NOT NULL DEFAULT 0,
  `f_add_charge` bigint(20) unsigned NOT NULL DEFAULT 0 COMMENT '充值获得的RMB',
  `f_add_donate` bigint(20) unsigned NOT NULL DEFAULT 0 COMMENT '充值赠送的RMB',
  `f_add_bind` bigint(20) unsigned NOT NULL DEFAULT 0 COMMENT '与充值无关的RMB产出',
  `f_sub_rmb` bigint(20) unsigned NOT NULL DEFAULT 0,
  PRIMARY KEY (`f_sampling_time`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COMMENT='每日统计';


-- ----------------------------
-- Table structure for `t_buy_money`
-- ----------------------------
DROP TABLE IF EXISTS `t_buy_money`;
CREATE TABLE `t_buy_money` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `f_player_id` bigint(20) unsigned NOT NULL COMMENT 'PID',
  `f_money` bigint(20) unsigned NOT NULL DEFAULT '0',
  `f_rmb` bigint(20) unsigned NOT NULL DEFAULT '0',
  `f_prices` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '商品花费的钱  1.99$x100',
  `f_item_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '商品ID',
  `f_order_id` varchar(64) NOT NULL DEFAULT '' COMMENT 'sku',
  `f_buy_type` varchar(64) NOT NULL DEFAULT '' COMMENT '商品类型',
  `f_inserttime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间',
  UNIQUE KEY `f_id` (`f_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=ascii;

-- 严重错误记录
-- ----------------------------
-- Table structure for `t_error_log`
-- ----------------------------
DROP TABLE IF EXISTS `t_error_log`;
CREATE TABLE `t_error_log` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `f_log_type` int(10) unsigned NOT NULL COMMENT 'log类型',
  `f_log_content` varchar(256) NOT NULL DEFAULT '' COMMENT 'log内容',
  `f_inserttime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间',
  PRIMARY KEY (`f_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4;

-- 邮件领取log
-- ----------------------------
-- Table structure for `t_log_mail`
-- ----------------------------
DROP TABLE IF EXISTS `t_log_mail`;
CREATE TABLE `t_log_mail` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `f_mailid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '邮件ID',
  `f_roleid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
  `f_sendid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '发送者ID',
  `f_sendname` varchar(64) DEFAULT '' COMMENT '发送者名字',
  `f_title` varchar(64) DEFAULT '' COMMENT '标题',
  `f_content` varchar(240) DEFAULT '' COMMENT '内容',
  `f_sendtime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '发送时间',
  `f_template_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '道具模板id',
  `f_item_count` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '道具个数',
  `f_currency_type` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '货币类型',
  `f_currency_num` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '货币数量',
  `f_type` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '邮件类型',
  `f_inserttime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间',
  UNIQUE KEY `f_id` (`f_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COMMENT='邮件领取log';


-- ----------------------------
-- Table structure for `t_bills_google`
-- ----------------------------
CREATE TABLE `t_bills_google` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_order_id`   varchar(128) NOT NULL COMMENT 'google 流水号',
  `f_product_id` varchar(32) NOT NULL COMMENT '购买的产品ID',
  `f_player_id`  bigint(20)  NOT NULL COMMENT '玩家id',
  `f_item_id`    int(10) unsigned NOT NULL COMMENT '商店物品ID',
  `f_app_name`   varchar(32) NOT NULL COMMENT '',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_bills_ios`
-- ----------------------------
CREATE TABLE `t_bills_ios` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_order_id`   varchar(128) NOT NULL COMMENT 'IOS AppStore 流水号',
  `f_product_id` varchar(32) NOT NULL COMMENT '购买的产品ID',
  `f_player_id`  bigint(20)  NOT NULL COMMENT '玩家id',
  `f_item_id`    int(10) unsigned NOT NULL COMMENT '商店物品ID',
  `f_app_name`   varchar(32) NOT NULL COMMENT '',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_bills_apus`
-- ----------------------------
CREATE TABLE `t_bills_apus` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_order_id`   varchar(128) NOT NULL COMMENT 'APUS 流水号',
  `f_product_id` varchar(32) NOT NULL COMMENT '购买的产品ID',
  `f_player_id`  bigint(20)  NOT NULL COMMENT '玩家id',
  `f_item_id`    int(10) unsigned NOT NULL COMMENT '商店物品ID',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_bills_alipay`
-- ----------------------------
CREATE TABLE `t_bills_alipay` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_order_id`       varchar(128) NOT NULL COMMENT '支付宝交易号',
  `f_out_trade_no`   varchar(32) NOT NULL COMMENT '商户订单号',
  `f_total_fee`      double NOT NULL COMMENT '花费',
  `f_player_id`      bigint(10)  NOT NULL COMMENT '玩家id',
  `f_item_id`        int(10) unsigned NOT NULL COMMENT '商店物品ID',
  `f_app_name`       varchar(32) NOT NULL COMMENT '',
  `f_buyer_email`    varchar(64) NOT NULL COMMENT '',
  `f_gmt_create`     timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '',
  `f_price`          double unsigned NOT NULL COMMENT '',
  `f_inserttime`     timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_bills_wx`
-- ----------------------------
DROP TABLE IF EXISTS `t_bills_wx`;
CREATE TABLE `t_bills_wx` (
  `f_id`             bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_trade_no`       varchar(128) NOT NULL COMMENT '产品交易流水号',
  `f_item_id`        int(10) unsigned NOT NULL DEFAULT 0 COMMENT '产品ID，对应游戏中出售道具的shopid',
  `f_app_name`       varchar(16) NOT NULL DEFAULT '' COMMENT '游戏客户端',
  `f_player_id`      bigint(10)  NOT NULL COMMENT '玩家id',
  `f_app_id`         varchar(32) NOT NULL COMMENT '微信分配的公众账号ID',
  `f_bank_type`      varchar(32) NOT NULL COMMENT '银行类型，采用字符串类型的银行标识',
  `f_cash_fee`       bigint(10)  NOT NULL COMMENT '现金支付金额订单现金支付金额',
  `f_fee_type`       varchar(32) NOT NULL COMMENT '货币类型，符合ISO4217标准的三位字母代码',
  `f_is_subscribe`   varchar(32) NOT NULL COMMENT '用户是否关注公众账号，Y-关注，N-未关注，仅在公众账号类型支付有效',
  `f_mch_id`         varchar(32) NOT NULL COMMENT '微信支付分配的商户号',
  `f_openid`         varchar(32) NOT NULL COMMENT '用户在商户appid下的唯一标识',
  `f_out_trade_no`   varchar(32) NOT NULL COMMENT '商户系统的订单号，与请求一致。',
  `f_time_end`       varchar(32) NOT NULL COMMENT '支付完成时间',
  `f_total_fee`      bigint(10)  NOT NULL COMMENT '订单总金额，单位为分',
  `f_trade_type`     varchar(32) NOT NULL COMMENT 'JSAPI、NATIVE、APP',
  `f_transaction_id` varchar(32) NOT NULL COMMENT '微信支付订单号',
  `f_inserttime`     timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_bills_jft`
-- ----------------------------
DROP TABLE IF EXISTS `t_bills_jft`;
CREATE TABLE `t_bills_jft` (
  `f_id`             bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_trade_no`       varchar(128) NOT NULL COMMENT '产品交易流水号',
  `f_item_id`        int(10) unsigned NOT NULL DEFAULT 0 COMMENT '产品ID，对应游戏中出售道具的shopid',
  `f_app_name`       varchar(16) NOT NULL DEFAULT '' COMMENT '游戏客户端',
  `f_player_id`      bigint(10)  NOT NULL COMMENT '玩家id',
  `f_fee`            double unsigned NOT NULL COMMENT '统一下单的金额',
  `f_inserttime`     timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_bills_jft_d`
-- ----------------------------
DROP TABLE IF EXISTS `t_bills_jft_d`;
CREATE TABLE `t_bills_jft_d` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_trade_no`       varchar(128) NOT NULL COMMENT '产品交易流水号',
  `f_app_name`       varchar(16) NOT NULL DEFAULT '' COMMENT '游戏客户端',
  `f_name`           varchar(16) NOT NULL DEFAULT '' COMMENT '姓名',
  `f_buyer_id`       bigint(10)  NOT NULL COMMENT '购买者id',
  `f_fee`            bigint(10)  unsigned NOT NULL COMMENT '花费金额',
  `f_inserttime`     timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_bind`
-- ----------------------------
CREATE TABLE `t_bind` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_game_type`  varchar(16) NOT NULL DEFAULT '' COMMENT '游戏类型',
  `f_name` varchar(128) NOT NULL COMMENT '帐号名称',
  `f_type` smallint(4) NOT NULL COMMENT '账号类型',
  `f_to_name` varchar(128) NOT NULL COMMENT '绑定到的目标帐号名称',
  `f_to_type` smallint(4) NOT NULL COMMENT '绑定到的目标账号类型',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_gift_code`
-- ----------------------------
CREATE TABLE `t_gift_code` (
  `f_gift_code` varchar(32) NOT NULL COMMENT '礼品兑换码',
  `f_template_id` int(10) unsigned NOT NULL COMMENT '礼品模板ID',
  `f_player_id`  bigint(20)  NOT NULL COMMENT '玩家id',
  `f_account_id` int(10)  NOT NULL COMMENT '帐号id',
  `f_section`     int(10) unsigned NOT NULL DEFAULT '0' COMMENT '归属号段',
  `f_id`          bigint(20) unsigned NOT NULL DEFAULT 0 COMMENT 'ID',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间',
  PRIMARY KEY (`f_gift_code`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;


-- ----------------------------
-- Table structure for `t_return_msg`
-- ----------------------------
CREATE TABLE `t_return_msg` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_app`  varchar(16) NOT NULL DEFAULT '' COMMENT 'app name',
  `f_player_id`  bigint(20)  NOT NULL COMMENT '玩家id',
  `f_account_id` int(10)  NOT NULL COMMENT '帐号id',
  `f_email` varchar(32) NOT NULL COMMENT 'email',
  `f_msg` varchar(512) NOT NULL COMMENT '反馈内容',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

CREATE TABLE `t_player_data` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_player_id`  bigint(20)  NOT NULL COMMENT '玩家id',
  `f_retmsg_tm` int(10)  NOT NULL COMMENT '最后一次反馈的时间',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

CREATE TABLE `t_sms_code` (
  `f_mn`    char(16)  NOT NULL COMMENT 'mobile number',
  `f_code`  char(8)  NOT NULL COMMENT '验证码',
  `f_instime` int(10)  NOT NULL COMMENT '记录生成时间',
  PRIMARY KEY (`f_mn`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_3u78`
-- ----------------------------
CREATE TABLE `t_3u78` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_username` varchar(128) NOT NULL COMMENT '帐号名称',
  `f_orderno` varchar(128) NOT NULL COMMENT '订单号',
  `f_productid` varchar(128) NOT NULL COMMENT '商品编号',
  `f_parvalue`  double NOT NULL COMMENT '商品面值',
  `f_num`  bigint(20)  NOT NULL COMMENT '充值数量',
  `f_account` varchar(128) NOT NULL COMMENT '购买者ip',
  `f_game`  varchar(128)  NOT NULL COMMENT '充值游戏',
  `f_zone`  varchar(128)  NOT NULL COMMENT '充值游戏区域',
  `f_server`  varchar(128)  NOT NULL COMMENT '充值游戏服务器',
  `f_state`   int(10)  NOT NULL COMMENT '处理状态',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_log_wxcdk`
-- ----------------------------
CREATE TABLE `t_log_wxcdk` (
  `f_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT UNIQUE,
  `f_openid`   varchar(128) NOT NULL COMMENT '玩家微信唯一标识',
  `f_template_id` int(32) NOT NULL COMMENT '玩家CDK模板id',
  `f_player_id`  bigint(20)  NOT NULL COMMENT '玩家id',
  `f_username`  varchar(128)  NOT NULL COMMENT '玩家id(手机号)',
  `f_cdk_key`    varchar(32) NOT NULL COMMENT '玩家CDK码',
  `f_app_name`   varchar(32) NOT NULL COMMENT '微信端',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;



