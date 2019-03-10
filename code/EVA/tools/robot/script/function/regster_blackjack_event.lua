regster_blackjack_event = {}

RegScriptEvent( "regster_blackjack_event", ROBOT_EVENT_BLACKJACK )

--CreateTimer
--@param1 客户端唯一ID
--@param2 定时器执行脚本事件
--@param3 执行脚本名字
--@param4 执行脚本函数

--------------------------------------------------BlackJack--------------------------------------------------

-- 房间内基本消息;
local MsgRoomBaseTimeMin = 10 * 1000;
local MsgRoomBaseTimeMax = 60 * 1000;

-- 下注;
local MsgPourTimeMin = 5 * 1000;
local MsgPourTimeMax = 10 * 1000;

-- 要牌、停牌、分牌;
local MsgCardTimeMin = 10 * 1000;
local MsgCardTimeMax = 50 * 1000;

-- 保险、双倍;
local MsgSurrenderTimeMin = 30 * 1000;
local MsgSurrenderTimeMax = 60 * 1000;

-- 离开房间;
local MsgLeaveRoomMin = 10 * 60 * 1000;
local MsgLeaveRoomMax = 20 * 60 * 1000;

regster_blackjack_event.OnEvent = function( eventID, ID )
 	
	-- 请求其他玩家详细信息;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_player" , "ReqPlayerInfo" );
	-- 请求其他玩家统计数据;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_player" , "ReqPlayerKPI" );
	-- 离开房间;
	CreateTimer( ID , math.random( MsgLeaveRoomMin , MsgLeaveRoomMax ) , "event_player" , "LeaveRoom" );
	-- 请求下注;
	CreateTimer( ID , math.random( MsgPourTimeMin , MsgPourTimeMax ) , "event_blackjack" , "BlackJackAddPour" );
	-- 请求要牌;
	CreateTimer( ID , math.random( MsgCardTimeMin , MsgCardTimeMax ) , "event_blackjack" , "BlackJackAskCard" );
	-- 请求分牌;
	CreateTimer( ID , math.random( MsgCardTimeMin , MsgCardTimeMax ) , "event_blackjack" , "BlackJackSplitCard" );
	-- 请求停牌;
	CreateTimer( ID , math.random( MsgCardTimeMin , MsgCardTimeMax ) , "event_blackjack" , "BlackJackStandCard" );
	-- 购买保险
	CreateTimer( ID , math.random( MsgSurrenderTimeMin , MsgSurrenderTimeMax ) , "event_blackjack" , "BlackJackBuySurrender" );
	-- 跳过保险
	CreateTimer( ID , math.random( MsgSurrenderTimeMin , MsgSurrenderTimeMax ) , "event_blackjack" , "BlackJackSkipSurrender" );
	-- 双倍;
	CreateTimer( ID , math.random( MsgSurrenderTimeMin , MsgSurrenderTimeMax ) , "event_blackjack" , "BlackJackDoubleCard" );
	-- 清除下注;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_blackjack" , "BlackJackClearPour" );
	-- Ranking Room Top;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_blackjack" , "RankingRoomTop" );
	-- 牌桌上打赏;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_blackjack" , "GiveTips" );
	-- 请求同局其它玩家详细信息;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_blackjack" , "RoomPlayerInfo" );
	-- 重置赌注(Bet, Bet*2, Betall);
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_blackjack" , "BlackJackResetPour" );
	-- 请求同步好友列表;	
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_friend" , "SynchFriendList" );
	-- 请求奖励好友;	
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_friend" , "RequestRewardFriend" );
	-- 好友邀请;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_friend" , "InviteFriend" );
	-- 房间聊天;
	CreateTimer( ID , math.random( MsgRoomBaseTimeMin , MsgRoomBaseTimeMax ) , "event_common" , "ChatRoom" );
	
	
end




