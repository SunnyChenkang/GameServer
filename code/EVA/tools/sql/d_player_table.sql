/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50611
Source Host           : localhost:3306
Source Database       : d_player

Target Server Type    : MYSQL
Target Server Version : 50611
File Encoding         : 65001

Date: 2013-05-05 14:05:24
*/


drop database if exists d_player ;

create database d_player default character set utf8mb4 ;

use d_player ;

/*==============================================================*/
/* Table: t_player                                         */
/*==============================================================*/
drop table if exists t_player;
create table t_player
(
   f_role_id			int(10) 	unsigned NOT NULL DEFAULT 0 comment '角色ID',
   f_role_kind 			tinyint(3)  unsigned NOT NULL DEFAULT 0 comment '角色类型',
   f_last_host			char(64) 	NOT NULL DEFAULT "" comment 		'上次登录地址',
   f_game_time			int(10) 	unsigned NOT NULL DEFAULT 0 comment '游戏时长',
   f_last_login_time	int(10) 	unsigned NOT NULL DEFAULT 0 comment '最后登录时间',
   f_last_offline_time  int(10) 	unsigned NOT NULL DEFAULT 0 comment '最后离线时间',
   f_nick_name			char(64)	NOT NULL DEFAULT "" comment 		'角色昵称',			
   f_head_id			int(10)		unsigned NOT NULL DEFAULT 0 comment '角色头像ID',
   f_create_time 		timestamp 	DEFAULT CURRENT_TIMESTAMP  comment 	'角色创建时间',	
   f_delete_state		tinyint(3)  unsigned NOT NULL DEFAULT 0 comment '删除状态',
  primary key (f_role_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_player comment '角色基础信息';

/*==============================================================*/
/* Table: t_item                                                */
/*==============================================================*/
drop table if exists t_item;
create table t_item
(
   f_role_id 		int(10) 	unsigned NOT NULL DEFAULT 0 comment '角色ID',
   f_item_id		int(10) 	unsigned NOT NULL DEFAULT 0 comment '道具ID',
   f_item_number	int(10) 	unsigned NOT NULL DEFAULT 0 comment '道具数量',
   f_last_time		int(10) 	unsigned NOT NULL DEFAULT 0 comment '失效时间',
   f_delete_state	tinyint(3)  unsigned NOT NULL DEFAULT 0 comment '删除状态',
   
  primary key (f_role_id , f_item_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_item comment '道具信息';

/*==============================================================*/
/* Table: t_statistics                                          */
/*==============================================================*/
drop table if exists t_statistics;
create table t_statistics
(
   f_role_id 		int(10) 	unsigned NOT NULL DEFAULT 0 comment '角色ID',
   f_statistics_id	int(10) 	unsigned NOT NULL DEFAULT 0 comment '统计ID',
   f_count			int(10) 	 		 NOT NULL DEFAULT 0 comment '统计数量',
   f_delete_state	tinyint(3)  unsigned NOT NULL DEFAULT 0 comment '删除状态',
   
  primary key (f_role_id , f_statistics_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_statistics comment '统计信息';

/*==============================================================*/
/* Table: t_mission                                             */
/*==============================================================*/
drop table if exists t_mission;
create table t_mission
(
   f_role_id 		int(10) 	unsigned NOT NULL DEFAULT 0 comment '角色ID'  ,
   f_mission_id		int(10) 	unsigned NOT NULL DEFAULT 0 comment '统计ID'  ,
   f_state			tinyint(3) 	unsigned NOT NULL DEFAULT 0 comment '任务状态', 
   f_target			int(10) 	 	     NOT NULL DEFAULT 0 comment '任务目标', 
   f_recetive_time	int(10) 	unsigned NOT NULL DEFAULT 0 comment '接取时间', 
   f_delete_state	tinyint(3)  unsigned NOT NULL DEFAULT 0 comment '删除状态',
   
  primary key (f_role_id , f_mission_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_mission comment '任务信息';