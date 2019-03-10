event_item = {}


-- 请求同步道具数据;
event_item.SynchItemData = function(id)	
	SynchItemData(id);
end

-- 使用道具;
event_item.UseItem = function(id)	
	UseItem(id);
end

-- 出售道具;
event_item.SellItem = function(id)	
	SellItem(id);
end

-- 商城购买道具;
event_item.StoreBuyItem = function(id)	
	StoreBuyItem(id);
end