use d_jj_log ;

-- ----------------------------
-- Procedure structure for `_t_fes_event_insert`
-- ----------------------------
DROP PROCEDURE IF EXISTS `_t_fes_event_insert`;
DELIMITER ;;
CREATE PROCEDURE `_t_fes_event_insert`(
	in af_id bigint(20),
	in af_event varchar(50),
	in af_param varchar(1024),
	in af_time int(10)
	)
begin
	insert into t_fes_event(
	            f_id,
				f_event,
				f_param,
				f_time
				)
				values(
				af_id,
				af_event,
				af_param,
				af_time
				);
end
;;
DELIMITER ;


drop procedure if exists _t_daily_statistics_querylast;
drop procedure if exists _t_daily_statistics_insert;
drop procedure if exists _t_daily_statistics_update;

drop procedure if exists _t_buy_money_insert;
drop procedure if exists _t_error_log_insert;
drop procedure if exists _t_mail_logs_insert;

DELIMITER ;; 
  
create procedure _t_daily_statistics_querylast()
begin
	select UNIX_TIMESTAMP(f_sampling_time),
	       f_add_money,
	       f_add_rmb,
	       f_add_charge,
	       f_add_donate,
	       f_add_bind,
	       f_sub_money,
	       f_sub_rmb
		   from t_daily_statistics
		   order by f_sampling_time desc limit 1;
end;;
  
create procedure _t_daily_statistics_insert(
	in af_sampling_time int(10) unsigned
	)
begin
	insert into t_daily_statistics( f_sampling_time )
				            values( FROM_UNIXTIME(af_sampling_time) );
end;;


create procedure _t_daily_statistics_update(
	in af_sampling_time int(10) unsigned,
	in af_add_money bigint(20) unsigned,
	in af_add_rmb bigint(20) unsigned,
	in af_add_charge bigint(20) unsigned,
	in af_add_donate bigint(20) unsigned,
	in af_add_bind bigint(20) unsigned,
	in af_sub_money bigint(20) unsigned,
	in af_sub_rmb bigint(20) unsigned
	)
	
begin
	update t_daily_statistics set
		   f_add_money = af_add_money,
		   f_add_rmb = af_add_rmb,
		   f_add_charge = af_add_charge,
		   f_add_donate = af_add_donate,
	       f_add_bind = af_add_bind,
		   f_sub_money = af_sub_money,
		   f_sub_rmb = af_sub_rmb where UNIX_TIMESTAMP(f_sampling_time)=af_sampling_time;
end;;

create procedure _t_buy_money_insert(
	in af_player_id bigint(20) unsigned,
	in af_money bigint(20) unsigned,
	in af_rmb bigint(20) unsigned,
	in af_prices int(10) unsigned,
	in af_item_id int(10) unsigned,
	in af_order_id varchar(64),
	in af_buy_type varchar(64)
	)
begin
	insert into t_buy_money(  f_player_id,  f_money,  f_rmb,  f_prices,  f_item_id,  f_order_id,  f_buy_type )
				     values( af_player_id, af_money, af_rmb, af_prices, af_item_id, af_order_id, af_buy_type );
end;;

create procedure _t_error_log_insert(
	in af_log_type int(10) unsigned,
	in af_log_content varchar(64)
	)
begin
	insert into t_error_log(  f_log_type,  f_log_content )
				     values( af_log_type, af_log_content );
end;;

create procedure _t_mail_logs_insert(
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
	insert into t_log_mail(
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

DELIMITER ;
