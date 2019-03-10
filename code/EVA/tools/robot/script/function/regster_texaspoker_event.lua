regster_texaspoker_event = {}

RegScriptEvent( "regster_texaspoker_event", ROBOT_EVENT_TEXASPOKER )

----------------------------------------Texaspoker----------------------------------------
local MsgRoomBaseTimeMin = 5 * 30 * 1000;
local MsgRoomBaseTimeMax = 5 * 60 * 1000;

-- 跟注;
local MsgCallPourTimeMin = 1 * 1000;
local MsgCallPourTimeMax = 5 * 1000;

-- 加注;
local MsgRaisePourTimeMin = 10 * 1000;
local MsgRaisePourTimeMax = 30 * 1000;

-- 弃牌、让牌、重置筹码
local MsgCardTimeMin = 30 * 1000;
local MsgCardTimeMax = 60 * 1000;

-- 离开房间;
local MsgLeaveRoomMin = 10 * 60 * 1000;
local MsgLeaveRoomMax = 20 * 60 * 1000;

-- 返回游戏;
local MsgGoBackGameMin = 5 * 30 * 1000;
local MsgGoBackGameMax = 5 * 60 * 1000;

regster_texaspoker_event.OnEvent = function( eventID, ID )
 
    -- 玩家跟注;
	CreateTimer( ID , math.random( MsgCallPourTimeMin , MsgCallPourTimeMax ) , "event_texaspker" , "CallPour" );
	-- 玩家加注;
	CreateTimer( ID , math.random( MsgRaisePourTimeMin , MsgRaisePourTimeMax ) , "event_texaspker" , "RaisePour" );
	-- 玩家弃牌;
	CreateTimer( ID , math.random( MsgCardTimeMin , MsgCardTimeMax ) , "event_texaspker" , "FoldCard" );
	-- 玩家让牌;
	CreateTimer( ID , math.random( MsgCardTimeMin , MsgCardTimeMax ) , "event_texaspker" , "CheckCard" );
	-- 重置筹码;
	CreateTimer( ID , math.random( MsgCardTimeMin , MsgCardTimeMax ) , "event_texaspker" , "ResetCoins" );
	-- 离开房间;
	CreateTimer( ID , math.random( MsgLeaveRoomMin , MsgLeaveRoomMax ) , "event_player" , "LeaveRoom" );
	-- 返回游戏;
	CreateTimer( ID, math.random( MsgGoBackRoomMin, MsgGoBackRoomMax ) , "event_texaspker", "GoBackGame" );
	-- 房间聊天;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_common" , "ChatRoom" );
	-- 好友邀请;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_friend" , "InviteFriend" );
	-- 请求同步好友列表;	
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_friend" , "SynchFriendList" );
	-- 德州竞技场报名;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_texaspker" , "TPChallApplyGame" );
	-- 德州取消竞技场报名;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_texaspker" , "TPChallCancelApplyGame" );
	-- 德州竞技场房间信息;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_texaspker" , "TPChallRoomData" );
	-- 德州竞技场请求退出;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_texaspker" , "TPChallRequestQuit" );
	
end