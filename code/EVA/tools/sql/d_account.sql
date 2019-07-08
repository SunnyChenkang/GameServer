/*
Navicat MySQL Data Transfer;

Source Server         : localhost_3306;
Source Server Version : 50611;
Source Host           : localhost:3306;
Source Database       : d_account;

Target Server Type    : MYSQL;
Target Server Version : 50611;
File Encoding         : 65001;

Date: 2019-3-15 11:30;
*/


drop database if exists d_account;

create database d_account default character set utf8mb4;

use d_account;

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for t_account_guest
-- ----------------------------
DROP TABLE IF EXISTS t_account_guest;
CREATE TABLE `t_account_guest` (
	f_account_id		int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 		'帐号id',
	f_device_id			varchar(128) NOT NULL DEFAULT '' COMMENT 					'设备唯一标识',
	f_freeze_to_time	int(10) unsigned NOT NULL DEFAULT '0' COMMENT 				'冻结到什么时间',
	f_inserttime 		timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 		'记录生成时间',
  PRIMARY KEY(f_account_id),
  KEY `f_device_id` (`f_device_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

