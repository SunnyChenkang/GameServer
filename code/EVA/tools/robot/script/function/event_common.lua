event_common = {}


-- 请求比赛奖池;
event_common.RequestPrizePool = function(id)
	RequestPrizePool(id);
end

-- 请求比赛奖池;
event_common.GetRankingMyData = function(id)
	GetRankingMyData(id);
end

-- 请求比赛房间人数; 
event_common.SynchRoomRankPlayerNum = function(id)
	SynchRoomRankPlayerNum(id);
end

-- 请求比赛数据;
event_common.GetChampionship = function(id)
	GetChampionship(id);
end

-- Ranking Room Top;
event_common.RankingRoomTop = function(id)
	RankingRoomTop(id);
end

-- chat room;
event_common.ChatRoom = function(id)
	ChatRoom(id,math.random(1,100))
end

-- 请求查看小猪存钱罐信息;
event_common.ViewPigInfo = function(id)
	ViewPigInfo(id);
end

-- 检验校验码绑定手机号;
event_player.BindMobileNumberCheck = function(id)
	BindMobileNumberCheck(id);
end

-- 跑马灯喊话;
event_player.ChatPaoMaDeng = function(id)
	ChatPaoMaDeng(id);
end

-- 获取 Send Money Limit;
event_player.GetSendMoneyLimit = function(id)
	GetSendMoneyLimit(id);
end
