/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50611
Source Host           : localhost:3306
Source Database       : d_jj_account

Target Server Type    : MYSQL
Target Server Version : 50611
File Encoding         : 65001

Date: 2013-05-05 14:05:24
*/


drop database if exists d_jj_account ;

create database d_jj_account default character set utf8mb4 ;

use d_jj_account ;

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `t_account_info`
-- ----------------------------
DROP TABLE IF EXISTS `t_account_info`;
CREATE TABLE `t_account_info` (
  `f_account_id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '游戏帐号id',
  `f_name` varchar(128) NOT NULL DEFAULT '' COMMENT '帐号名称',
  `f_type` smallint(4) NOT NULL DEFAULT '0' COMMENT '账号类型',
  `f_freeze_time` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '冻结到什么时间',
  `f_uuid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'f_uuid',
  `f_insert_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间',
  PRIMARY KEY (`f_name`,`f_type`),
  UNIQUE KEY `f_account_id` (`f_account_id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Table structure for `t_area`
-- ----------------------------
DROP TABLE IF EXISTS `t_area`;
CREATE TABLE `t_area` (
  `f_start_host` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'IP开始',
  `f_end_host` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'IP结束',
  `f_country` varchar(45) NOT NULL DEFAULT '' COMMENT '国家',
  `f_province` varchar(45) NOT NULL DEFAULT '' COMMENT '省份',
  `f_city` varchar(45) NOT NULL DEFAULT '' COMMENT '城市',
  `f_district` varchar(45) NOT NULL DEFAULT '' COMMENT '地区',
  `f_isp` varchar(45) NOT NULL DEFAULT '' COMMENT '运营商',
  `f_area_code` varchar(45) NOT NULL DEFAULT '' COMMENT '地区标识',
  PRIMARY KEY (`f_start_host`,`f_end_host`),
  KEY `f_start_host` (`f_start_host`),
  KEY `f_end_host` (`f_end_host`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;