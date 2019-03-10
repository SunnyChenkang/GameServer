regster_slots_event = {}

RegScriptEvent( "regster_slots_event", ROBOT_EVENT_SLOT )

-- 房间内基本消息;
local MsgRoomBaseTimeMin = 20 * 1000;
local MsgRoomBaseTimeMax = 30 * 1000;

local MsgSlotsSpinTimeMin = 5 * 1000;
local MsgSlotsSpinTimeMax = 10 * 1000;

local MsgLeaveRoomMin = 10 * 60 * 1000;
local MsgLeaveRoomMax = 20 * 60 * 1000;

regster_slots_event.OnEvent = function( eventID, ID )

	-- 老虎机 拉杆;
	CreateTimer( ID , math.random( MsgSlotsSpinTimeMin , MsgSlotsSpinTimeMax ) , "event_slots" , "SlotsSpin" );
	-- 老虎机小游戏;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_slots" , "SlotsBonusGameSelect" );
	-- 请求商店信息;	
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_shop" , "RequestShopInfo" );
	-- 请求购买Money;	
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_shop" , "RequestBuyMoney" );
	-- 离开房间;
	CreateTimer( ID , math.random( MsgLeaveRoomMin , MsgLeaveRoomMax ) , "event_player" , "LeaveRoom" );
	-- 房间聊天;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_blackjack" , "ChatRoom" );
	-- 请求Slots奖池数据;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_blackjack" , "GetSlotsJackpots" );

end