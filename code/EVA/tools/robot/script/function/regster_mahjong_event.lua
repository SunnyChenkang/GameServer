regster_mahjong_event = {}

RegScriptEvent( "regster_mahjong_event", ROBOT_EVENT_MAHJONG )

--CreateTimer
--@param1 客户端唯一ID
--@param2 定时器执行脚本事件
--@param3 执行脚本名字
--@param4 执行脚本函数

--------------------------------------------------Mahjong--------------------------------------------------

-- 房间内基本消息;
local MsgRoomBaseTimeMin = 2 * 1000;
local MsgRoomBaseTimeMax = 5 * 1000;


-- 离开房间;
local MsgLeaveRoomMin = 10 * 60 * 1000;
local MsgLeaveRoomMax = 20 * 60 * 1000;

regster_mahjong_event.OnEvent = function( eventID, ID )
 	
	-- 南京麻将操作权限;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_mahjong" , "MahjongUserOperate" );
	-- 南京麻将出牌;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_mahjong" , "MahjongOutCard" );
	-- 南京麻将用户开始准备;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_mahjong" , "MahjongStartReady" );
	-- 南京麻将用户取消准备;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_mahjong" , "MahjongCancelReady" );

	
	
end




