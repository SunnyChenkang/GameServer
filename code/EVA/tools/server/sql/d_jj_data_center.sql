/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50611
Source Host           : localhost:3306
Source Database       : d_jj_data_center

Target Server Type    : MYSQL
Target Server Version : 50611
File Encoding         : 65001

Date: 2015-11-28 15:32:46
*/

drop database if exists d_jj_data_center;
create database d_jj_data_center default character set utf8mb4 ;
use d_jj_data_center ;


CREATE TABLE `t_person_info` (
  `f_person_id`  int(10) unsigned NOT NULL COMMENT '' PRIMARY KEY
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- 设备信息
CREATE TABLE `t_device_info` (
  `f_account_id` int(10) unsigned NOT NULL COMMENT '帐号id',
  `f_device`     varchar(32) NOT NULL DEFAULT '' COMMENT '设备编号',
  `f_system`     varchar(32) NOT NULL DEFAULT '' COMMENT '操作系统',
  `f_version`    varchar(32) NOT NULL DEFAULT '' COMMENT '系统版本号',
  `f_phone_mode` varchar(32) NOT NULL DEFAULT '' COMMENT '手机型号',
  `f_country`    varchar(32) NOT NULL DEFAULT '' COMMENT '国家编码',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间',
  INDEX (f_account_id),
  PRIMARY KEY (`f_account_id`, `f_device`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- 账号基本信息
CREATE TABLE `t_account_info` (
  `f_account_id` int(10) unsigned NOT NULL COMMENT '帐号id',
  `f_name`       varchar(32) NOT NULL DEFAULT '' COMMENT '姓名',
  `f_mail`       varchar(32) NOT NULL DEFAULT '' COMMENT 'email',
  `f_sex`        tinyint(3) unsigned NOT NULL DEFAULT 0 comment '性别',
  `f_fb_id`      varchar(32) NOT NULL DEFAULT '' COMMENT 'facebook id',
  `f_fb_name`    varchar(32) NOT NULL DEFAULT '' COMMENT 'facebook name',
  `f_person_id`  int(10) unsigned NOT NULL DEFAULT 0 COMMENT '账号绑定到人',
  `f_weight`     int(10) unsigned NOT NULL DEFAULT 0 COMMENT '玩家贡献度',
  `f_login_day`  int(10) unsigned NOT NULL DEFAULT 0 COMMENT '累计登录天数',
  `f_last_ip`    int(10) unsigned NOT NULL DEFAULT 0 COMMENT '最后一次登录IP',
  `f_lastlogin`  timestamp  COMMENT '最后一次登录时间',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间',
  PRIMARY KEY (`f_account_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- 游戏信息统计
CREATE TABLE `t_game_info` (
  `f_account_id` int(10) unsigned NOT NULL COMMENT '帐号id',
  `f_game_id` int(10) unsigned NOT NULL DEFAULT 0 COMMENT '游戏ID',
  `f_con_exp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'consumer expectations 消费期望',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间',
  PRIMARY KEY (`f_account_id`, `f_game_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- 游戏充值记录
CREATE TABLE `t_buy_money` (
  `f_id`                  bigint(20) unsigned NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `f_account_id`          int(10) unsigned NOT NULL COMMENT '帐号id',
  `f_game_id`             int(10) unsigned NOT NULL DEFAULT 0 COMMENT '游戏ID',
  `f_game_pid`            bigint(20) unsigned NOT NULL COMMENT 'PID',
  `f_money`               bigint(20) unsigned NOT NULL DEFAULT 0 COMMENT '买到的钱',
  `f_rmb`                 bigint(20) unsigned NOT NULL DEFAULT 0 COMMENT '买到的rmb',
  `f_item_id`             int(10) unsigned NOT NULL DEFAULT 0 COMMENT '商品ID',
  `f_prices`              int(10) unsigned NOT NULL DEFAULT 0 COMMENT '商品花费的钱  1.99$x100',
  `f_order_id`            varchar(64) NOT NULL DEFAULT '' COMMENT 'sku',
  `f_buy_type`            varchar(64) NOT NULL DEFAULT '' COMMENT '商品类型',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- 玩家设备中的软件列表
CREATE TABLE `t_device_apps` (
  `f_id`                  bigint(20) unsigned NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `f_account_id`          int(10) unsigned NOT NULL COMMENT '帐号id',
  `f_device`              varchar(32) NOT NULL DEFAULT '' COMMENT '设备编号',
  `f_app_name`            varchar(64) NOT NULL DEFAULT '' COMMENT 'app name',
  `f_inserttime` timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;





