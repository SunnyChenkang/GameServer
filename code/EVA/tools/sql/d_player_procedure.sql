use d_player ;

drop procedure if exists t_is_exist_player;

drop procedure if exists t_load_player;
drop procedure if exists t_load_item;
drop procedure if exists t_load_statistics;
drop procedure if exists t_load_mission;

/* d_player.t_playerinfo */
drop procedure if exists t_insert_player;
drop procedure if exists t_delete_player;
drop procedure if exists t_update_player;

/* d_player.t_item */
drop procedure if exists t_insert_item;
drop procedure if exists t_delete_item;
drop procedure if exists t_update_item;

/* d_player.t_statistics */
drop procedure if exists t_insert_statistics;
drop procedure if exists t_delete_statistics;
drop procedure if exists t_update_statistics;

/* d_player.t_mission */
drop procedure if exists t_insert_mission;
drop procedure if exists t_delete_mission;
drop procedure if exists t_update_mission;

DELIMITER ;; 

create procedure t_is_exist_player( in af_role_id int(10) unsigned )
begin
	select f_role_id from t_player where f_role_id = af_role_id;
end;;

create procedure t_load_player( in af_role_id int(10) unsigned )
begin
	select 	f_role_id ,
			f_role_kind,
			f_last_host ,
			f_game_time ,
			f_last_login_time ,
			f_last_offline_time ,
			UNIX_TIMESTAMP( f_create_time ),
			f_nick_name,
			f_head_id
			from t_player
			where f_role_id = af_role_id and f_delete_state = 0;
end;;

create procedure t_load_item( in af_role_id int(10) unsigned )
begin
	select  f_item_id,
			f_item_number,
			f_last_time
			from t_item
			where f_role_id = af_role_id and f_delete_state = 0;
end;;

create procedure t_load_statistics( in af_role_id int(10) unsigned )
begin
	select	f_statistics_id,
			f_count
			from t_statistics
			where f_role_id = af_role_id and f_delete_state = 0;
end;;

create procedure t_load_mission( in af_role_id int(10) unsigned )
begin
	select  f_mission_id,
			f_state,
			f_target,
			f_recetive_time
			from t_mission
			where f_role_id = af_role_id and f_delete_state = 0;
end;;

create procedure t_insert_player( in af_role_id   int(10) unsigned,
								  in af_role_kind tinyint(3) unsigned,
								  in af_last_host char(64) ,
								  in af_game_time int(10)    unsigned,
								  in af_last_login_time int(10) unsigned,
								  in af_last_offline_time int(10) unsigned,
								  in af_nick_name char(64),
								  in af_head_id int(10) unsigned )
begin
	insert into t_player( f_role_id , f_role_kind , f_last_host , f_game_time , f_last_login_time , f_last_offline_time,f_nick_name,f_head_id ) 
	values ( af_role_id , af_role_kind , af_last_host , af_game_time , af_last_login_time , af_last_offline_time,af_nick_name,af_head_id );
end;;

create procedure t_delete_player( in af_role_id   int(10) unsigned )
begin
	update t_player set f_delete_state = 1 where f_role_id = af_role_id;
end;;

create procedure t_update_player( in af_role_id   int(10) unsigned,
								  in af_last_host char(64),
								  in af_game_time int(10) unsigned,
								  in af_last_login_time int(10) unsigned,
								  in af_last_offline_time int(10) unsigned,
								  in af_nick_name char(64),
								  in af_head_id int(10) unsigned )
begin
	update t_player set f_last_host = af_last_host,
						f_game_time = af_game_time,
						f_last_login_time = af_last_login_time,
						f_last_offline_time = af_last_offline_time,
						f_nick_name	= af_nick_name,
						f_head_id = af_head_id
	where f_role_id = af_role_id;
end;;

create procedure t_insert_item( in af_role_id int(10) unsigned, 
								in af_item_id int(10) unsigned,
								in af_item_number int(10) unsigned,
								in af_last_time int(10) unsigned )
begin
	insert into t_item( f_role_id , f_item_id , f_item_number )
	values( af_role_id , af_item_id , af_item_number );
end;;

create procedure t_delete_item( in af_role_id int(10) unsigned )
begin
	update t_item set f_delete_state = 1 where f_role_id = af_role_id;
end;;

create procedure t_update_item( in af_role_id int(10) unsigned,
								in af_item_id int(10) unsigned,
								in af_item_number int(10) unsigned,
								in af_last_time int(10) unsigned )
begin
	update t_item set f_item_id     = af_item_id,
					  f_item_number = af_item_number,
					  f_last_time	= af_last_time
	where f_role_id = af_role_id;
end;;

create procedure t_insert_statistics( in af_role_id int(10) unsigned,
									  in af_statistics_id int(10) unsigned,
									  in af_count int(10) signed )
begin
	insert into t_statistics( f_role_id , f_statistics_id , f_count )
	values ( af_role_id , af_statistics_id , af_count );
end;;

create procedure t_delete_statistics( in af_role_id int(10) unsigned )
begin
	update t_statistics set f_delete_state = 1 where  f_role_id = af_role_id;
end;;

create procedure t_update_statistics( in af_role_id int(10) unsigned,
									  in af_statistics_id int(10) unsigned,
									  in af_count int(10) signed )
begin
	update t_statistics set f_statistics_id = af_statistics_id,
							f_count			= af_count
	where f_role_id = af_role_id;
end;;

create procedure t_insert_mission( in af_role_id int(10) unsigned,
								   in af_mission_id int(10) unsigned,
								   in af_state tinyint(3) unsigned,
								   in af_target int(10) signed,
								   in af_recetive_time int(10) unsigned )
begin
	insert into t_mission( f_role_id , f_mission_id , f_state , f_target , f_recetive_time )
	values ( af_role_id , af_mission_id , af_state , af_target , af_recetive_time );
end;;

create procedure t_delete_mission( in af_role_id int(10) unsigned )
begin
	update t_mission set f_delete_state = 1 where f_role_id = af_role_id;
end;;

create procedure t_update_mission( in af_role_id int(10) unsigned,
								   in af_mission_id int(10) unsigned,
								   in af_state tinyint(3) unsigned,
								   in af_target int(10) signed,
								   in af_recetive_time int(10) unsigned )
begin
	update t_mission set f_mission_id    = af_mission_id,
						 f_state	     = af_state,
						 f_target	  	 = af_target,
						 f_recetive_time = af_recetive_time
	where f_role_id = af_role_id;
end;;

DELIMITER ;











