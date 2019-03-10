regster_event = {}

RegScriptEvent( "regster_event", ROBOT_EVENT_REGSTEREVENT )

--CreateTimer
--@param1 客户端唯一ID
--@param2 定时器执行脚本事件
--@param3 执行脚本名字
--@param4 执行脚本函数

-------------------------------------大厅消息-------------------------------------------

local MsgHallBaseTimeMin = 1 * 1000;
local MsgHallBaseTimeMax = 5 * 1000;

-- 进入房间;
local MsgEnterRoomMin =  5 * 1000;
local MsgEnterRoomMax =  10 * 1000;


regster_event.OnEvent = function( eventID, ID )
 
	-- 检测消息发送时间;	
	-- CreateTimer( ID , 12 , "event_player" , "CkeckSendMsgTime" );
	-- 进入房间;
	CreateTimer( ID , math.random( MsgEnterRoomMin , MsgEnterRoomMax ) , "event_player" , "EnterGame" );
	-- 请求刷新玩家信息;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "SyncPlayerInfo" );
	-- 请求游戏币排行榜（前十名）;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "MoneyRanking" );
	-- 添加金钱;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "PlayerAddMoney" );
	-- 绑定Facebook;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "BindFacebook" );
	-- 领取奖励;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "GetReward" );
	-- 请求改名字;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "PlayerRename" );
	-- 请求其他玩家详细信息;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "ReqOtherPlayerInfo" );
	-- 请求自己详细信息;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "ReqSelfPlayerInfo" );
	-- 请求其他玩家统计数据;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "ReqPlayerKPI" );
	-- 更新个性签名;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "UpdateDynamicMsg" );
	-- 修改头像;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_player" , "ReHeadPortrait" );
	-- 检验校验码绑定手机号;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_common" , "BindMobileNumberCheck" );
	-- 跑马灯喊话;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_common" , "ChatPaoMaDeng" );
	-- 获取 Send Money Limit;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_common" , "GetSendMoneyLimit" );
	-- 请求比赛奖池;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_common" , "RequestPrizePool" );
	-- 请求自己的排行数据;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_common" , "GetRankingMyData" );
	-- 请求比赛参赛人数;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_common" , "SynchRoomRankPlayerNum" );
	-- 请求比赛数据;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_common" , "GetChampionship" );
	-- Ranking Room Top;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_common" , "RankingRoomTop" );
	-- 发送普通邮件;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_mail" , "RequestSendCommmonMail" );
	-- 请求邮件数据;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_mail" , "RequestMailData" );
	-- 请求系统邮件奖励;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_mail" , "RequestSystemMailReward" );
	-- 请求普通邮件奖励;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_mail" , "RequestCommonMailReward" );
	-- 请求删除普通邮件;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_mail" , "RequestDeleteCommonMail" );
	-- 请求删除系统邮件;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_mail" , "RequestDeleteSystemMail" );
	-- 请求查看普通邮件;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_mail" , "RequestLookCommonMail" );
	-- 请求邮件状态;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_mail" , "CheckMailState" );
	-- 请求同步好友列表;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "SynchFriendList" );
	-- 请求同步好友申请列表;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "SynchApplyList" );
	-- 添加屏蔽列表;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "AddBlackList" );
	-- 同步屏蔽列表;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "SyncBlackList" );
	-- 移除屏蔽列表;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "DeleteBlackList" );
	-- 好友申请;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "AddFriendApply" );
	-- 好友添加;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "AddFriend" );
	-- 删除好友;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "DeleteFriend" );
	-- 删除好友申请;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "DeleteApplyFriend" );
	-- 请求好友详细信息;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "RequestFriendDetail" );
	-- 请求申请好友详细信息;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "RequestApplyDetail" );
	-- 请求奖励好友;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "RequestRewardFriend" );
	-- 推荐好友;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "RequestRecommendFriend" );
	-- 搜索PID;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "SearchPID" );
	-- 好友私聊;
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_friend" , "PrivateChat" );
	-- 大转盘;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_roulette" , "PullRouletteMoney" );
	-- 转倍率;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_roulette" , "PullRouletteRate" );
	-- 美金转倍率;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_roulette" , "PullRouletteRateRMB" );
	-- 获取转盘奖励;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_roulette" , "RouletteGetMoney" );
	-- 请求商店信息;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_shop" , "RequestShopInfo" );
	-- 请求购买Money;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_shop" , "RequestBuyMoney" );
	-- 大厅看广告领取奖励;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_ads" , "HallAdsDrawAward" );
	-- 房间看广告领取奖励;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_ads" , "RoomAdsDrawAward" );
	-- 请求同步成就信息;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_achievement" , "SynchAchievementData" );
	-- 请求同步完成成就信息;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_achievement" , "SynchCompleteAchievementData" );
	-- 请求领取成就奖励;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_achievement" , "DrawAchievementReward" );
	-- 请求同步统计信息;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_achievement" , "SynchStatisticsData" );
	-- 请求同步统计信息;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_achievement" , "RestoreScoreData" );
	-- 请求同步任务信息;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_achievement" , "SynchMissionData" );
	-- 请求同步道具信息;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_item" , "SynchItemData" );
	-- 使用道具;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_item" , "UseItem" );
	-- 出售道具;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_item" , "SellItem" );
	-- 购买商城道具;	
	CreateTimer( ID , math.random( MsgHallBaseTimeMin , MsgHallBaseTimeMax ) , "event_item" , "StoreBuyItem" );
	
end




