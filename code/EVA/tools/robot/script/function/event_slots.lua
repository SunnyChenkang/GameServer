event_slots = {}

-- 老虎机拉杆;
event_slots.SlotsSpin = function(id)
	SlotsSpin(id);
end

-- 老虎机小游戏;
event_slots.SlotsBonusGameSelect = function(id)
    SlotsBonusGameSelect(id);
end

-- 请求Slots奖池数据;
event_slots.GetSlotsJackpots = function(id)
	GetSlotsJackpots(id);
end