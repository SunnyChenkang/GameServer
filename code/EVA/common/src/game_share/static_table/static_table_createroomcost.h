/********************************************************************
	created:	2016/12/30
	created:	30:12:2016   13:36
	file base:	static_table_createroomcost
	file ext:	h
	author:		WHJ
	
	purpose:	创建私房消耗表，之前是放到麻将的配置中的，但是现在用的地方比较
				多，所以说单独拿出来了一个xml	
*********************************************************************/
#ifndef GAME_SHARE_STATIC_TABLE_CREATEROOMCOST_H
#define GAME_SHARE_STATIC_TABLE_CREATEROOMCOST_H

#include <game_share/game_def.h>
#include "static_table_mahjong.h"
class CreateRoomCostConfig : public NLMISC::CSingleton<CreateRoomCostConfig>
{
public:
	CreateRoomCostConfig( void );
	~CreateRoomCostConfig( void );
	//   重置数据;
	void ResetData( void );
	//   加载表;
	bool LoadConfig( void );
	///                            获取创建私人房消耗数量;
	CreatePrivateConsumeItem*      GetCreateConsumeItem( uint );


private:
	std::map<uint,CreatePrivateConsumeItem>             m_CreatePrivateConsumeItem;
};

#define CreateRoomCostData CreateRoomCostConfig::instance()

#endif //GAME_SHARE_STATIC_TABLE_CREATEROOMCOST_H;