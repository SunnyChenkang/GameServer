event_mahjong = {}

local PourNumTab = {
	[0] = 0x00,					--// 没有类型;
	[1] = 0x01,					--// 左吃类型;
	[2] = 0x02,					--// 中吃类型;
	[3] = 0x04,					--// 右吃类型;
	[4] = 0x08,					--// 碰牌类型;
	[5] = 0x10,					--// 补牌类型;
	[6] = 0x20,					--// 明杠牌类型;
	[7] = 0x40,					--// 吃胡类型;
	[8] = 0x80					--// 验证权限;
}  

-- 用户选择权限;
event_mahjong.MahjongUserOperate = function(id)
	MahjongUserOperate( id, math.random(0,8) );
end

-- 南京麻将出牌;
event_mahjong.MahjongOutCard = function(id)
    MahjongOutCard(id);
end

-- 南京麻将用户开始准备;
event_mahjong.MahjongStartReady = function(id)
    MahjongStartReady(id);
end

-- 南京麻将用户取消准备;
event_mahjong.MahjongCancelReady = function(id)
    MahjongCancelReady(id);
end