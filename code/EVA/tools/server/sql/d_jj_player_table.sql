/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50611
Source Host           : localhost:3306
Source Database       : d_jj_player

Target Server Type    : MYSQL
Target Server Version : 50611
File Encoding         : 65001

Date: 2013-05-05 14:05:24
*/


drop database if exists d_jj_player ;

create database d_jj_player default character set utf8mb4 ;

use d_jj_player ;

/*==============================================================*/
/* Table: t_playerinfo                                          */
/*==============================================================*/
drop table if exists t_playerinfo;
create table t_playerinfo
(
   f_player_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment 'PID',
   f_account_id         bigint(20) unsigned NOT NULL DEFAULT 0 comment '账号ID',
   f_nickname           char(64) NOT NULL DEFAULT "" comment '昵称',
   f_username           char(64) NOT NULL DEFAULT "" comment '渠道账号唯一ID',
   f_dynamic_msg        char(64) NOT NULL DEFAULT "" comment '个人动态',
   f_channel_id         smallint(5) unsigned NOT NULL DEFAULT 0 comment '渠道编号',
   f_level              smallint(5) unsigned NOT NULL DEFAULT 0 comment '等级',
   f_portrait           int(10) unsigned NOT NULL DEFAULT 0 comment '头像',
   f_exp                bigint(20) unsigned NOT NULL DEFAULT 0 comment '当前等级的经验',
   f_vip_level          int(10) unsigned NOT NULL DEFAULT 0 comment 'VIP 等级',
   f_vip_exp            int(10) unsigned NOT NULL DEFAULT 0 comment 'VIP 经验',
   f_vip_time			int(10) unsigned NOT NULL DEFAULT 0 comment 'VIP 时长',
   f_vip_time_level		int(10) unsigned NOT NULL DEFAULT 0 comment 'VIP 时长等级',
   f_coupon  			bigint(20) unsigned NOT NULL DEFAULT 0 comment '优惠券',
   f_money              bigint(20) unsigned NOT NULL DEFAULT 0 comment '游戏币',
   f_charge             bigint(20) unsigned NOT NULL DEFAULT 0 comment '充值获得的RMB',
   f_donate             bigint(20) unsigned NOT NULL DEFAULT 0 comment '充值赠送的RMB',
   f_bind               bigint(20) unsigned NOT NULL DEFAULT 0 comment '与充值无关的RMB产出',
   f_flag_bit           bigint(20) unsigned NOT NULL DEFAULT 0 comment '各种占一位的标识',
   f_safe_box           bigint(20) unsigned NOT NULL DEFAULT 0 comment '保险箱',
   f_like               int(10) unsigned NOT NULL DEFAULT 0 comment '收到的赞',
   f_game_time			int(10) unsigned NOT NULL DEFAULT 0 comment '游戏时长',
   f_roulette_money     int(10) NOT NULL DEFAULT 0 comment '转盘基础金币',
   f_roulette_rate      float NOT NULL DEFAULT 1 comment '转盘倍率',
   f_last_login_ip      int(10) unsigned NOT NULL DEFAULT 0 comment '最后一次登录IP',
   f_checkin_7day_count int(10) unsigned NOT NULL DEFAULT 0 comment '7天签到次数',
   f_reward_7day_time   int(10) unsigned NOT NULL DEFAULT 0 comment '7天签到领取奖励时间',
   f_collect_time  		int(10) unsigned NOT NULL DEFAULT 0 comment '敬业福初始时间',
   f_weapons_level      int(10) unsigned NOT NULL DEFAULT 1 comment '武器等级',
   f_appname            varchar(64) NOT NULL DEFAULT '' COMMENT '包名',
   f_bind_channel_id    int(10) unsigned NOT NULL DEFAULT 0 comment '渠道ID',
   f_insert_time        timestamp DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间',
   
  primary key (f_player_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_playerinfo comment '角色基础信息';

/*==============================================================*/
/* Table: t_player_priv                                         */
/*==============================================================*/
drop table if exists t_player_priv;
create table t_player_priv
(
   f_player_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment 'PID',
   f_free_money_num     int(10) unsigned NOT NULL DEFAULT 0 comment '每天免费领取金币计数',
   f_free_money_time    int(10) unsigned NOT NULL DEFAULT 0 comment '最后一次领取时间',
   f_last_login_time    int(10) unsigned NOT NULL DEFAULT 0 comment '最后一次登录时间',
   f_pig_id             int(10) unsigned NOT NULL DEFAULT 0 comment '使用的小猪ID',
   f_pig_money          bigint(20) unsigned NOT NULL DEFAULT 0 comment '小猪累计金币',
   f_tip_money          int(10) unsigned NOT NULL DEFAULT 0 comment '打赏了多少钱',
   f_tip_time           int(10) unsigned NOT NULL DEFAULT 0 comment '打赏时间',
   f_safe_box_pwd       char(16) NOT NULL DEFAULT "" comment '保险箱密码',
   f_safe_box_salt      int(10) unsigned NOT NULL DEFAULT 0,
   f_bind_proxy         bigint(20) unsigned NOT NULL DEFAULT 0 comment '代理商ID',
   f_bind_channel_id    int(10) unsigned NOT NULL DEFAULT 0 comment '渠道ID',
   primary key (f_player_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_player_priv comment '角色信息，仅服务器需要';

/*==============================================================*/
/* Table: t_championship                                        */
/*==============================================================*/
drop table if exists t_championship;
create table t_championship
(
   f_player_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment 'PID',
   f_room_type          char(8) NOT NULL DEFAULT "" comment '参加比赛的房间类型',
   f_coin               bigint(20) unsigned NOT NULL DEFAULT 0 comment '筹码数',
   f_buy_back_count     int(10) unsigned NOT NULL DEFAULT 0 comment '买活次数',
   f_last_enter         int(10) unsigned NOT NULL DEFAULT 0 comment '最后一次参加比赛的时间',
   f_time_id			int(10) unsigned NOT NULL DEFAULT 0 comment '配置表时间唯一ID',
  primary key (f_player_id, f_room_type)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_championship comment '比赛信息';

/*==============================================================*/
/* Table: t_gameinfo                                            */
/*==============================================================*/
drop table if exists t_gameinfo;
create table t_gameinfo
(
   f_player_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment 'PID',
   f_game_type          char(64) NOT NULL DEFAULT "" comment '游戏类型',
   f_ext32_0            int(10) unsigned NOT NULL DEFAULT 0,
   f_ext32_1            int(10) unsigned NOT NULL DEFAULT 0,
   f_ext32_2            int(10) unsigned NOT NULL DEFAULT 0,
   f_ext32_3            int(10) unsigned NOT NULL DEFAULT 0,
   f_ext64_0            bigint(20) unsigned NOT NULL DEFAULT 0,
   f_ext64_1            bigint(20) unsigned NOT NULL DEFAULT 0,
  primary key (f_player_id, f_game_type)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_gameinfo comment '玩家游戏数据';

/*==============================================================*/
/* Table: t_kpi                                                 */
/*==============================================================*/
drop table if exists t_kpi;
create table t_kpi
(
   f_player_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment 'PID',
   f_kpi_type           int(10) unsigned NOT NULL DEFAULT 0 comment '统计数据类型',
   f_kpi                blob NOT NULL comment '游戏统计数据',
  primary key (f_player_id, f_kpi_type)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_kpi comment '游戏统计数据';

/*==============================================================*/
/* Table: t_achievement                                         */
/*==============================================================*/
drop table if exists t_achievement;
create table t_achievement
(
   f_player_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment '角色ID' ,
   f_achievement_id     int(10) unsigned NOT NULL DEFAULT 0 comment '成就ID' ,
   f_state              tinyint(3) unsigned NOT NULL DEFAULT 0 comment '成就状态' ,
   f_target             bigint(20) unsigned NOT NULL DEFAULT 0 comment '任务目标' ,
   
   index (f_player_id),
   primary key (f_player_id , f_achievement_id )
)
ENGINE=MYISAM DEFAULT CHARSET=utf8mb4;
alter table t_achievement comment '成就数据';

/*==============================================================*/
/* Table: t_complete_achievement                                */
/*==============================================================*/
drop table if exists t_complete_achievement;
create table t_complete_achievement
(
   f_player_id           bigint(20) unsigned NOT NULL comment 'PID' ,
   f_achievement_id      blob NOT NULL comment '成就ID' ,
   
  primary key (f_player_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_complete_achievement comment '玩家已领取奖励成就信息';


/*==============================================================*/
/* Table: t_incomplete_bills                                    */
/*==============================================================*/
drop table if exists t_incomplete_bills;
create table t_incomplete_bills
(
   f_order_id            char(33) NOT NULL DEFAULT "",
   f_player_id           bigint(20) unsigned NOT NULL comment 'PID',
   f_money               bigint(20) unsigned NOT NULL DEFAULT 0,
   f_bonus               float NOT NULL DEFAULT 0 comment '购买时的加钱折扣',
   f_rmb                 bigint(20) unsigned NOT NULL DEFAULT 0,
   f_rmb_bonus           float NOT NULL DEFAULT 0 comment '购买时的加钱折扣',
   f_add_vip_exp         int(10) unsigned NOT NULL DEFAULT 0 comment '需要增加的vip积分',
   f_prices              int(10) unsigned NOT NULL DEFAULT 0 comment '商品花费的钱  1.99$x100',
   f_buy_type            char(8) NOT NULL DEFAULT "" comment '购买类型',
   f_shopid              int(10) unsigned NOT NULL DEFAULT 0 comment '商店中的商品ID',
  index (f_player_id),
  primary key (f_order_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_incomplete_bills comment '未领取的账单';

/*==============================================================*/
/* Table: t_statistics                                         */
/*==============================================================*/
drop table if exists t_statistics;
create table t_statistics
(
   f_player_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment '角色ID' ,
   f_statistics_id      int(10) unsigned NOT NULL DEFAULT 0 comment '统计数据ID' ,
   f_count              bigint(20) NOT NULL DEFAULT 0 comment '统计计数' ,
   
   index (f_player_id),
   primary key (f_player_id , f_statistics_id )
)
ENGINE=MYISAM DEFAULT CHARSET=utf8mb4;
alter table t_statistics comment '统计数据';

/*==============================================================*/
/* Table: t_service_data                                        */
/*==============================================================*/
drop table if exists t_service_data;
create table t_service_data
(
   f_sid         int(10) unsigned NOT NULL DEFAULT 0 comment '服务器ID',
   f_key         char(16) NOT NULL DEFAULT "" comment '数据分类类型',
   f_ext64_0     bigint(20) unsigned NOT NULL DEFAULT 0,
   f_ext64_1     bigint(20) unsigned NOT NULL DEFAULT 0,
   f_extdb_0     double NOT NULL DEFAULT 0,
   f_extdb_1     double NOT NULL DEFAULT 0,
   primary key (f_sid, f_key)
)
ENGINE=MYISAM DEFAULT CHARSET=utf8mb4;
alter table t_service_data comment '服务器持久化数据';

/*==============================================================*/
/* Table: t_itemdata          f_itemdata                        */
/*==============================================================*/
drop table if exists t_itemdata;
create table t_itemdata
(
   f_item_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment '物品ID' ,
   f_player_id        bigint(20) unsigned NOT NULL DEFAULT 0 comment '账号ID' ,
   f_template_id      int(10) unsigned NOT NULL DEFAULT 0 comment '配置表中的物品ID', 
   f_num              smallint(5) unsigned NOT NULL DEFAULT 0 comment '物品数量',
-- f_attach_id        bigint(20) unsigned NOT NULL DEFAULT 0 comment '归属ID',
-- f_item_type        tinyint(3) unsigned NOT NULL DEFAULT 0 comment '物品类型' ,
   f_con_type         tinyint(3) unsigned NOT NULL DEFAULT 0 comment '容器类型' ,
-- f_con_pos          tinyint(3) unsigned NOT NULL DEFAULT 0 comment '物品在容器中的位置' ,
-- f_lasttime         int(10) unsigned NOT NULL DEFAULT 0 comment '物品失效时间',
-- f_savetime         timestamp NOT NULL DEFAULT 0 DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP comment '记录保存时间' ,
   f_delete_state     tinyint(3) unsigned NOT NULL DEFAULT 0 comment '删除标记',
   f_bind_channel_id  int(10) unsigned NOT NULL DEFAULT 0 comment '渠道ID', 
   index (f_player_id),
   primary key (f_item_id)
)ENGINE=MYISAM DEFAULT CHARSET=utf8mb4;
alter table t_itemdata comment '道具数据' ;


/*==============================================================*/
/* Table: t_itemparam                                           */
/*==============================================================*/
drop table if exists t_itemparam;
create table t_itemparam
(
   f_item_id      bigint(20) unsigned NOT NULL DEFAULT 0 comment '物品ID' ,
   f_type         int(10) unsigned NOT NULL DEFAULT 0 comment '类型' ,
   f_value        bigint(20) unsigned NOT NULL DEFAULT 0 comment '类型值' ,
   f_delete_state tinyint(3) unsigned NOT NULL DEFAULT 0 comment '删除标记',
   index (f_item_id),
   primary key (f_item_id,f_type)
)
ENGINE=MYISAM DEFAULT CHARSET=utf8mb4;
alter table t_itemparam comment '物品属性数据' ;

/*==============================================================*/
/* Table: t_missiontracker                                      */
/*==============================================================*/
drop table if exists t_missiontracker;
create table t_missiontracker
(
   f_player_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment '玩家PID' ,
   f_mission_id         int(10) unsigned NOT NULL DEFAULT 0 comment '任务ID' ,
   f_accepttime         int(10) unsigned NOT NULL DEFAULT 0 comment '接取时间' ,
   f_state              tinyint(3) unsigned NOT NULL DEFAULT 0 comment '任务状态' ,
   f_target             bigint(20) unsigned NOT NULL DEFAULT 0 comment '任务目标' ,
   f_delete_state       tinyint(3) unsigned NOT NULL DEFAULT 0 comment '删除标记',
   
   index (f_player_id),
   primary key (f_player_id , f_mission_id )
)
ENGINE=MYISAM DEFAULT CHARSET=utf8mb4;
alter table t_missiontracker comment '任务记录';

/*==============================================================*/
/* Table: t_activate_icon_set                                     */
/*==============================================================*/
drop table if exists t_activate_icon_set;
create table t_activate_icon_set
(
   f_player_id               bigint(20) unsigned NOT NULL comment 'PID' ,
   f_activate_icon_id        blob NOT NULL comment '已激活的图集id' ,
   
   primary key (f_player_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_activate_icon_set comment '已激活的图集信息';

/*==============================================================*/ 
/* Table: t_unlock_icon_set                                 */
/*==============================================================*/
drop table if exists t_unlock_icon_set;
create table t_unlock_icon_set
(
   f_player_id           bigint(20) unsigned NOT NULL comment 'PID' ,
   f_curr_icon_id        int(10) unsigned NOT NULL DEFAULT 0 comment '当前正在解锁的图集id' ,
   f_start_time          int(10) unsigned NOT NULL DEFAULT 0 comment '开始解锁时间' ,
   f_unlock_icon_id      blob NOT NULL comment '已解锁的图集id' ,
   
  primary key (f_player_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_unlock_icon_set comment '已解锁的图集信息';

/*==============================================================*/
/* Table: t_qualifying                                          */
/*==============================================================*/
drop table if exists t_qualifying;
create table t_qualifying
(
   f_player_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment 'PID',
   f_qualifying         char(64) NOT NULL DEFAULT "" comment '比赛名称',
   f_coin               bigint(20) unsigned NOT NULL DEFAULT 0 comment '比赛购买筹码总数',
   f_score              int(10) unsigned NOT NULL DEFAULT 0 comment '比赛积分',
   f_credit_score		int(10) unsigned NOT NULL DEFAULT 0 comment '信用分',
   f_dan				int(10) unsigned NOT NULL DEFAULT 0 comment '段位',
   f_star 				int(10) unsigned NOT NULL DEFAULT 0 comment '星',
   f_statistics			int(10) NOT NULL DEFAULT 0 comment '统计胜利失败连续次数',
   f_last_enter         int(10) unsigned NOT NULL DEFAULT 0 comment '最后一次参加比赛的时间',
   f_insert_time		int(10) unsigned NOT NULL DEFAULT 0 comment '插入时间',
   primary key (f_player_id, f_qualifying)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_qualifying comment '排位赛';

/*==============================================================*/
/* Table: t_fighting_record                                     */
/*==============================================================*/
drop table if exists t_fighting_record;
create table t_fighting_record
(
   f_record_id			bigint(20) unsigned NOT NULL DEFAULT 0 comment '记录ID',
   f_player_id          bigint(20) unsigned NOT NULL DEFAULT 0 comment 'PID',
   f_room_type          char(64) NOT NULL DEFAULT "" comment '参加房间类型',
   f_room_id 			bigint(20) unsigned NOT NULL DEFAULT 0 comment '房间ID',
   f_time         		int(10) unsigned NOT NULL DEFAULT 0 comment '记录时间' ,
   f_content			varchar(1024)  NOT NULL DEFAULT "" comment '战斗内容',
   index(f_player_id),
   primary key (f_record_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_fighting_record comment '战斗记录';

/*==============================================================*/
/* Table: t_personal                                     		*/
/*=============================================================*/
drop table if exists t_personal;
create table t_personal 
(
  f_player_id bigint(20) unsigned NOT NULL DEFAULT 0 COMMENT '玩家ID',
  f_mobile bigint(10) unsigned DEFAULT 0 COMMENT '手机号',
  f_idcard varchar(64) DEFAULT "" COMMENT '身份证',
  f_name varchar(32) DEFAULT "" COMMENT '姓名',
  f_point int(10) unsigned DEFAULT 0 COMMENT '积分',
  f_bankcard varchar(64) DEFAULT "" COMMENT '银行卡号',
  f_bind_channel_id int(10) unsigned DEFAULT 0 COMMENT '渠道ID',
  f_bankname varchar(128) DEFAULT "" COMMENT '银行名字',
  f_banktype varchar(32) DEFAULT "" COMMENT '银行类型',
  primary key (f_player_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
alter table t_personal comment '个人信息';