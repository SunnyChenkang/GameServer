/*
Navicat MySQL Data Transfer

Source Server         : 121.43.98.130_3306
Source Server Version : 50173
Source Host           : 121.43.98.130:3306
Source Database       : wechat

Target Server Type    : MYSQL
Target Server Version : 50173
File Encoding         : 65001

Date: 2016-06-20 16:36:53
*/

drop database if exists wechat;
create database wechat default character set utf8 ;
use wechat ;

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `player_feedback`
-- ----------------------------
DROP TABLE IF EXISTS `player_feedback`;
CREATE TABLE `player_feedback` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '反馈id',
  `open_id` varchar(200) DEFAULT NULL COMMENT '微信对应公共账号openid',
  `loginType` int(11) DEFAULT '1' COMMENT '登陆方式',
  `game_number` varchar(20) DEFAULT NULL COMMENT '玩家游戏账号',
  `phone_type` int(11) DEFAULT NULL COMMENT '设备类型',
  `question_type` int(11) DEFAULT NULL COMMENT '问题类型',
  `description` varchar(300) DEFAULT NULL COMMENT '问题详情',
  `pic_cut` varchar(200) NOT NULL COMMENT '图片截图',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1 COMMENT='玩家问题反馈';

-- ----------------------------
-- Records of player_feedback
-- ----------------------------
INSERT INTO `player_feedback` VALUES ('1', '123', '2', '2', '2', '2', '2', '2');

-- ----------------------------
-- Table structure for `wx_account`
-- ----------------------------
DROP TABLE IF EXISTS `wx_account`;
CREATE TABLE `wx_account` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `accountaccesstoken` varchar(255) DEFAULT NULL,
  `accountappid` varchar(255) DEFAULT NULL,
  `accountappsecret` varchar(255) DEFAULT NULL,
  `accountdesc` varchar(255) DEFAULT NULL,
  `accountemail` varchar(255) DEFAULT NULL,
  `accountid` varchar(255) DEFAULT NULL,
  `accountname` varchar(255) DEFAULT NULL,
  `accountnumber` varchar(255) DEFAULT NULL,
  `accounttoken` varchar(255) DEFAULT NULL,
  `accounttype` int(11) DEFAULT NULL,
  `addtoekntime` datetime DEFAULT NULL,
  `username` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of wx_account
-- ----------------------------
INSERT INTO `wx_account` VALUES ('1', null, '', '', '', '2223@qq.com', '11', '11', '11', '11', '10', null, null);
INSERT INTO `wx_account` VALUES ('2', null, '', '', '', '2222@qq.com', '22', '222', '11', '122', '20', '2014-07-16 19:49:41', null);
INSERT INTO `wx_account` VALUES ('3', null, '22', '22', '222', '333@qq.com', '222', '33', '444', '444', '10', '2014-07-16 19:52:19', null);
INSERT INTO `wx_account` VALUES ('4', null, '11', '22', '222', '555@qq.com', '333', '44', '444', '555', '10', '2014-07-16 19:52:59', null);
INSERT INTO `wx_account` VALUES ('5', null, '', '', '', '222@qq.com', '555', '555', '555', '555', '10', '2014-07-16 22:42:16', null);
INSERT INTO `wx_account` VALUES ('6', null, '', '', '', '222@qq.com', '666', '666', '666', '666', '20', '2014-07-17 01:05:20', null);
