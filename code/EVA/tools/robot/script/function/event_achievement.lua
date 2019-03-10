event_achievement = {}


-- 请求同步成就信息;
event_achievement.SynchAchievementData = function(id)
	SynchAchievementData( id );
end

-- 请求同步完成成就信息;
event_achievement.SynchCompleteAchievementData = function(id)
	SynchCompleteAchievementData(id);
end

-- 请求领取成就奖励;
event_achievement.DrawAchievementReward = function(id)
	DrawAchievementReward(id);
end

-- 请求同步统计信息;
event_achievement.SynchStatisticsData = function(id)
	SynchStatisticsData(id);
end

-- 请求同步统计信息;
event_achievement.SynchMissionData = function(id)
	SynchMissionData(id);
end

-- 请求同步统计信息;
event_achievement.RestoreScoreData = function(id)
	RestoreScoreData(id);
end