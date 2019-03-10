event_player = {}

-- 添加数据
event_player.SendGMCommon = function(id) 
	local ramVal = math.random(0,1000);
	SendGMCommon(id , ramVal);
end


-- 进入房间;
event_player.EnterGame = function(id)	
	EnterGame(id);
end

-- 离开房间;
event_player.LeaveRoom = function(id) 
	LeaveRoom(id);
end

-- 检测消息发送时间;
event_player.CkeckSendMsgTime = function(id)
	CkeckSendMsgTime(id);
end

-- 请求同步玩家信息;
event_player.SyncPlayerInfo = function(id)
	SyncPlayerInfo(id);
end

-- 请求游戏币排行榜（前十名）;
event_player.MoneyRanking = function(id)
	MoneyRanking(id);
end

-- 添加金钱;
event_player.PlayerAddMoney = function(id)
	PlayerAddMoney(id);
end

-- 减少金钱;
-- event_player.PlayerSubMoney = function(id)
	-- PlayerSubMoney(id);
-- end

-- 领取奖励;
event_player.GetReward = function(id)
	GetReward(id);
end

event_player.BindFacebook = function(id)
	BindFacebook(id);
end

-- 请求改名字;
event_player.PlayerRename = function(id)
	PlayerRename(id);
end

-- 请求其他玩家详细信息;
event_player.ReqOtherPlayerInfo = function(id)
	ReqOtherPlayerInfo(id);
end

-- 请求其他玩家详细信息;
event_player.ReqSelfPlayerInfo = function(id)
	ReqSelfPlayerInfo(id);
end

-- 请求其他玩家统计数据;
event_player.ReqPlayerKPI = function(id)
	ReqPlayerKPI(id);
end

-- 更新个性签名;
event_player.UpdateDynamicMsg = function(id)
	UpdateDynamicMsg(id);
end

-- 修改头像;
event_player.ReHeadPortrait = function(id)
	ReHeadPortrait(id,math.random(0,6));
end


