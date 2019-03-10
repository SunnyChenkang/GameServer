event_roulette = {}

--   "PRM";  // 大转盘
event_roulette.PullRouletteMoney = function(id)
	PullRouletteMoney(id);
end

--   "PRR";  // 转倍率
event_roulette.PullRouletteRate = function(id)
	PullRouletteRate(id);
end

--   "PRRR"; // 美金转倍率
event_roulette.PullRouletteRateRMB = function(id)
	PullRouletteRateRMB(id);
end

--   "RGM";  // 获取转盘奖励
event_roulette.RouletteGetMoney = function(id)
	RouletteGetMoney(id);
end