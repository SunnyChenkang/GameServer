/********************************************************************
	created:	2017/09/19
	created:	19:9:2017   19:39
	file base:	static_table_ddzpool
	file ext:	h
	author:		WHJ
	
	purpose:	斗地主配置
*********************************************************************/
#ifndef GAME_SHARE_DDZPOOL_H
#define GAME_SHARE_DDZPOOL_H

#include "static_tabel_struct.h"

// 斗地主配牌
class DDZPoolConFig : public NLMISC::CSingleton<DDZPoolConFig>
{
public:

	DDZPoolConFig( void )
	{
		ResetData();
	}
    ~DDZPoolConFig(){}

	void ResetData( void )
	{
		m_HandCardPool.clear();
	}
    typedef std::vector< std::vector<uint8> > TCardPools;
	// 转换，策划填写的牌不按CardList中的值
	uint8 SwitchToCardValue( NLMISC::CSString& );

	// 加载配置
	bool LoadCardConfig( void );

	// 判断是否是合法的配置
	bool IsValidConfig( void ) const;

    // 获取手牌
    TCardPools& GetCard(){ return m_HandCardPool;}

private:
    TCardPools m_HandCardPool;		// 手牌列表，
};

#define DDZPoolConfig  DDZPoolConFig::instance()

#endif // GAME_SHARE_DDZPOOL_H;