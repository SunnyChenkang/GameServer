use d_jj_data_center;

/* 真实玩家基本信息  */
drop procedure if exists _t_person_info_pagination;
drop procedure if exists _t_person_info_insert;
drop procedure if exists _t_person_info_update;

/* 账号基本信息 */
drop procedure if exists _t_account_info_pagination;
drop procedure if exists _t_account_info_insert;
drop procedure if exists _t_account_info_update;

/* 游戏充值记录 */
drop procedure if exists _t_buy_money_pagination;
drop procedure if exists _t_buy_money_insert;

/* 设备信息 */
drop procedure if exists _t_device_info_pagination;
drop procedure if exists _t_device_info_insert;
drop procedure if exists _t_device_info_update;

/* 设备安装的app */
drop procedure if exists _t_device_apps_pagination;
drop procedure if exists _t_device_apps_insert;

DELIMITER ;; 

create procedure _t_person_info_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_person_id
		   from t_person_info
		   where f_person_id>=a_greater_id
		   order by f_person_id asc limit 2000;
end;;

create procedure _t_person_info_update(
	in af_old_person_id int(10) unsigned,
	in af_new_person_id int(10) unsigned
	)
begin
	update t_person_info set
		   f_person_id  = af_new_person_id
    where  f_person_id = af_old_person_id;
end;;

create procedure _t_person_info_insert(
	in af_person_id int(10) unsigned
	)
begin
	insert into t_person_info(  f_person_id )
				       values( af_person_id );
						
end;;

create procedure _t_device_info_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_account_id, f_device, f_system, f_version, f_phone_mode, f_country
		   from t_device_info
		   where f_account_id>=a_greater_id
		   order by f_account_id asc limit 2000;
end;;

create procedure _t_device_info_update(
	in af_account_id int(10) unsigned,
	in af_device varchar(32),
	in af_system varchar(32),
	in af_version varchar(32),
	in af_phone_mode varchar(32),
	in af_country varchar(32)
	)
begin
	update t_device_info set
		   f_account_id = af_account_id,
		   f_device     = af_device,
		   f_system     = af_system,
		   f_version    = af_version,
		   f_phone_mode = af_phone_mode,
		   f_country    = af_country
    where  f_account_id = af_account_id;
end;;
  
create procedure _t_device_info_insert(
	in af_account_id int(10) unsigned,
	in af_device  varchar(32),
	in af_system  varchar(32),
	in af_version varchar(32),
	in af_phone_mode varchar(32),
	in af_country varchar(32)
	)
begin
	insert into t_device_info(  f_account_id,  f_device,  f_system,  f_version,  f_phone_mode,  f_country )
				       values( af_account_id, af_device, af_system, af_version, af_phone_mode, af_country );
						
end;;

create procedure _t_account_info_pagination(
	in a_greater_id int(10) unsigned )
begin
	select f_account_id,
		   f_name,
		   f_mail,
		   f_sex,
		   f_fb_id,
		   f_fb_name,
		   f_person_id,
		   f_weight,
		   f_login_day,
		   f_last_ip,
		   UNIX_TIMESTAMP(f_lastlogin),
		   UNIX_TIMESTAMP(f_inserttime)
		   from t_account_info
		   where f_account_id>=a_greater_id
		   order by f_account_id asc limit 2000;
end;;

create procedure _t_account_info_insert(
	in af_account_id int(10) unsigned
	)
begin
	insert into t_account_info(  f_account_id )
				        values( af_account_id );
end;;

create procedure _t_account_info_update(
	in af_account_id int(10) unsigned,
	in af_name varchar(32),
	in af_mail varchar(32),
	in af_sex tinyint(3) unsigned,
	in af_fb_id varchar(32),
	in af_fb_name varchar(32),
	in af_person_id int(10) unsigned,
	in af_weight    int(10) unsigned,
	in af_login_day int(10) unsigned,
	in af_last_ip   int(10) unsigned,
	in af_lastlogin int(10) unsigned
	)
	
begin
	update t_account_info set
		   f_name  = af_name,
		   f_mail  = af_mail,
		   f_sex   = af_sex,
		   f_fb_id = af_fb_id,
	       f_fb_name = af_fb_name,
		   f_person_id = af_person_id,
		   f_weight = af_weight,
		   f_login_day = af_login_day,
		   f_last_ip = af_last_ip,
		   f_lastlogin = FROM_UNIXTIME(af_lastlogin)
    where  f_account_id = af_account_id;
end;;

  
create procedure _t_buy_money_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_account_id,
		   f_game_id,
		   f_game_pid,
		   f_money,
		   f_rmb,
		   f_item_id,
		   f_prices,
		   f_order_id,
		   f_buy_type,
		   UNIX_TIMESTAMP(f_inserttime)
		   from t_buy_money
		   where f_account_id>=a_greater_id
		   order by f_account_id asc limit 2000;
end;;

create procedure _t_buy_money_insert(
	in af_account_id int(10) unsigned,
	in af_game_id int(10) unsigned,
	in af_game_pid bigint(20) unsigned,
	in af_money bigint(20) unsigned,
	in af_rmb bigint(20) unsigned,
	in af_item_id int(10) unsigned,
	in af_prices int(10) unsigned,
	in af_order_id varchar(64),
	in af_buy_type varchar(64)
	)
begin
	insert into t_buy_money(  f_account_id,  f_game_id,  f_game_pid,  f_money,  f_rmb,  f_item_id,  f_prices,  f_order_id,  f_buy_type )
				     values( af_account_id, af_game_id, af_game_pid, af_money, af_rmb, af_item_id, af_prices, af_order_id, af_buy_type );	
end;;

create procedure _t_device_apps_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_id, f_device, f_app_name
		   from t_device_apps
		   where f_id>a_greater_id
		   order by f_id asc limit 2000;
end;;

create procedure _t_device_apps_insert(
	in af_account_id int(10) unsigned,
	in af_device varchar(32),
	in af_app_name varchar(64)
	)
begin
	insert into t_device_apps(  f_account_id,  f_device,  f_app_name )
				       values( af_account_id, af_device, af_app_name );	
end;;



DELIMITER ;












