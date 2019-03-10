
use d_jj_mail ;


drop procedure if exists _t_casion_pagination_common;
drop procedure if exists _t_casion_query_common;
drop procedure if exists _t_casion_insert_common;
drop procedure if exists _t_casion_update_common;
drop procedure if exists _t_casion_delete_common;
drop procedure if exists _t_casion_query_maxid;

drop procedure if exists _t_casion_pagination_system;
drop procedure if exists _t_casion_query_system;
drop procedure if exists _t_casion_insert_system;
drop procedure if exists _t_casion_update_system;
drop procedure if exists _t_casion_delete_system;

drop procedure if exists _t_casino_pagination_template;
drop procedure if exists _t_casino_query_template;
drop procedure if exists _t_casino_insert_template;
drop procedure if exists _t_casino_update_template;
drop procedure if exists _t_casino_delete_template;

drop procedure if exists _t_casion_friend_pagination;
drop procedure if exists _t_casion_friend_query;
drop procedure if exists _t_casion_friend_insert;
drop procedure if exists _t_casion_friend_update;
drop procedure if exists _t_casion_friend_delete;

drop procedure if exists _t_casion_black_list_pagination;
drop procedure if exists _t_casion_black_list_query;
drop procedure if exists _t_casion_black_list_insert;
drop procedure if exists _t_casion_black_list_update;
drop procedure if exists _t_casion_black_list_delete;

drop procedure if exists _t_casion_bind_friend_pagination;
drop procedure if exists _t_casion_bind_friend_query;
drop procedure if exists _t_casion_bind_friend_insert;
drop procedure if exists _t_casion_bind_friend_update;
drop procedure if exists _t_casion_bind_friend_delete;

drop procedure if exists _t_casion_friend_tissue_pagination;
drop procedure if exists _t_casion_friend_tissue_query;
drop procedure if exists _t_casion_friend_tissue_insert;
drop procedure if exists _t_casion_friend_tissue_update;
drop procedure if exists _t_casion_friend_tissue_delete;
drop procedure if exists _t_casion_friend_tissue_query_maxid;

DELIMITER ;;

create procedure _t_casion_pagination_system(
	in af_greaterid bigint(20) unsigned )
begin
	select f_roleid,
		   f_owner,
		   f_idx,
		   f_circle
		   from t_mail_system
		   where
		   f_roleid > af_greaterid order by f_roleid asc limit 1000;
end;;

create procedure _t_casion_query_system(
	in af_roleid bigint(20) unsigned )
begin
	select f_roleid,
		   f_owner,
		   f_idx,
		   f_circle
		   from t_mail_system
		   where
		   f_roleid = af_roleid;
end;;

create procedure _t_casion_insert_system(
	in af_roleid bigint(20) unsigned,
	in af_owner blob ,
	in af_idx int(10) unsigned,
	in af_circle int(10) unsigned)
begin
	insert into t_mail_system(
				f_roleid,
				f_owner,
				f_idx,
				f_circle)
				value(
				af_roleid,
				af_owner,
				af_idx,
				af_circle);
end;;

create procedure _t_casion_update_system(
	in af_roleid bigint(20) unsigned,
	in af_owner blob ,
	in af_idx int(10) unsigned,
	in af_circle int(10) unsigned )
begin
	update t_mail_system set
		   f_owner  = af_owner,
		   f_idx = af_idx,
		   f_circle = af_circle
	where  f_roleid = af_roleid;
end;;

create procedure _t_casion_delete_system(
	in af_roleid bigint(20) unsigned )
begin
	delete from t_mail_system where f_roleid = af_roleid;
end;;

create procedure _t_casion_pagination_common(
	in af_greaterid bigint(20) unsigned )
begin
	select f_mailid,
		   f_roleid,
		   f_sendid,
		   f_sendname,
		   f_title,
		   f_content,
		   f_sendtime,
		   f_template_id,
		   f_item_count,
		   f_currency_type,
		   f_currency_num,
		   f_type
		   from t_mail_common
		   where 
		   f_mailid > af_greaterid order by f_mailid asc limit 1000;
end;;

create procedure _t_casion_query_common(
	in af_mailid bigint(20) unsigned)
begin
	select f_mailid,
		   f_roleid,
		   f_sendid,
		   f_sendname,
		   f_title,
		   f_content,
		   f_sendtime,
		   f_template_id,
		   f_item_count,
		   f_currency_type,
		   f_currency_num,
		   f_type
		   from t_mail_common
		   where 
		   f_mailid = af_mailid;
end;;

create procedure _t_casion_insert_common(
	in af_mailid bigint(20) unsigned,
	in af_roleid bigint(20) unsigned,
	in af_sendid bigint(20) unsigned,
	in af_sendname varchar(64),
	in af_title varchar(64),
	in af_content varchar(240),
	in af_sendtime int(10) unsigned,
    in af_template_id int(10) unsigned,
    in af_item_count int(10) unsigned,
    in af_currency_type int(10) unsigned,
    in af_currency_num bigint(20) unsigned,
	in af_type tinyint(3) unsigned)
begin
	insert into t_mail_common(
				f_mailid,
				f_roleid,
				f_sendid,
				f_sendname,
				f_title,
				f_content,
				f_sendtime,
		        f_template_id,
		        f_item_count,
				f_currency_type,
				f_currency_num,
				f_type)
				value (
				af_mailid,
				af_roleid,
				af_sendid,
				af_sendname,
				af_title,
				af_content,
				af_sendtime,
				af_template_id,
				af_item_count,
				af_currency_type,
				af_currency_num,
				af_type);
end;;

create procedure _t_casion_update_common(
	in af_mailid bigint(20) unsigned,
	in af_roleid bigint(20) unsigned,
	in af_sendid bigint(20) unsigned,
	in af_sendname varchar(64),
	in af_title varchar(64),
	in af_content varchar(240),
	in af_sendtime int(10) unsigned,
    in af_template_id int(10) unsigned,
	in af_item_count int(10) unsigned,
	in af_currency_type int(10) unsigned,
	in af_currency_num bigint(20) unsigned,
	in af_type tinyint(3) unsigned )
begin
	update t_mail_common set
		   f_roleid = af_roleid,
		   f_sendid = af_sendid,
		   f_sendname = af_sendname,
		   f_title  = af_title,
		   f_content= af_content,
		   f_sendtime = af_sendtime,
		   f_template_id = af_template_id,
		   f_item_count = af_item_count,
		   f_currency_type = af_currency_type,
		   f_currency_num = af_currency_num,
		   f_type = af_type
	where
		   f_mailid = af_mailid;
end;;

create procedure _t_casion_delete_common(
	in af_mailid bigint(20) unsigned )
begin
	delete from t_mail_common where f_mailid = af_mailid;
end;;

create procedure _t_casion_query_maxid()
begin
	select max( f_mailid >> 4 ) from t_mail_common;
end;;

create procedure _t_casino_pagination_template(
	in af_greaterid bigint(20) unsigned,
	in af_cur_time int(10) unsigned )
begin
	select f_autoid,
		   f_name,
		   f_title,
		   f_content,
		   f_sendtime,
		   f_pasttime,
		   f_type,
		   f_template_id,
		   f_item_count,
		   f_currency_type,
		   f_currency_num,
		   f_appname
		   from t_mail_template
		   where 
		   f_autoid > af_greaterid order by f_autoid asc limit 1000;
end;;

create procedure _t_casino_query_template(
	in af_autoid bigint(20) unsigned )
begin
	select f_autoid,
		   f_name,
		   f_title,
		   f_content,
		   f_sendtime,
		   f_pasttime,
		   f_type,
		   f_template_id,
		   f_item_count,
		   f_currency_type,
		   f_currency_num,
		   f_appname
		   from t_mail_template
		   where 
		   af_autoid = f_autoid;
end;;

create procedure _t_casino_insert_template (
	in af_name varchar(32),
	in af_title varchar(64),
	in af_content varchar(240),
	in af_sendtime int(10) unsigned,
	in af_pasttime int(10) unsigned,
	in af_type tinyint(3) unsigned,
    in af_template_id int(10) unsigned,
    in af_item_count int(10) unsigned,
	in af_currency_type int(10) unsigned,
    in af_currency_num bigint(20) unsigned,
	in af_appname varchar(64)	)
begin
	insert into t_mail_template(
				f_name,
				f_title,
				f_content,
				f_sendtime,
				f_pasttime,
				f_type,
                f_template_id,
				f_item_count,
                f_currency_type,
				f_currency_num,
				f_appname )
				values (
				af_name,
				af_title,
				af_content,
				af_sendtime,
				af_pasttime,
				af_type,
				af_template_id,
				af_item_count,
				af_currency_type,
				af_currency_num,
				af_appname
				);
end;;

create procedure _t_casino_update_template(
	in af_autoid bigint(20) unsigned,
	in af_name varchar(32),
	in af_title varchar(64),
	in af_content varchar(240),
	in af_sendtime int(10) unsigned,
	in af_pasttime int(10) unsigned,
	in af_type tinyint(3) unsigned,
    in af_template_id int(10) unsigned,
    in af_item_count int(10) unsigned,
	in af_currency_type int(10) unsigned,
    in af_currency_num bigint(20) unsigned,
	in af_appname varchar(64))
begin
	update t_mail_template set 
		   f_name = af_name,
		   f_title = af_title,
		   f_content = af_content,
		   f_sendtime = af_sendtime,
		   f_pasttime = af_pasttime,
		   f_type = af_type,
           f_template_id = af_template_id,
		   f_item_count = af_item_count,
		   f_currency_type = af_currency_type,
		   f_currency_num = af_currency_num,
		   f_appname = af_appname
	where
		   f_autoid=af_autoid;
end;;

create procedure _t_casino_delete_template(
	in af_autoid bigint(20) unsigned )
begin
	delete from t_mail_template where f_autoid = af_autoid;
end;;

create procedure _t_casion_friend_pagination(
	in af_greaterid bigint(20) unsigned )
begin
	select f_roleid,
		   f_friend
		   from t_friend
		   where
		   f_roleid > af_greaterid order by f_roleid asc limit 1000;
end;;

create procedure _t_casion_friend_query(
	in af_roleid bigint(20) unsigned )
begin
	select f_roleid,
		   f_friend
		   from t_friend
		   where f_roleid=af_roleid;
end;;

create procedure _t_casion_friend_insert(
	in af_roleid bigint(20) unsigned,
	in af_friend blob )
begin
	insert into t_friend(
				f_roleid,
				f_friend)
				values(
				af_roleid,
				af_friend);
end;;

create procedure _t_casion_friend_update(
	in af_roleid bigint(20) unsigned,
	in af_friend blob )
begin
	update t_friend set 
		   f_friend = af_friend
		   where
		   f_roleid = af_roleid;
end;;

create procedure _t_casion_friend_delete( 
	in af_roleid bigint(20) unsigned )
begin
	delete from t_friend where f_roleid = af_roleid;
end;;


create procedure _t_casion_black_list_pagination(
	in af_greaterid bigint(20) unsigned )
begin
	select f_roleid,
		   f_black_list
		   from t_black_list
		   where
		   f_roleid > af_greaterid order by f_roleid asc limit 1000;
end;;

create procedure _t_casion_black_list_query(
	in af_roleid bigint(20) unsigned )
begin
	select f_roleid,
		   f_black_list
		   from t_black_list
		   where f_roleid=af_roleid;
end;;

create procedure _t_casion_black_list_insert(
	in af_roleid bigint(20) unsigned,
	in af_black_list blob )
begin
	insert into t_black_list(
				f_roleid,
				f_black_list)
				values(
				af_roleid,
				af_black_list);
end;;

create procedure _t_casion_black_list_update(
	in af_roleid bigint(20) unsigned,
	in af_black_list blob )
begin
	update t_black_list set 
		   f_black_list = af_black_list
		   where
		   f_roleid = af_roleid;
end;;

create procedure _t_casion_black_list_delete( 
	in af_roleid bigint(20) unsigned )
begin
	delete from t_black_list where f_roleid = af_roleid;
end;;

create procedure _t_casion_bind_friend_pagination(
	in a_greaterid bigint(20) unsigned )
begin
	select f_bind_src_player_id,
		   f_bind_dst_player_id,
		   f_state,
		   f_game_count,
		   f_dst_state
		   from t_bind_friend
		   where
		   f_bind_src_player_id > a_greaterid order by f_bind_src_player_id asc limit 2000;
end;;

create procedure _t_casion_bind_friend_query(
	in af_bind_src_player_id bigint(20) unsigned,
	in af_bind_dst_player_id bigint(20) unsigned )
begin
	select f_bind_src_player_id,
		   f_bind_dst_player_id,
		   f_state,
		   f_game_count,
		   f_dst_state
		   from t_bind_friend
		   where f_bind_src_player_id = af_bind_src_player_id and f_bind_dst_player_id = af_bind_dst_player_id;
end;;

create procedure _t_casion_bind_friend_insert(
	in af_bind_src_player_id bigint(20) unsigned,
	in af_bind_dst_player_id bigint(20) unsigned,
	in af_state int(10) unsigned,
	in af_game_count int(10) unsigned,
	in af_dst_state int(10) unsigned )
begin
	insert into t_bind_friend(
				f_bind_src_player_id,
				f_bind_dst_player_id,
				f_state,
				f_game_count,
				f_dst_state)
				values(
				af_bind_src_player_id,
				af_bind_dst_player_id,
				af_state,
				af_game_count,
				af_dst_state);
end;;

create procedure _t_casion_bind_friend_update(
	in af_bind_src_player_id bigint(20) unsigned,
	in af_bind_dst_player_id bigint(20) unsigned,
	in af_state int(10) unsigned,
	in af_game_count int(10) unsigned,
	in af_dst_state int(10) unsigned )
begin
	update t_bind_friend set 
		   f_state = af_state,
		   f_game_count = af_game_count,
		   f_dst_state = af_dst_state
		   where
		   f_bind_src_player_id = af_bind_src_player_id and f_bind_dst_player_id = af_bind_dst_player_id;
end;;

create procedure _t_casion_bind_friend_delete( 
	in af_bind_src_player_id bigint(20) unsigned,
	in af_bind_dst_player_id bigint(20) unsigned )
begin
	delete from t_bind_friend 
	where f_bind_src_player_id = af_bind_src_player_id and f_bind_dst_player_id = af_bind_dst_player_id;
end;;

create procedure _t_casion_friend_tissue_pagination(
	in a_greaterid bigint(20) unsigned )
begin
	select f_tissue_id,
		   f_name,
		   f_master_id,
		   f_create_time,
		   f_tissue_state,
		   f_tissue_areaid,
		   f_member,
		   f_gamelist,
		   f_tissue_money,
		   f_tissue_limit,
		   f_tissue_notity,
		   f_identity_state,
		   f_tissue_icon
		   from t_friend_tissue
		   where
		   f_delete_state = 0 and f_tissue_id > a_greaterid order by f_tissue_id asc limit 2000;
end;;

create procedure _t_casion_friend_tissue_insert(
	in af_tissue_id bigint(20) unsigned,
	in af_name varchar(64) ,
	in af_master_id bigint(20) unsigned,
	in af_member blob ,
	in af_create_time int(10) unsigned,
	in af_tissue_state int(10) unsigned,
	in af_tissue_money bigint(20) unsigned,
	in af_tissue_limit int(10) unsigned,
	in af_tissue_areaid int(10) unsigned,
	in af_gamelist blob,
	in af_tissue_notity varchar(256),
	in af_bind_channel_id int(10) unsigned,
	in af_identity_state int(10) unsigned,
	in af_tissue_icon varchar(256) )
begin
	insert into t_friend_tissue(
				f_tissue_id,
				f_name,
				f_master_id,
				f_member,
				f_create_time,
				f_delete_state,
				f_tissue_state,
				f_tissue_money,
				f_tissue_limit,
				f_tissue_areaid,
				f_gamelist,
				f_tissue_notity,
				f_bind_channel_id,
				f_identity_state,
				f_tissue_icon)
				values(
				af_tissue_id,
				af_name,
				af_master_id,
				af_member,
				af_create_time,
				0,
				af_tissue_state,
				af_tissue_money,
				af_tissue_limit,
				af_tissue_areaid,
				af_gamelist,
				af_tissue_notity,
				af_bind_channel_id,
				af_identity_state,
				af_tissue_icon);
end;;

create procedure _t_casion_friend_tissue_update(
	in af_tissue_id bigint(20) unsigned,
	in af_member blob,
	in af_tissue_state  int(10) unsigned,
	in af_name varchar(64),
	in af_tissue_money  bigint(20) unsigned,
	in af_tissue_limit int(10) unsigned,
	in af_gamelist blob,
	in af_tissue_notity varchar(256),
	in af_identity_state int(10) unsigned,
	in af_tissue_icon varchar(256) )
begin
	update t_friend_tissue set
		   f_tissue_id    	= af_tissue_id,
		   f_member 	  	= af_member,
		   f_name         	= af_name,
		   f_tissue_state 	= af_tissue_state,
		   f_tissue_money	= af_tissue_money,
		   f_tissue_limit 	= af_tissue_limit,
		   f_gamelist		= af_gamelist,
		   f_tissue_notity	= af_tissue_notity,
		   f_identity_state = af_identity_state,
		   f_tissue_icon	= af_tissue_icon
	where  f_tissue_id    	= af_tissue_id;
end;;

create procedure _t_casion_friend_tissue_delete(
	in af_tissue_id bigint(20) unsigned )
begin
	update t_friend_tissue set
		   f_delete_state = 1
	where  f_tissue_id = af_tissue_id;
end;;

create procedure _t_casion_friend_tissue_query_maxid()
begin
	select max( f_tissue_id ) from t_friend_tissue;
end;;

DELIMITER ;

