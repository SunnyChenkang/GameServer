event_blackjack = {}

local PourNumTab = {
	[0] = 50,
	[1] = 100,
	[2] = 500
}  

-- 请求下注;
event_blackjack.BlackJackAddPour = function(id)
	local rand_index  = math.random(0,2);
	local rand_count = math.random(1,5);
	local rand_pour = PourNumTab[rand_index];
	BlackJackAddPour( id, rand_count , rand_pour );
end

-- 请求要牌;
event_blackjack.BlackJackAskCard = function(id)
	BlackJackAskCard(id);
end

-- 请求分牌;
event_blackjack.BlackJackSplitCard = function(id)
	BlackJackSplitCard(id);
end

-- 请求停牌;
event_blackjack.BlackJackStandCard = function(id)
	BlackJackStandCard(id);
end

-- 购买保险;
event_blackjack.BlackJackBuySurrender = function(id)
	BlackJackBuySurrender(id);
end

-- 跳过保险;
event_blackjack.BlackJackSkipSurrender = function(id)
	BlackJackSkipSurrender(id);
end

-- 双倍;
event_blackjack.BlackJackDoubleCard = function(id)
	BlackJackDoubleCard(id);
end

-- 清除下注;
event_blackjack.BlackJackClearPour = function(id)
	BlackJackClearPour(id);
end

-- 牌桌上打赏;
event_blackjack.GiveTips = function(id)
	GiveTips(id);
end

-- 请求同局其它玩家详细信息;
event_blackjack.RoomPlayerInfo = function(id)
	RoomPlayerInfo(id);
end

-- 好友邀请;
event_blackjack.InviteFriend = function(id)
	InviteFriend(id);
end

-- 重置赌注(Bet, Bet*2, Betall);
event_blackjack.BlackJackResetPour = function(id)

	local rand_index  = math.random(0,2);
	local rand_pour = PourNumTab[rand_index];
	BlackJackResetPour( id , rand_pour );
end

