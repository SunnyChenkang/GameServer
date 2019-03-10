event_texaspker = {}

-- 玩家跟注;
event_texaspker.CallPour = function(id)
	CallPour(id);
end

-- 玩家加注;
event_texaspker.RaisePour = function(id)
	RaisePour(id);
end

-- 玩家弃牌;
event_texaspker.FoldCard = function(id)
	FoldCard(id);
end

-- 玩家让牌;
event_texaspker.CheckCard = function(id)
    CheckCard(id);
end

-- 重置筹码;
event_texaspker.ResetCoins = function(id)
	ResetCoins(id);
end

-- 返回游戏;
event_texaspker.GoBackGame = function(id)
	GoBackGame(id);
end

-- 德州竞技场报名;
event_texaspker.TPChallApplyGame = function(id)
    TPChallApplyGame(id);
end

-- 德州竞技场取消报名;
event_texaspker.TPChallCancelApplyGame = function(id)
    TPChallCancelApplyGame(id);
end

-- 德州竞技场房间信息;
event_texaspker.TPChallRoomData = function(id)
    TPChallRoomData(id);
end

-- 德州竞技场请求退出;
event_texaspker.TPChallRequestQuit = function(id)
    TPChallRequestQuit(id);
end
