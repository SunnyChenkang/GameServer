use d_jj_player ;

drop procedure if exists _t_casino_query_role_maxid;
drop procedure if exists _t_casino_pre_treatment;
drop procedure if exists _t_casino_after_treatment;

/* t_playerinfo */
drop procedure if exists _t_playerinfo_query_playernum;
drop procedure if exists _t_playerinfo_insert;
drop procedure if exists _t_playerinfo_update;
drop procedure if exists _t_playerinfo_pagination;

/* t_achievement */
drop procedure if exists _t_achievement_insert;
drop procedure if exists _t_achievement_update;
drop procedure if exists _t_achievement_delete;
drop procedure if exists _t_achievement_pagination;

/* t_complete_achievement */
drop procedure if exists _t_complete_achievement_update;
drop procedure if exists _t_complete_achievement_insert;
drop procedure if exists _t_complete_achievement_pagination;

/* 普通游戏竞技场 */
drop procedure if exists _t_championship_pagination;
drop procedure if exists _t_championship_insert;
drop procedure if exists _t_championship_update;
drop procedure if exists _t_championship_delete;


/* 排位赛 */
drop procedure if exists _t_qualifying_pagination;
drop procedure if exists _t_qualifying_insert;
drop procedure if exists _t_qualifying_update;

drop procedure if exists _t_player_priv_pagination;
drop procedure if exists _t_player_priv_insert;
drop procedure if exists _t_player_priv_update;

drop procedure if exists _t_kpi_pagination;
drop procedure if exists _t_kpi_insert;
drop procedure if exists _t_kpi_update;

/* t_incomplete_bills */
drop procedure if exists _t_incomplete_bills_pagination;
drop procedure if exists _t_incomplete_bills_insert;
drop procedure if exists _t_incomplete_bills_delete;

/* t_statistics */
drop procedure if exists _t_statistics_insert;
drop procedure if exists _t_statistics_update;
drop procedure if exists _t_statistics_pagination;

drop procedure if exists _t_gameinfo_pagination;
drop procedure if exists _t_gameinfo_insert;
drop procedure if exists _t_gameinfo_update;

drop procedure if exists _t_service_data_pagination;
drop procedure if exists _t_service_data_insert;
drop procedure if exists _t_service_data_update;

/* t_itemdata */
drop procedure if exists _t_query_item_data;
drop procedure if exists _t_insert_item_data;
drop procedure if exists _t_update_item_data;
drop procedure if exists _t_delete_item_data;
drop procedure if exists _t_pagination_item_data;

/* t_itemparam */
drop procedure if exists _t_query_item_param;
drop procedure if exists _t_insert_item_param;
drop procedure if exists _t_update_item_param;
drop procedure if exists _t_delete_item_param;
drop procedure if exists _t_delete_item_param_all;
drop procedure if exists _t_pagination_item_param;

/* t_missiontracker */
drop procedure if exists _t_insert_mission_tracker;
drop procedure if exists _t_update_mission_tracker;
drop procedure if exists _t_delete_mission_tracker;
drop procedure if exists _t_pagination_mission_tracker;

/* t_activate_icon_set */
drop procedure if exists _t_activate_icon_set_update;
drop procedure if exists _t_activate_icon_set_insert;
drop procedure if exists _t_activate_icon_set_pagination;

/* t_unlock_icon_set */
drop procedure if exists _t_unlock_icon_set_update;
drop procedure if exists _t_unlock_icon_set_insert;
drop procedure if exists _t_unlock_icon_set_pagination;

/* t_fighting_record */
drop procedure if exists _t_fighting_record_update;
drop procedure if exists _t_fighting_record_insert;
drop procedure if exists _t_fighting_record_pagination;

drop procedure if exists _t_query_item_maxid;
drop procedure if exists _t_query_record_maxid;

/* t_personal */
drop procedure if exists _t_personal_update;
drop procedure if exists _t_personal_insert;
drop procedure if exists _t_personal_pagination;

DELIMITER ;; 

create procedure _t_playerinfo_query_playernum()
begin
	select count(*) from t_playerinfo;
end;;

create procedure _t_playerinfo_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
	       f_account_id,
		   f_nickname,
		   f_username,
		   f_dynamic_msg,
		   f_channel_id,
		   f_level,
		   f_portrait,
		   f_exp,
		   f_vip_level,
		   f_vip_exp,
		   f_vip_time,
		   f_vip_time_level,
		   f_coupon,
		   f_money,
		   f_charge,
		   f_donate,
		   f_bind,
		   f_flag_bit,
		   f_safe_box,
		   f_like,
		   f_game_time,
		   f_roulette_money,
		   f_roulette_rate,
		   f_last_login_ip,
		   f_checkin_7day_count,
		   f_reward_7day_time,
		   f_collect_time,
		   f_weapons_level,
		   f_appname,
		   f_bind_channel_id,
		   UNIX_TIMESTAMP(f_insert_time)
		   from t_playerinfo
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 2000;
end;;

create procedure _t_playerinfo_insert(
	in af_player_id bigint(20) unsigned,
	in af_account_id bigint(20) unsigned,
	in af_nickname char(64),
	in af_username char(64),
	in af_channel_id smallint(5) unsigned,
	in af_level smallint(5) unsigned,
	in af_last_login_ip int(10) unsigned
	)
begin
/*
	insert into t_playerinfo(  f_player_id,  f_account_id,  f_nickname,  f_username,  f_channel_id,  f_level, f_portrait, f_vip_exp,  f_money, f_flag_bit, f_roulette_money, f_roulette_rate )
				      values( af_player_id, af_account_id, af_nickname, af_username, af_channel_id, af_level,          0,         0, af_money,          0,                0,               1 );

	insert into t_player_priv(  f_player_id,  f_bjtip_rcv_num, f_bjtip_rcv_time, f_free_money_num, f_free_money_time )
				       values( af_player_id,                0,                0,                0,                 0 );
*/

	insert into t_playerinfo(  f_player_id,  f_account_id,  f_nickname,  f_username,  f_channel_id,  f_level,  f_last_login_ip )
				      values( af_player_id, af_account_id, af_nickname, af_username, af_channel_id, af_level, af_last_login_ip );
end;;

create procedure _t_playerinfo_update(
	in af_player_id bigint(20) unsigned,
	in af_nickname char(64),
	in af_username char(64),
	in af_dynamic_msg char(64),
	in af_channel_id smallint(5) unsigned,
	in af_level smallint(5) unsigned,
	in af_portrait int(10) unsigned,
	in af_exp bigint(20) unsigned,
	in af_vip_level int(10) unsigned,
	in af_vip_exp int(10) unsigned,
	in af_vip_time int(10) unsigned,
	in af_vip_time_level int(10) unsigned,
	in af_coupon bigint(20) unsigned,
	in af_money bigint(20) unsigned,
	in af_charge bigint(20) unsigned,
	in af_donate bigint(20) unsigned,
	in af_bind bigint(20) unsigned,
	in af_flag_bit bigint(20) unsigned,
	in af_safe_box bigint(20) unsigned,
	in af_like int(10) unsigned,
	in af_game_time int(10) unsigned,
	in af_roulette_money int(10) unsigned,
	in af_roulette_rate float,
	in af_last_login_ip int(10) unsigned,
    in af_checkin_7day_count int(10) unsigned,
    in af_reward_7day_time int(10) unsigned,
	in af_collect_time int(10) unsigned,
	in af_weapons_level int(10) unsigned,
	in af_appname varchar(64),
	in af_bind_channel_id int(10) unsigned)
	
begin
	update t_playerinfo set
		   f_nickname = af_nickname,
		   f_username = af_username,
		   f_dynamic_msg = af_dynamic_msg,
		   f_channel_id = af_channel_id,
	       f_level = af_level,
		   f_portrait = af_portrait,
		   f_exp = af_exp,
		   f_vip_level = af_vip_level,
		   f_vip_exp = af_vip_exp,
		   f_vip_time = af_vip_time,
		   f_vip_time_level = af_vip_time_level,
		   f_coupon = af_coupon,
		   f_money = af_money,
		   f_charge = af_charge,
		   f_donate = af_donate,
		   f_bind = af_bind,
		   f_flag_bit = af_flag_bit,
		   f_safe_box = af_safe_box,
		   f_like = af_like,
		   f_game_time = af_game_time,
		   f_roulette_money = af_roulette_money,
		   f_roulette_rate = af_roulette_rate,
		   f_last_login_ip = af_last_login_ip,
		   f_checkin_7day_count = af_checkin_7day_count,
		   f_reward_7day_time = af_reward_7day_time,
		   f_collect_time = af_collect_time,
		   f_weapons_level = af_weapons_level,
		   f_appname = af_appname,
		   f_bind_channel_id = af_bind_channel_id
    where  f_player_id = af_player_id;
end;;

create procedure _t_championship_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
	       f_room_type,
	       f_coin,
		   f_buy_back_count,
		   f_last_enter,
		   f_time_id
		   from t_championship
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 2000;
end;;

create procedure _t_championship_insert(
	in af_player_id       bigint(20) unsigned ,
	in af_room_type       char(8),
	in af_coin            bigint(20) unsigned,
	in af_buy_back_count  int(10) unsigned ,
	in af_last_enter      int(10) unsigned ,
	in af_time_id		  int(10) unsigned )
begin
	insert into t_championship(  f_player_id,  f_room_type,  f_coin,  f_buy_back_count,  f_last_enter , f_time_id )
				        values( af_player_id, af_room_type, af_coin, af_buy_back_count, af_last_enter , af_time_id );	
end;;

create procedure _t_championship_update(
	in af_player_id       bigint(20) unsigned ,
	in af_room_type       char(8),
	in af_coin            bigint(20) unsigned,
	in af_buy_back_count  int(10) unsigned ,
	in af_last_enter      int(10) unsigned ,
	in af_time_id		  int(10) unsigned)
begin
	update t_championship set
		   f_coin       = af_coin ,
		   f_buy_back_count = af_buy_back_count,
		   f_last_enter = af_last_enter,
		   f_time_id	= af_time_id
    where  f_player_id=af_player_id and f_room_type=af_room_type;
end;;

create procedure _t_championship_delete(
	in af_player_id       bigint(20) unsigned ,
	in af_room_type       char(8) )
begin
	DELETE FROM t_championship
    WHERE f_player_id=af_player_id and f_room_type=af_room_type;
end;;

create procedure _t_qualifying_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
	       f_qualifying,
	       f_coin,
		   f_score,
		   f_credit_score,
		   f_dan,
		   f_star,
		   f_statistics,
		   f_last_enter
		   from t_qualifying
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 2000;
end;;

create procedure _t_qualifying_insert(
	in af_player_id			bigint(20) unsigned ,
	in af_qualifying		char(64),
	in af_coin				bigint(20) unsigned,
	in af_score				int(10) unsigned,
	in af_credit_score		int(10) unsigned,
	in af_dan				int(10) unsigned,
	in af_star				int(10) unsigned,
	in af_statistics		int(10),
	in af_last_enter      	int(10) unsigned,
	in af_insert_time		int(10) unsigned)
begin
	insert into t_qualifying( f_player_id,
							  f_qualifying,
							  f_coin,
							  f_score,
							  f_credit_score,
							  f_dan,
							  f_star,
							  f_statistics,
							  f_last_enter,
							  f_insert_time)
				              values(
							  af_player_id,
							  af_qualifying,
							  af_coin,
							  af_score,
							  af_credit_score,
							  af_dan,
							  af_star,
							  af_statistics,
							  af_last_enter,
							  af_insert_time);	
end;;

create procedure _t_qualifying_update(
	in af_player_id			bigint(20) unsigned ,
	in af_qualifying		char(64),
	in af_coin				bigint(20) unsigned,
	in af_score				int(10) unsigned,
	in af_credit_score		int(10) unsigned,
	in af_dan				int(10) unsigned,
	in af_star				int(10) unsigned,
	in af_statistics		int(10),
	in af_last_enter      	int(10) unsigned )
begin
	update t_qualifying set
		   f_coin       		= af_coin,
		   f_score      		= af_score,
		   f_credit_score		= af_credit_score,
		   f_dan				= af_dan,
		   f_star				= af_star,
		   f_statistics			= af_statistics,
		   f_last_enter 		= af_last_enter
    where  f_player_id=af_player_id and f_qualifying=af_qualifying;
end;;


create procedure _t_gameinfo_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
	       f_game_type,
	       f_ext32_0,
		   f_ext32_1,
		   f_ext32_2,
		   f_ext32_3,
		   f_ext64_0,
		   f_ext64_1
		   from t_gameinfo
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 2000;
end;;

create procedure _t_gameinfo_insert(
	in af_player_id       bigint(20) unsigned ,
	in af_game_type       char(64),
	in af_ext32_0         int(10) unsigned,
	in af_ext32_1         int(10) unsigned,
	in af_ext32_2         int(10) unsigned,
	in af_ext32_3         int(10) unsigned,
	in af_ext64_0         bigint(20) unsigned,
	in af_ext64_1         bigint(20) unsigned )
begin
	insert into t_gameinfo(  f_player_id,  f_game_type,  f_ext32_0,  f_ext32_1,  f_ext32_2,  f_ext32_3,  f_ext64_0,  f_ext64_1 )
				    values( af_player_id, af_game_type, af_ext32_0, af_ext32_1, af_ext32_2, af_ext32_3, af_ext64_0, af_ext64_1 );
end;;

create procedure _t_gameinfo_update(
	in af_player_id       bigint(20) unsigned ,
	in af_game_type       char(64),
	in af_ext32_0         int(10) unsigned,
	in af_ext32_1         int(10) unsigned,
	in af_ext32_2         int(10) unsigned,
	in af_ext32_3         int(10) unsigned,
	in af_ext64_0         bigint(20) unsigned,
	in af_ext64_1         bigint(20) unsigned )
begin
	update t_gameinfo set
	       f_ext32_0	= af_ext32_0,
		   f_ext32_1	= af_ext32_1,
		   f_ext32_2	= af_ext32_2,
		   f_ext32_3	= af_ext32_3,
		   f_ext64_0	= af_ext64_0,
		   f_ext64_1	= af_ext64_1
    where  f_player_id=af_player_id and f_game_type=af_game_type;
end;;

create procedure _t_player_priv_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
		   f_free_money_num,
		   f_free_money_time,
		   f_last_login_time,
		   f_pig_id,
		   f_pig_money,
		   f_tip_money,
		   f_tip_time,
		   f_safe_box_pwd,
		   f_safe_box_salt,
		   f_bind_proxy,
		   f_bind_channel_id
		   from t_player_priv
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 2000;
end;;

create procedure _t_player_priv_insert(
	in af_player_id 				bigint(20) unsigned
	)
begin
	insert into t_player_priv( f_player_id  )
				       values( af_player_id );
end;;

create procedure _t_player_priv_update(
	in af_player_id                 bigint(20) unsigned ,
	in af_free_money_num            int(10) unsigned,
	in af_free_money_time           int(10) unsigned,
	in af_last_login_time           int(10) unsigned,
	in af_pig_id                    int(10) unsigned,
	in af_pig_money                 bigint(20) unsigned,
	in af_tip_money                 int(10) unsigned,
	in af_tip_time                  int(10) unsigned,
	in af_safe_box_pwd              char(16),
	in af_safe_box_salt             int(10) unsigned,
	in af_bind_proxy                bigint(20) unsigned,
	in af_bind_channel_id           int(10) unsigned
	)
begin
	update t_player_priv set
		   f_free_money_num       = af_free_money_num,
		   f_free_money_time      = af_free_money_time,
		   f_last_login_time      = af_last_login_time,
		   f_pig_id               = af_pig_id,
		   f_pig_money            = af_pig_money,
	       f_tip_money            = af_tip_money,
		   f_tip_time             = af_tip_time,
		   f_safe_box_pwd         = af_safe_box_pwd,
		   f_safe_box_salt        = af_safe_box_salt,
		   f_bind_proxy           = af_bind_proxy,
		   f_bind_channel_id	  = af_bind_channel_id
    where  f_player_id=af_player_id;
end;;

create procedure _t_kpi_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
	       f_kpi_type,
	       f_kpi
		   from t_kpi
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 2000;
end;;

create procedure _t_kpi_insert(
	in af_player_id       bigint(20) unsigned ,
	in af_kpi_type        int(10) unsigned,
	in af_kpi             blob )
begin
	insert into t_kpi(  f_player_id,  f_kpi_type,  f_kpi )
			   values( af_player_id, af_kpi_type, af_kpi );	
end;;

create procedure _t_kpi_update(
	in af_player_id       bigint(20) unsigned,
	in af_kpi_type        int(10) unsigned,
	in af_kpi             blob )
begin
	update t_kpi set
	       f_kpi_type = af_kpi_type,
	       f_kpi  = af_kpi
    where  f_player_id=af_player_id;
	
	if ROW_COUNT() = 0 then
		insert into t_kpi(  f_player_id, f_kpi_type, f_kpi )
			   values( af_player_id, af_kpi_type, af_kpi );	
	end if;
   
end;;

create procedure _t_achievement_insert(
	in af_player_id bigint(20) unsigned,
	in af_achievement_id int(10) unsigned,
	in af_state tinyint(3) unsigned,
	in af_target bigint(20) unsigned)
begin
	    insert into t_achievement(
		            f_player_id ,
				    f_achievement_id ,
					f_state ,
					f_target )
					values (
					af_player_id ,
					af_achievement_id ,
					af_state ,
					af_target );
end;;

create procedure _t_achievement_update(
    in af_player_id bigint(20) unsigned,
	in af_achievement_id int(10) unsigned,
	in af_state tinyint(3) unsigned,
	in af_target bigint(20) unsigned )
begin
	update t_achievement set 
			f_state = af_state,
		   f_target = af_target
	where  f_player_id = af_player_id and 
	       f_achievement_id = af_achievement_id;
end;;

create procedure _t_achievement_delete(
	in af_player_id bigint(20) unsigned,
	in af_achievement_id int(10) unsigned )
begin
	delete from t_achievement
	where  f_player_id  = af_player_id and
	       f_achievement_id = af_achievement_id;
end;;

create procedure _t_achievement_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
	       f_achievement_id,
		   f_state,
		   f_target
		   from t_achievement
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 2000;
end;;

create procedure _t_complete_achievement_update(
	in af_player_id bigint(20) unsigned,
	in af_achievement_id blob )
begin
	update t_complete_achievement set
	       f_achievement_id = af_achievement_id
	where f_player_id = af_player_id;
end;;

create procedure _t_complete_achievement_insert(
	in af_player_id bigint(20) unsigned,
	in af_achievement_id blob )
begin 
	insert into t_complete_achievement(  f_player_id,  f_achievement_id )
			   values( af_player_id, "\0\0\0\0" );
end;;

create procedure _t_complete_achievement_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
		   f_achievement_id
		   from t_complete_achievement
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 2000;
end;;	

create procedure _t_incomplete_bills_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_order_id,
	       f_player_id,
	       f_money,
		   f_bonus,
		   f_rmb,
		   f_rmb_bonus,
		   f_add_vip_exp,
		   f_prices,
		   f_buy_type,
		   f_shopid
		   from t_incomplete_bills
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 2000;
end;;

create procedure _t_incomplete_bills_insert(
	in af_order_id char(33),
	in af_player_id bigint(20) unsigned,
	in af_money bigint(20) unsigned,
	in af_bonus float,
	in af_rmb bigint(20) unsigned,
	in af_rmb_bonus float,
	in af_add_vip_exp int(10) unsigned,
	in af_prices int(10) unsigned,
	in af_buy_type char(8),
	in af_shopid int(10) unsigned	)
	
begin
	insert into t_incomplete_bills(
				f_order_id,
				f_player_id,
				f_money,
				f_bonus,
				f_rmb,
				f_rmb_bonus,
				f_add_vip_exp,
				f_prices,
				f_buy_type,
				f_shopid)
				values (
				af_order_id,
				af_player_id,
				af_money,
				af_bonus,
				af_rmb,
				af_rmb_bonus,
				af_add_vip_exp,
				af_prices,
				af_buy_type,
				af_shopid);
end;;

create procedure _t_incomplete_bills_delete( 
	in af_order_id char(33) )
begin
	delete from t_incomplete_bills 
	where  f_order_id  = af_order_id;
end;;

create procedure _t_statistics_insert(
	in af_player_id bigint(20) unsigned,
	in af_statistics_id int(10) unsigned,
	in af_count bigint(20) unsigned)
begin
	    insert into t_statistics(
		            f_player_id,
				    f_statistics_id,
					f_count )
					values (
					af_player_id,
					af_statistics_id,
					af_count );
end;;

create procedure _t_statistics_update(
    in af_player_id bigint(20) unsigned,
	in af_statistics_id int(10) unsigned,
	in af_count bigint(20) unsigned )
begin
	update t_statistics set
		   f_count = af_count
	where  f_player_id = af_player_id and 
	       f_statistics_id = af_statistics_id;
end;;

create procedure _t_statistics_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
	       f_statistics_id,
		   f_count
		   from t_statistics
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 2000;
end;;


create procedure _t_service_data_insert(
	in af_sid int(10) unsigned,
	in af_key char(16),
	in af_ext64_0 bigint(20) unsigned,
	in af_ext64_1 bigint(20) unsigned,
	in af_extdb_0 double,
	in af_extdb_1 double
	)
begin
	    insert into t_service_data(  f_sid,  f_key,  f_ext64_0,  f_ext64_1,  f_extdb_0,  f_extdb_1 )
					       values ( af_sid, af_key, af_ext64_0, af_ext64_1, af_extdb_0, af_extdb_1 );
end;;

create procedure _t_service_data_update(
	in af_sid int(10) unsigned,
	in af_key char(16),
	in af_ext64_0 bigint(20) unsigned,
	in af_ext64_1 bigint(20) unsigned,
	in af_extdb_0 double,
	in af_extdb_1 double
	)
begin
	update t_service_data set
		   f_ext64_0 = af_ext64_0,
		   f_ext64_1 = af_ext64_1,
		   f_extdb_0 = af_extdb_0,
		   f_extdb_1 = af_extdb_1
	where  f_sid=af_sid and f_key=af_key;
end;;

create procedure _t_service_data_pagination()
begin
	select f_sid,
	       f_key,
		   f_ext64_0,
		   f_ext64_1,
		   f_extdb_0,
		   f_extdb_1
		   from t_service_data;
end;;

create procedure _t_pagination_item_data(
	in a_greater_id bigint(20) unsigned )
begin
	select f_item_id,
	       f_player_id,
		   f_template_id,
		   f_num,
		   f_con_type
		   from t_itemdata
		   where f_player_id>=a_greater_id and f_delete_state = 0
		   order by f_player_id asc limit 2000;
end;;

create procedure _t_query_item_data(
	in af_player_id bigint(20) unsigned )
begin
	select f_item_id,
	       f_player_id,
		   f_template_id,
		   f_num,
		   f_con_type
		   from t_itemdata
		   where
		   f_player_id = af_player_id and f_delete_state = 0;
end;;

create procedure _t_insert_item_data(
	in af_item_id bigint(20) unsigned ,
	in af_player_id bigint(20) unsigned ,
	in af_template_id int (10) unsigned ,
	in af_num smallint(5) unsigned ,
	in af_con_type tinyint(3) unsigned ,
	in af_bind_channel_id int (10) unsigned )
begin
	insert into t_itemdata( 
				f_item_id,
				f_player_id,
				f_template_id,
				f_num,
				f_con_type,
				f_bind_channel_id)
				values(
			    af_item_id,
				af_player_id,
				af_template_id,
				af_num,
				af_con_type,
				af_bind_channel_id
			   );
end;;

create procedure _t_update_item_data(
    in af_item_id bigint(20) unsigned,
	in af_template_id int(10) unsigned,
	in af_num smallint(5) unsigned,
	in af_con_type tinyint(3) unsigned)
begin
	update t_itemdata set
           f_template_id = af_template_id,
		   f_num = af_num,
		   f_con_type = af_con_type
	where  f_item_id = af_item_id;
end;;

create procedure _t_delete_item_data(
	in af_item_id bigint(20) unsigned )
begin
	update t_itemdata set
	       f_delete_state = 1
	where  f_item_id = af_item_id;
end;;

create procedure _t_pagination_item_param(
	in a_greater_id bigint(20) unsigned )
begin
	select f_item_id,
	       f_type,
		   f_value
		   from t_itemparam
	       where  f_item_id >= a_greater_id and f_delete_state = 0 
		   order by f_item_id asc limit 2000;
end;;

create procedure _t_query_item_param(
	in af_item_id bigint(20) unsigned )
begin
	select f_item_id,
	       f_type,
		   f_value
		   from t_itemparam
	       where  f_item_id = af_item_id and f_delete_state = 0 ;
end;;

create procedure _t_insert_item_param(
	in af_item_id bigint(20) unsigned,
	in af_type int(10) unsigned ,
	in af_value bigint(20) unsigned )
begin
	insert into t_itemparam(
	            f_item_id,
				f_type,
				f_value )
				values(
				af_item_id,
				af_type,
				af_value );
end;;

create procedure _t_update_item_param(
    af_item_id bigint(20) unsigned,
	af_type int(10) unsigned ,
	af_value bigint(20) unsigned )
begin
	update t_itemparam set
		   f_value = af_value
	where  f_item_id = af_item_id and f_type = af_type;
end;;

create procedure _t_delete_item_param(
	in af_item_id bigint(20) unsigned,
	in af_type int(10) unsigned	)
begin
	update t_itemparam set
		   f_delete_state = 1
	where  f_item_id = af_item_id and f_type = af_type;
end;;

create procedure _t_delete_item_param_all(
	in af_item_id bigint(20) unsigned )
begin
	update t_itemparam set
		   f_delete_state = 1
	where  f_item_id = af_item_id;
end;;

create procedure _t_pagination_mission_tracker(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
	       f_mission_id,
		   UNIX_TIMESTAMP(f_accepttime),
		   f_state,
		   f_target
		   from t_missiontracker
		   where f_player_id>=a_greater_id and f_delete_state = 0
		   order by f_player_id asc limit 2000;
end;;

create procedure _t_insert_mission_tracker(
	in af_player_id bigint(20) unsigned,
	in af_mission_id int (10) unsigned,
	in af_accepttime int (10) unsigned,
	in af_state tinyint(3) unsigned,
	in af_target bigint(20) unsigned )
begin
	insert into t_missiontracker( 
				f_player_id,
				f_mission_id,
				f_accepttime,
				f_state,
				f_target)
				values(
				af_player_id,
				af_mission_id,
				af_accepttime,
				af_state,
				af_target
			   );
end;;

create procedure _t_update_mission_tracker(
    in af_player_id bigint(20) unsigned,
	in af_mission_id int(10) unsigned,
	in af_accepttime int(10) unsigned,
	in af_state tinyint(3) unsigned,
	in af_target bigint(20) unsigned )
begin
	update t_missiontracker set
           f_accepttime = af_accepttime,
		   f_state      = af_state,
		   f_target     = af_target
	where  f_player_id = af_player_id and f_mission_id = af_mission_id;
end;;

create procedure _t_delete_mission_tracker(
	in af_player_id bigint(20) unsigned,
	in af_mission_id int(10) unsigned )
begin
	update t_missiontracker set
	       f_delete_state = 1
	where  f_player_id = af_player_id and f_mission_id = af_mission_id;
end;;

create procedure _t_activate_icon_set_update(
	in af_player_id bigint(20) unsigned,
	in af_activate_icon_id blob )
begin
	update t_activate_icon_set set
	       f_activate_icon_id = af_activate_icon_id
	where f_player_id = af_player_id;
end;;

create procedure _t_activate_icon_set_insert(
	in af_player_id bigint(20) unsigned,
	in af_activate_icon_id blob )
begin 
	insert into t_activate_icon_set(  f_player_id,  f_activate_icon_id )
			   values( af_player_id, af_activate_icon_id );
end;;

create procedure _t_activate_icon_set_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
		   f_activate_icon_id
		   from t_activate_icon_set
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 1000;
end;;	

create procedure _t_unlock_icon_set_update(
	in af_player_id bigint(20) unsigned,
	in af_curr_icon_id int(10) unsigned,
	in af_start_time int(10) unsigned,
	in af_unlock_icon_id blob )
begin
	update t_unlock_icon_set set
	       f_curr_icon_id = af_curr_icon_id,
		   f_start_time = af_start_time,
	       f_unlock_icon_id = af_unlock_icon_id
	where f_player_id = af_player_id;
end;;

create procedure _t_unlock_icon_set_insert(
	in af_player_id bigint(20) unsigned,
	in af_curr_icon_id int(10) unsigned,
	in af_start_time int(10) unsigned,
	in af_unlock_icon_id blob )
begin 
	insert into t_unlock_icon_set( f_player_id,  f_curr_icon_id,  f_start_time, f_unlock_icon_id )
			   values( af_player_id, af_curr_icon_id, af_start_time, af_unlock_icon_id );
end;;

create procedure _t_unlock_icon_set_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
		   f_curr_icon_id,
		   f_start_time,
		   f_unlock_icon_id
		   from t_unlock_icon_set
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 1000;
end;;	

create procedure _t_fighting_record_update(
	in af_record_id bigint(20) unsigned,	
	in af_player_id bigint(20) unsigned,
	in af_room_type  char(64),
	in af_room_id   bigint(20) unsigned,
	in af_time 		int(10) unsigned,
	in af_content	varchar(1024) )
begin
	update t_fighting_record set
	       f_room_type = af_room_type,
		   f_room_id = af_room_id,
	       f_time = af_time,
		   f_content = af_content
	where  f_record_id = af_record_id;
end;;

create procedure _t_fighting_record_insert(
	in af_record_id bigint(20) unsigned,	
	in af_player_id bigint(20) unsigned,
	in af_room_type  char(64),
	in af_room_id   bigint(20) unsigned,
	in af_time 		int(10) unsigned,
	in af_content	varchar(1024) )
begin 
	insert into t_fighting_record( f_record_id,   f_player_id,  f_room_type,  f_room_id,  f_time,  f_content )
			               values( af_record_id, af_player_id, af_room_type, af_room_id, af_time, af_content );
end;;

create procedure _t_fighting_record_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_record_id,
		   f_player_id,
		   f_room_type,
		   f_room_id,
		   f_time,
		   f_content
		   from t_fighting_record
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 1000;
end;;	

--  8位服务器ID 52位ID  4位区ID
create procedure _t_casino_query_role_maxid()
begin
	select max( f_player_id >> 4 ) from t_playerinfo;
end;;

create procedure _t_query_item_maxid()
	select max( ( f_item_id >> 4 ) & 0xFFFFFFFFFFFFF ) from t_itemdata;;
	
create procedure _t_query_record_maxid()
	select max( ( f_record_id >> 4 ) & 0xFFFFFFFFFFFFF ) from t_fighting_record;;
	
create procedure _t_casino_pre_treatment()
begin
/*
	ALTER TABLE `t_itemdata`
	ADD INDEX `idx_itemdata` (`f_player_id`) USING BTREE ;

	ALTER TABLE `t_itemparam`
	ADD INDEX `idx_itemparam` (`f_item_id`) USING BTREE ;

	ALTER TABLE `t_guard_data`
	ADD INDEX `idx_guarddata` (`f_player_id`) USING BTREE ;

	ALTER TABLE `t_limituse`
	ADD INDEX `idx_limituse` (`f_player_id`) USING BTREE ;

	ALTER TABLE `t_missiontemp`
	ADD INDEX `idx_missiontemp` (`f_player_id`) USING BTREE ;

	ALTER TABLE `t_missiontracker`
	ADD INDEX `idx_missiontracker` (`f_player_id`) USING BTREE ;

	ALTER TABLE `t_achievement`
	ADD INDEX `idx_achievement` (`f_player_id`) USING BTREE ;

	ALTER TABLE `t_hero`
	ADD INDEX `idx_hero` (`f_player_id`) USING BTREE ;

	ALTER TABLE `t_castle_info`
	ADD INDEX `idx_castledata` (`f_player_id`) USING BTREE ;
*/
end;;

create procedure _t_casino_after_treatment()
begin
/*
	--ALTER TABLE `t_playerinfo` 		DROP INDEX `idx_player`;
	--ALTER TABLE `t_itemdata`   		DROP INDEX `idx_itemdata`;
	--ALTER TABLE `t_guard_data` 		DROP INDEX `idx_guarddata`;
	--ALTER TABLE `t_limituse`   		DROP INDEX `idx_limituse`;
	--ALTER TABLE `t_missiontemp`		DROP INDEX `idx_missiontemp`;
	--ALTER TABLE `t_missiontracker`	DROP INDEX `idx_missiontracker`;
	--ALTER TABLE `t_achievement`		DROP INDEX `idx_achievement`;
	--ALTER TABLE `t_hero`			    DROP INDEX `idx_hero`;
	--ALTER TABLE `t_castle_info`		DROP INDEX `idx_castledata`;
*/
end;;

create procedure _t_personal_update(
	in af_player_id bigint(20) unsigned,	
	in af_mobile bigint(10) unsigned,	
	in af_idcard  varchar(64),
	in af_name   varchar(32),
	in af_point  int(10) unsigned,
	in af_bankcard	varchar(64),
	in af_bind_channel_id  int(10) unsigned ,
	in af_bankname varchar(128),
	in af_banktype varchar(32))
begin
	declare num int;
	select count(*) into num from t_personal where f_player_id = af_player_id;
	if(num = 0) then
		insert into t_personal( f_player_id,  f_mobile,  f_idcard,  f_name,  f_point,  f_bankcard,  f_bind_channel_id, f_bankname, f_banktype )
				   values( af_player_id, af_mobile, af_idcard, af_name, af_point, af_bankcard, af_bind_channel_id, af_bankname, af_banktype );
	else
		update t_personal set
			f_mobile = af_mobile,
	       		f_idcard = af_idcard,
		   	f_name = af_name,
	       		f_point = af_point,
		   	f_bankcard = af_bankcard,
			f_bind_channel_id = af_bind_channel_id,
			f_bankname = af_bankname,
			f_banktype = af_banktype
		where  f_player_id = af_player_id;
	end if;
end;;

create procedure _t_personal_insert(
	in af_player_id bigint(20) unsigned,	
	in af_mobile bigint(10) unsigned,	
	in af_idcard  varchar(64),
	in af_name   varchar(32),
	in af_point  int(10) unsigned,
	in af_bankcard	varchar(64),
	in af_bind_channel_id  int(10) unsigned,
	in af_bankname varchar(128),
	in af_banktype varchar(32) )
begin 
	insert into t_personal( f_player_id,  f_mobile,  f_idcard,  f_name,  f_point,  f_bankcard,  f_bind_channel_id , f_bankname , f_banktype )
			               values( af_player_id, af_mobile, af_idcard, af_name, af_point, af_bankcard, af_bind_channel_id , af_bankname , af_banktype );
end;;
	
create procedure _t_personal_pagination(
	in a_greater_id bigint(20) unsigned )
begin
	select f_player_id,
		   f_mobile,
	       f_idcard,
		   f_name,
		   f_point,
		   f_bankcard,
		   f_bind_channel_id,
		   f_bankname,
		   f_banktype
		   from t_personal
		   where f_player_id>=a_greater_id
		   order by f_player_id asc limit 1000;
end;;

DELIMITER ;











