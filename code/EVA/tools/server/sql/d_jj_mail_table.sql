
drop database if exists d_jj_mail ;

create database d_jj_mail default character set utf8mb4 ;

use d_jj_mail ;


-- ----------------------------
-- Table structure for `t_mail_common`
-- ----------------------------
DROP TABLE IF EXISTS `t_mail_common`;
CREATE TABLE `t_mail_common` (
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
  PRIMARY KEY (`f_mailid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COMMENT='普通邮件';


-- ----------------------------
-- Table structure for `t_mail_system`
-- ----------------------------
DROP TABLE IF EXISTS `t_mail_system`;
CREATE TABLE `t_mail_system` (
  `f_roleid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
  `f_owner` blob NOT NULL COMMENT '拥有邮件',
  `f_idx` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '位置',
  `f_circle` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '圈数',
  PRIMARY KEY (`f_roleid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COMMENT='系统邮件';

-- ----------------------------
-- Table structure for `t_mail_template`
-- ----------------------------
DROP TABLE IF EXISTS `t_mail_template`;
CREATE TABLE `t_mail_template` (
  `f_autoid` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '自增列',
  `f_name` varchar(32) DEFAULT '' COMMENT '名字',
  `f_title` varchar(64) DEFAULT '' COMMENT '标题',
  `f_content` varchar(240) DEFAULT '' COMMENT '内容',
  `f_sendtime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '发送时间',
  `f_pasttime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '过期时间',
  `f_type` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '邮件类型',
  `f_template_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '道具模板id',
  `f_item_count` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '道具个数',
  `f_currency_type` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '货币类型',
  `f_currency_num` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '货币数量',
  `f_inserttime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '记录生成时间',
  `f_appname` varchar(64) DEFAULT '' COMMENT '包名',
  PRIMARY KEY (`f_autoid`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COMMENT='系统邮件模板';

-- ----------------------------
-- Table structure for `t_friend`
-- ----------------------------
DROP TABLE IF EXISTS `t_friend`;
CREATE TABLE `t_friend` (
  `f_roleid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色ID',
  `f_friend` blob NOT NULL COMMENT '好友',
  PRIMARY KEY (`f_roleid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COMMENT='好友';

-- ----------------------------
-- Table structure for `t_black_list`
-- ----------------------------
DROP TABLE IF EXISTS `t_black_list`;
CREATE TABLE `t_black_list` (
  `f_roleid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色ID',
  `f_black_list` blob NOT NULL COMMENT '黑名单',
  PRIMARY KEY (`f_roleid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COMMENT='黑名单';

-- ----------------------------
-- Table structure for `t_bind_friend`
-- ----------------------------
DROP TABLE IF EXISTS `t_bind_friend`;
CREATE TABLE `t_bind_friend` (
  `f_bind_src_player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '发送邀请码的玩家PID',
  `f_bind_dst_player_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '使用邀请码的玩家PID',
  `f_state` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'scr右边界面dst玩家各个任务完成状况scr的领取记录',
  `f_game_count` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '已经完成的游戏局数',
  `f_dst_state` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'dst自己的领取记录',
  PRIMARY KEY (`f_bind_src_player_id`,`f_bind_dst_player_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COMMENT='分享好友模版';

-- ----------------------------
-- Table structure for `t_friend_tissue`
-- ----------------------------
DROP TABLE IF EXISTS `t_friend_tissue`;
CREATE TABLE `t_friend_tissue` (
  `f_tissue_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '群组织ID',
  `f_name` varchar(64) DEFAULT '' COMMENT '群组织名字',
  `f_master_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '群主',
  `f_member` blob NOT NULL COMMENT '群成员',
  `f_delete_state`  int(10) unsigned NOT NULL DEFAULT '0' COMMENT '删除表状态',
  `f_create_time`   int(10) unsigned NOT NULL DEFAULT '0' COMMENT '创建时间',
  `f_tissue_state`  int(10) unsigned NOT NULL DEFAULT '0' COMMENT '群状态',
  `f_tissue_money`  bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '群组织库存货币',
  `f_tissue_limit`  int(10) unsigned NOT NULL DEFAULT '0' COMMENT '群组织每日消耗上限',
  `f_tissue_areaid` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '群归属地理位置',
  `f_gamelist` blob NOT NULL COMMENT '游戏列表',
  `f_tissue_notity`  varchar(256) DEFAULT '' COMMENT '群公告',
  `f_bind_channel_id`  int(10) unsigned NOT NULL DEFAULT '0' COMMENT '渠道ID',
  `f_identity_state`   int(10) unsigned NOT NULL DEFAULT '0' COMMENT '认证状态',
  `f_tissue_icon`   varchar(256) DEFAULT '' COMMENT  '俱乐部图标',
  PRIMARY KEY (`f_tissue_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COMMENT='群组织';
