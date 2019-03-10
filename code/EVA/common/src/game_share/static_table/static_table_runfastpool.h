#ifndef GAME_SHARE_RUNFASTPOOL_H
#define GAME_SHARE_RUNFASTPOOL_H

#include "static_tabel_struct.h"

// 跑得快配牌
class RunFastPoolConFig : public NLMISC::CSingleton<RunFastPoolConFig>
{
public:

	RunFastPoolConFig( void )
	{
		ResetData();
	}
    ~RunFastPoolConFig(){}

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

#define RunFastPoolConfig  RunFastPoolConFig::instance()

#endif // GAME_SHARE_RUNFASTPOOL_H;