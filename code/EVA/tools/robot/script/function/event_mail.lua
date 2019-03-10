event_mail = {}


-- 请求发送普通邮件;
event_mail.RequestSendCommmonMail = function(id)	
	RequestSendCommmonMail(id, math.random(1,10) , math.random(1,100) );
end

-- 请求邮件数据;
event_mail.RequestMailData = function(id)	
	RequestMailData(id);
end

-- 请求系统邮件奖励;
event_mail.RequestSystemMailReward = function(id)
	RequestSystemMailReward(id);
end

-- 请求普通邮件奖励;
event_mail.RequestCommonMailReward = function(id)
	RequestCommonMailReward(id);
end

-- 请求删除普通邮件;
event_mail.RequestDeleteCommonMail = function(id)
	RequestDeleteCommonMail(id);
end

-- 请求删除系统邮件;
event_mail.RequestDeleteSystemMail = function(id)
	RequestDeleteSystemMail(id);
end

--请求查看普通邮件;
event_mail.RequestLookCommonMail = function(id)
	RequestLookCommonMail(id);
end 

-- 请求邮件状态;
event_mail.CheckMailState = function(id)
	CheckMailState(id);
end