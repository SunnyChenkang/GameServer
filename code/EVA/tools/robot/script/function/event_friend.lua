event_friend = {}

local RFRandomMoneyTab = {
	[0] = 50,
	[1] = 100,
	[2] = 500,
	[3] = 1000,
	[4] = 5000
}  

-- 请求同步好友列表;
event_friend.SynchFriendList = function(id)	
	SynchFriendList(id);
end

-- 请求同步好友申请列表;
event_friend.SynchApplyList = function(id)
	SynchApplyList(id);
end

-- 同步屏蔽列表;
event_friend.SyncBlackList = function(id)
	SyncBlackList(id);
end

-- 好友申请;
event_friend.AddFriendApply = function(id)
	AddFriendApply(id);
end

-- 好友添加;
event_friend.AddFriend = function(id)
	AddFriend(id);
end

-- 删除好友;
event_friend.DeleteFriend = function(id)
	DeleteFriend(id);
end

-- 删除好友申请;
event_friend.DeleteApplyFriend = function(id)
	DeleteApplyFriend(id);
end

-- 请求好友详细信息;
event_friend.RequestFriendDetail = function(id)
	RequestFriendDetail(id);
end

-- 请求申请好友详细信息;
event_friend.RequestApplyDetail = function(id)
	RequestApplyDetail(id);
end

-- 请求奖励好友;
event_friend.RequestRewardFriend = function(id)
	-- local rand_index  = math.random(1);
	-- local rand_money = RFRandomMoneyTab[rand_index];
	RequestRewardFriend(id,1);
end

-- 推荐好友;
event_friend.RequestRecommendFriend = function(id)
	RequestRecommendFriend(id);
end

-- 好友邀请;
event_friend.InviteFriend = function(id)
	InviteFriend(id);
end

-- 好友私聊;
event_friend.PrivateChat = function(id)
	PrivateChat(id);
end

-- 好友私聊;
event_friend.SearchPID = function(id)
	SearchPID(id);
end

-- 移除屏蔽列表;
event_friend.DeleteBlackList = function(id)
	DeleteBlackList(id);
end

-- 添加屏蔽列表;
event_friend.AddBlackList = function(id)
	AddBlackList(id);
end