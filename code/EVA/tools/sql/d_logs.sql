/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50611
Source Host           : localhost:3306
Source Database       : d_logs

Target Server Type    : MYSQL
Target Server Version : 50611
File Encoding         : 65001

Date: 2013-05-05 14:05:24
*/

drop database if exists d_logs;

create database d_logs default character set utf8mb4;

use d_logs;

-- login;
drop procedure if exists t_login_dot_create;
drop procedure if exists t_login_dot_insert;

-- offline;
drop procedure if exists t_offline_dot_create;
drop procedure if exists t_offline_dot_insert;

-- item;
drop procedure if exists t_item_dot_create;
drop procedure if exists t_item_dot_insert;


DELIMITER ;;

create procedure t_login_dot_create()
begin
	set @login_dot_create = concat(
	'CREATE TABLE IF NOT EXISTS t_login_dot_', date_format(curdate(),'%y%m%d'),
	"(
		`f_auto_id`		 bigint(20)   unsigned NOT NULL AUTO_INCREMENT		 comment '自增ID',
		`f_role_id`		 int(10)      unsigned NOT NULL DEFAULT 0 			 comment '角色ID',
		`f_role_kind`	 int(10)   	  unsigned NOT NULL DEFAULT 0 			 comment '角色类型',
		`f_client_host`	 varchar(64)  NOT NULL DEFAULT '' 					 comment 'IP地址',
		`f_offline_time` timestamp 	  NOT NULL DEFAULT '0000-00-00 00:00:00' comment '离线时间',
		`f_insert_time`  timestamp    NOT NULL DEFAULT '0000-00-00 00:00:00' comment '记录生成事件',
		PRIMARY KEY(`f_auto_id`),
		KEY `f_role_id` (`f_role_id`)
	) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4" );
	PREPARE login_dot_create FROM @login_dot_create;
	EXECUTE login_dot_create;
end;;

create procedure t_login_dot_insert( in af_role_id  	int(10) unsigned,
									 in af_role_kind 	int(10) unsigned,
									 in af_client_host	varchar(64),
									 in af_offline_time int(10) unsigned,
									 in af_insert_time  int(10) unsigned)
begin
	call t_login_dot_create();
	set @role_id 		  = af_role_id;
	set @role_kind		  = af_role_kind;
	set @client_host      = af_client_host;
	set @offline_time 	  = af_offline_time;
	set @insert_time 	  = FROM_UNIXTIME(af_insert_time);
	set @login_dot_insert = concat("INSERT INTO t_login_dot_" , date_format(curdate() , "%y%m%d"),
	"(`f_role_id`,`f_role_kind`,`f_client_host`,`f_offline_time`,`f_insert_time`) VALUES (?,?,?,?,?)");
	PREPARE login_dot_insert FROM @login_dot_insert;
	EXECUTE login_dot_insert USING @role_id,@role_kind,@client_host,@offline_time,@insert_time;
end;;

create procedure t_offline_dot_create()
begin
	set @offline_dot_create = concat(
	'CREATE TABLE IF NOT EXISTS t_offline_dot_' , date_format( curdate() , '%y%m%d') ,
	"(
		`f_auto_id` 	bigint(20) 	unsigned NOT NULL AUTO_INCREMENT 		comment '自增ID',
		`f_role_id`		int(10) 	unsigned NOT NULL DEFAULT 0 			comment '角色ID',
		`f_role_kind`	int(10)		unsigned NOT NULL DEFAULT 0 			comment '角色类型',
		`f_client_host`	varchar(64) NOT NULL DEFAULT ''						comment 'IP地址',
		`f_login_time`	timestamp 	NOT NULL DEFAULT '0000-00-00 00:00:00'	comment '上线时间',
		`f_insert_time`  timestamp    NOT NULL DEFAULT '0000-00-00 00:00:00' comment '记录生成事件',
		PRIMARY KEY(`f_auto_id`),
		KEY `f_role_id` (`f_role_id`)
	) ENGINE = InnoDB DEFAULT CHARSET=utf8mb4" );
	PREPARE offline_dot_create FROM @offline_dot_create;
	EXECUTE offline_dot_create;
end;;

create procedure t_offline_dot_insert( in af_role_id     int(10) 	unsigned,
									   in af_role_kind   int(10) 	unsigned,
									   in af_client_host varchar(64),
									   in af_login_time  int(10) unsigned,
									   in af_insert_time int(10) unsigned )
begin
	call t_offline_dot_create();
	set @role_id 		= af_role_id;
	set @role_kind		= af_role_kind;
	set @client_host	= af_client_host;
	set @login_time 	= af_login_time;
	set @insert_time 	= af_insert_time;
	set @offline_dot_insert = concat("INSERT INTO t_offline_dot_" , date_format(curdate() , "%y%m%d"),
	"(`f_role_id` , `f_role_kind` , `f_client_host` , `f_login_time` , `f_insert_time`) VALUES(?,?,?,?,?)" );
	PREPARE offline_dot_insert FROM @offline_dot_insert;
	EXECUTE offline_dot_insert USING @role_id,@role_kind,@client_host,@login_time,@insert_time;
end;;

create procedure t_item_dot_create()
begin
	set @item_dot_create = concat(
	'CREATE TABLE IF NOT EXISTS t_item_dot_', date_format(curdate(),'%y%m%d'),
	"(
		`f_auto_id` 	bigint(20) unsigned NOT NULL AUTO_INCREMENT 		comment '自增ID',
		`f_item_id` 	int(10) unsigned NOT NULL DEFAULT 0 				comment '道具ID',
		`f_role_id` 	int(10) unsigned NOT NULL DEFAULT 0 				comment '角色ID',
		`f_oper_dot`	int(10) unsigned NOT NULL DEFAULT 0 				comment '操作事件',
		`f_oper_count`	int(10) unsigned NOT NULL DEFAULT 0 				comment '操作道具数量',
		`f_total_count` int(10) unsigned NOT NULL DEFAULT 0 				comment '操作后道具总数量',
		`f_insert_time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00'	comment '记录生成时间',
		PRIMARY KEY( `f_auto_id` ),
		KEY `f_role_id` (`f_role_id`,`f_item_id`),
		KEY `f_item_id` (`f_item_id`)
	) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4" );
	PREPARE item_dot_create FROM @item_dot_create;  
	EXECUTE item_dot_create;
end;;

create procedure t_item_dot_insert( in af_item_id	  int(10) unsigned,
									in af_role_id	  int(10) unsigned,
									in af_oper_dot	  int(10) unsigned,
									in af_oper_count  int(10) unsigned,
									in af_total_count int(10) unsigned,
									in af_insert_time int(10) unsigned)
begin
	call t_item_dot_create();
	set @item_id  		 = af_item_id;
	set @role_id  		 = af_role_id;
	set @oper_dot 		 = af_oper_dot;
	set @oper_count		 = af_oper_count;
	set @total_count	 = af_total_count;
	set @insert_time 	 = FROM_UNIXTIME(af_insert_time);
	set @item_dot_insert = concat("INSERT INTO t_item_dot_" , date_format(curdate() ,'%y%m%d'),
	"(`f_item_id`,`f_role_id`,`f_oper_dot`,`f_oper_count`,`f_total_count`,`f_insert_time`) VALUES(?,?,?,?,?,?)");
	PREPARE item_dot_insert FROM  @item_dot_insert;
	EXECUTE item_dot_insert USING @item_id,@role_id,@oper_dot,@oper_count,@total_count,@insert_time;
end;;

DELIMITER ;
