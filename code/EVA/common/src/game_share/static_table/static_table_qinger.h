#ifndef GAME_SHARE_STATIC_TABLE_QINGER_H
#define GAME_SHARE_STATIC_TABLE_QINGER_H

#include <game_share/game_def.h>

// 玩家状态基础时间;
struct QingErStateTimeBase
{
    uint32 WaitTime;                  // 等待游戏;
    uint32 WaitTimeOut;               // 等待游戏超时;
    uint32 CheckStartGameTime;        // 检查游戏开始;
    uint32 StartGameTime;             // 开始游戏;
    uint32 ActionTime;                // 玩家自己活动时间;
    uint32 ActionListenTime;          // 玩家听牌操作时间;
    uint32 ActionTrustTime;           // 玩家托管操作时间;
    uint32 ShowDownTime;              // 结算时间;
    uint32 WaitGameOver;              // 游戏结束;

    QingErStateTimeBase( void )
        : StartGameTime ( 0 )
        , CheckStartGameTime( 0 )
        , WaitTime( 0 )
        , WaitTimeOut( 0 )
        , ActionTime ( 0 )
        , ActionListenTime( 0 )
        , ActionTrustTime( 0 )
        , ShowDownTime ( 0 )
        , WaitGameOver( 0 )
    {
    }
};

// 青儿状态时间;
struct QingErStateTime : public QingErStateTimeBase
{
    uint32 CheckTianDiChoiceTime;     // 检查用户权限;
    uint32 HandMendFlowerTime;        // 手牌补花时间;
    uint32 AholdMendFlowerTime;       // 抓牌补花时间;
    uint32 MakeMoundTime;             // 摇色子标记牌墩;
    uint32 MakeBankerTime;            // 摇色子标记庄家时间;
    uint32 FirstBrandTime;            // 发手牌时间;
    uint32 WaitUserChoiceTime;        // 等待玩家操作;
    uint32 WaitSelfChoiceTime;        // 等待自己操作;
    uint32 WaitUserTrustChoiceTime;   // 等待托管玩家操作;
    uint32 WaitSelfTrustChoiceTime;   // 等待托管自己操作;
    uint32 WaitQiangGangChoiceTime;   // 等待用户抢杠胡操作;
    uint32 WaitOutCardTime;           // 等待出牌完成;
    uint32 WaitTouchCardTime;         // 等待碰牌完成;
    uint32 WaitBarCardTime;           // 等待杠牌完成;
    uint32 WaitEatCardTime;           // 等待吃牌完成;
    uint32 WaitAmerceTime;            // 等待罚钱完成;
    uint32 WaitTouchFinishTime;       // 碰牌完成;
    uint32 WaitBarFinishTime;         // 杠牌完成;
    uint32 WaitEatFinishTime;         // 吃牌完成;
    uint32 WaitAmerceFinishTime;      // 罚钱完成;
    uint32 WaitRelieveTime;           // 解散房间;
    uint32 WaitRelieveFinishTime;     // 解散房间完成;
    uint32 WaitZiMoHuTime;            // 自摸胡牌;
    uint32 WaitDianPaoHuTime;         // 点炮胡牌;
    uint32 WaitLiuJuHuTime;           // 流局胡牌;
    uint32 WaitQiangGangHuTime;       // 抢杠胡牌;
    uint32 WaitDaBarKaiHuaHuTime;     // 大杠开花胡牌;
    uint32 WaitPengDuiHuTime;         // 碰对胡牌;
    uint32 WaitZiMoMengTime;          // 自摸梦牌;
    uint32 WaitCathenTime;            // 下注刷新;
    uint32 WaitContract;			  // 承包刷新;
    uint32 WaitAutoOutCardTime;		  // 自動出牌時間;
    uint32 WaitVirtualTime;           // 虚拟牌时间;

    QingErStateTime()
    : CheckTianDiChoiceTime(0)
    , MakeBankerTime( 0 )
    , FirstBrandTime( 0 )
    , WaitUserChoiceTime( 0 )
    , WaitSelfChoiceTime( 0 )
    , WaitUserTrustChoiceTime( 0 )
    , WaitSelfTrustChoiceTime( 0 )
    , WaitQiangGangChoiceTime( 0 )
    , WaitOutCardTime( 0 )
    , WaitTouchCardTime( 0 )
    , WaitBarCardTime( 0 )
    , WaitEatCardTime( 0 )
    , WaitAmerceTime( 0 )
    , WaitTouchFinishTime( 0 )
    , WaitBarFinishTime( 0 )
    , WaitEatFinishTime( 0 )
    , WaitAmerceFinishTime( 0 )
    , WaitRelieveTime( 0 )
    , WaitRelieveFinishTime( 0 )
    , WaitZiMoHuTime( 0 )
    , WaitDianPaoHuTime( 0 )
    , WaitLiuJuHuTime( 0 )
    , WaitQiangGangHuTime( 0 )
    , WaitDaBarKaiHuaHuTime( 0 )
    , WaitPengDuiHuTime( 0 )
    , WaitZiMoMengTime( 0 )
	, WaitContract( 0 )
	, WaitAutoOutCardTime( 0 )
    , WaitVirtualTime( 0 )
    {

    }
};

//  青儿房间配置;
struct QingErRoomData
{
    TGameRoomKind Kind;    // 游戏种类;
    uint32 FlowerNum;        // 胡牌硬花数;
    uint32 DaGangKaiHua;     // 大杠开花;
    uint32 FlowerScoreMoney; // 硬花兑换货币;
    uint32 BaseFlower;       // 底花;
    uint32 BaseScore;        // 底分
    int    WinScore;         // 胜利积分;
    int    LostScore;        // 失败积分;
    int    FlatScore;        // 平积分;
    int    LeiBaoTaCount;    // 垒宝塔次数;
    int    LeiBaoTaScore;    // 垒宝塔积分;
    QingErRoomData( void ) : FlowerNum( 0 )
                            , DaGangKaiHua( 0 )
                            , FlowerScoreMoney( 0 )
                            , BaseFlower( 0 )
                            , WinScore( 0 )
                            , LostScore( 0 )
                            , FlatScore( 0 )
                            , LeiBaoTaCount( 0 )
                            , LeiBaoTaScore( 0 )
                            , BaseScore(0)
                            , Kind( TGD_NORMAL )
    {

    }
};

// 青儿软花配置;
struct QingErMildFlowerScore
{
    uint32 RateValue;
    uint32 SidesPeng;
    uint32 SidesMingGang;
    uint32 SidesAnGang;
    uint32 NormalMingGang;
    uint32 NormalAnGang;
    uint32 QueYiMen;
    uint32 YaDang;
    uint32 DuDiao;
    uint32 HandFengTou;
    QingErMildFlowerScore( void ) : RateValue( 0 )
                                   , SidesPeng( 0 )
                                   , SidesMingGang( 0 )
                                   , SidesAnGang( 0 )
                                   , NormalMingGang( 0 )
                                   , NormalAnGang( 0 )
                                   , QueYiMen( 0 )
                                   , YaDang( 0 )
                                   , DuDiao( 0 )
                                   , HandFengTou( 0 )
    {
        memset( this , 0 , sizeof( QingErMildFlowerScore ) );
    }
};

// 胡牌积分;
struct QingErHuScore
{
    uint32 FlowerValue;
    std::vector<uint> FlowerList;
    QingErHuScore( void ) : FlowerValue( 0 )
    {
        FlowerList.clear();
        FlowerList.resize( 3 );
    }
};

// 测试牌库;
struct QingErTestPool
{
	uint32 TestCardPoolOpen;
	uint32 TestJianZhang;
	std::string PoolCardStr;
	std::vector<uint8> PoolCards;
	QingErTestPool( void ) : TestJianZhang( 0 ) ,TestCardPoolOpen( 0 )
	{
		PoolCards.clear();
	}
};

// 开杠积分;
struct QingErKaiGangScore
{
    uint32 MingGangScore;
    uint32 AnGangScore;
    uint32 FlowerGangScore;
    uint32 HuiPiMBarScore;
    uint32 HuiPiABarScore;
	uint32 HuiABarScore;
	uint32 HuiMBarScore;
    QingErKaiGangScore( void )
    {
        memset( this , 0 , sizeof( QingErKaiGangScore ) );
    }
};

// 其它积分;
struct QingErOtherScoreData
{
    uint32 Param1;
    uint32 Param2;
    QingErOtherScoreData( void )
    {
        memset( this , 0 , sizeof( QingErOtherScoreData ) );
    }
};

// 结算积分;
struct QingErJieSuanScore
{
    uint OutCardScore;
    //std::string ScoreName;
    QingErJieSuanScore( void )
    {
        OutCardScore = 0;
    }
};

// 花数段;
struct QingErFlowerSubsection
{
    uint        ID;
    uint        FlowerNum;
    DEF::MONEY  MinMoney;
    DEF::MONEY  MaxMoney;
    QingErFlowerSubsection( void )
    {
        memset( this , 0 , sizeof( QingErFlowerSubsection ) );
    }
};

// 创建房间消耗道具;
struct QingErCreatePrivateConsumeItem
{
    uint32              ID;
    uint32              GameCount;
    uint32              ConsumeItemNum;
    DEF::TEMPLATE_ID    GoldItemID;
    DEF::TEMPLATE_ID    SilverItemID;
    uint32              RatioValue;
    uint32              AllIntegral;
    uint32              OwnerIntegral;
    QingErCreatePrivateConsumeItem( void )
    {
        memset( this , 0 , sizeof( QingErCreatePrivateConsumeItem ) );
    }

    DEF::TEMPLATE_ID GetConsumeItemID( TGameConsumePay Kind )
    {
        return ( Kind == TGC_GOLD ) ? GoldItemID : SilverItemID;
    }
};

// 外包数据;
struct QingErPakcCardScore
{
    int Score;
};

struct QingErWinIntegral
{
    uint32 Integral;
};

// 状态执行次数;
struct QingErStateCount
{
	int CheckStartGame;
    int CheckShowDownEochGame;
    int CheckGameOverEochGame;

    QingErStateCount( void )
        : CheckStartGame( 0 )
        , CheckShowDownEochGame( 0 )
        , CheckGameOverEochGame( 0 )
    {

    }
};

struct QingErCardPool
{
    std::vector< std::vector<uint8> > HandCardPool;
    std::vector< uint8 >              CardPool;
    QingErCardPool( void )
    {
        ResetData();
    }
    void ResetData( void )
    {
        HandCardPool.clear();
        HandCardPool.resize(4);
        CardPool.clear();
    }
    uint8 SwitchToCard( uint8 Value )
    {
        // 万字牌;
        if ( Value >= 1 && Value <= 9 )     { return Value; }
        // 条子牌;
        if ( Value >= 21 && Value <= 29 )   { return ( Value - 4 ); }
        // 桶字牌;
        if ( Value >= 11 && Value <= 19 )   { return ( Value + 22 ); }
        // 东南西北;
        if ( Value >= 31 && Value <= 34 )   { return ( Value + 18 ); }
        // 中发白;
        if ( Value >= 35 && Value <= 37 )   { return ( Value + 18 ); }
        // 春夏秋冬梅兰竹菊;
        if ( Value >= 41 && Value <= 48 )   { return ( Value + 24 ); }
        return 0;
    }
}; 

class QingErConfig : public NLMISC::CSingleton<QingErConfig>
{
public:
    QingErConfig( void );
   ~QingErConfig( void );

    //   重置数据;
    void ResetData( void );
    //   加载表;
    bool LoadConfig( void );
    //   加载麻将牌型;
    bool LoadQingErPool( void );
    //   加载花数段;
    bool LoadFlowerSubsection( void );

    ///                            获取花数段;
    uint                           GetQEFlowerSubsection( DEF::MONEY );
    ///                            获取最小花;
    uint                           GetMinFlowerMoney( void );
	///                            获取测试牌库数据;
	QingErTestPool&                GetQingErTestPool();
	///                            获取结算分数;
	std::map<uint32 , QingErJieSuanScore >     GetQingErScore();
    ///                            获取麻将奖池积分;
    QingErCardPool&                GetQingErCardPool( void ) { return mQingErCardPool; }
    ///                            软花;
    QingErMildFlowerScore*         GetQEMildFlowerScore( TGameRoomKind Kind );
    ///                            获取青儿状态时间;
    QingErStateTime*               GetQingErStateTime( TGameRoomKind Kind );
    ///                            获取麻将其它积分;
    QingErOtherScoreData*          GetMahJongOtherScore( TGameRoomKind Kind );
    ///                            状态执行次数;
    QingErStateCount&              GetStateCount( void )    { return m_QingErStateCount; }
private:
    QingErCardPool         mQingErCardPool;
    std::vector<QingErFlowerSubsection>                mFlowerSubsection;
    std::map<TGameRoomKind , QingErKaiGangScore >      m_QingErKaiGangScore;
    std::map<TGameRoomKind , QingErStateTime >         m_QingErStateTime;
    QingErStateCount                                   m_QingErStateCount;
	QingErTestPool                                     m_QingErTestPool;
	std::map<uint32 , QingErJieSuanScore >             m_QingErScore;
};

#define QingErData            QingErConfig::instance()
#define QingErMildFlower(rhs) QingErData.GetQEMildFlowerScore( rhs )
#define QingErStateTime(rhs)  QingErData.GetQingErStateTime(rhs)
#define QingErTestPool()      QingErData.GetQingErTestPool()
#define QingErStaticScore()         QingErData.GetQingErScore()


#endif //GAME_SHARE_STATIC_TABLE_QINGER_H;