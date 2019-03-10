#ifndef GAME_SHARE_STATIC_TABLE_MAHJONG_H
#define GAME_SHARE_STATIC_TABLE_MAHJONG_H

#include <game_share/game_def.h>

// 玩家状态基础时间;
struct StateTimeBase
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

    StateTimeBase( void )
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

// 南京麻将状态时间;
struct MahJongNanJingStateTime : public StateTimeBase
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

    MahJongNanJingStateTime()
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

//  南京麻将房间配置;
struct MahJongRoomData
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
    MahJongRoomData( void ) : FlowerNum( 0 )
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

// 南京软花配置;
struct MahJongMildFlowerScore
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
    MahJongMildFlowerScore( void ) : RateValue( 0 )
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
        memset( this , 0 , sizeof( MahJongMildFlowerScore ) );
    }
};

// 胡牌积分;
struct MahJongHuScore
{
    uint32 FlowerValue;
    std::vector<uint> FlowerList;
    MahJongHuScore( void ) : FlowerValue( 0 )
    {
        FlowerList.clear();
        FlowerList.resize( 3 );
    }
};

// 开杠积分;
struct MahJongKaiGangScore
{
    uint32 MingGangScore;
    uint32 AnGangScore;
    uint32 FlowerGangScore;
    uint32 HuiPiMBarScore;
    uint32 HuiPiABarScore;
	uint32 HuiABarScore;
	uint32 HuiMBarScore;
    MahJongKaiGangScore( void )
    {
        memset( this , 0 , sizeof( MahJongKaiGangScore ) );
    }
};

// 其它积分;
struct MahJongOtherScoreData
{
    uint32 Param1;
    uint32 Param2;
    MahJongOtherScoreData( void )
    {
        memset( this , 0 , sizeof( MahJongOtherScoreData ) );
    }
};

// 罚款积分;
struct MahJongAmerceScore
{
    uint OutCardScore;
    uint WithCardScore;
    uint SeriesCardScore;
    MahJongAmerceScore( void )
    {
        memset( this , 0 , sizeof( MahJongAmerceScore ) );
    }
};

// 花数段;
struct FlowerSubsection
{
    uint        ID;
    uint        FlowerNum;
    DEF::MONEY  MinMoney;
    DEF::MONEY  MaxMoney;
    FlowerSubsection( void )
    {
        memset( this , 0 , sizeof( FlowerSubsection ) );
    }
};

// 创建房间消耗道具;
struct CreatePrivateConsumeItem
{
    uint32              ID;
    uint32              GameCount;
    uint32              ConsumeItemNum;
    DEF::TEMPLATE_ID    GoldItemID;
    DEF::TEMPLATE_ID    SilverItemID;
    uint32              RatioValue;
    uint32              AllIntegral;
    uint32              OwnerIntegral;
    CreatePrivateConsumeItem( void )
    {
        memset( this , 0 , sizeof( CreatePrivateConsumeItem ) );
    }

    DEF::TEMPLATE_ID GetConsumeItemID( TGameConsumePay Kind )
    {
        return ( Kind == TGC_GOLD ) ? GoldItemID : SilverItemID;
    }
};

// 外包数据;
struct PakcCardScore
{
    int Score;
};

struct WinIntegral
{
    uint32 Integral;
};

// 状态执行次数;
struct MahJongStateCount
{
	int CheckStartGame;
    int CheckShowDownEochGame;
    int CheckGameOverEochGame;

    MahJongStateCount( void )
        : CheckStartGame( 0 )
        , CheckShowDownEochGame( 0 )
        , CheckGameOverEochGame( 0 )
    {

    }
};

struct MahJongCardPool
{
    std::vector< std::vector<uint8> > HandCardPool;
    std::vector< uint8 >              CardPool;
    MahJongCardPool( void )
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

class MahJongConfig : public NLMISC::CSingleton<MahJongConfig>
{
public:
    MahJongConfig( void );
   ~MahJongConfig( void );

    //   重置数据;
    void ResetData( void );
    //   加载表;
    bool LoadConfig( void );
    //   加载麻将牌型;
    bool LoadMahJongPool( void );
    //   加载花数段;
    bool LoadFlowerSubsection( void );

    ///                            获取花数段;
    uint                           GetFlowerSubsection( DEF::MONEY );
    ///                            获取最小花;
    uint                           GetMinFlowerMoney( void );
    ///                            获取房间数据;
    MahJongRoomData*               GetMahJongRoomData( std::string );
    ///                            获取麻将奖池积分;
    MahJongCardPool&               GetMahJongCardPool( void ) { return mNanJingCardPool; }
    ///                            罚款花数;
    MahJongAmerceScore*            GetMahJongAmerceScore( TGameRoomKind Kind );
    ///                            软花;
    MahJongMildFlowerScore*        GetMildFlowerScore( TGameRoomKind Kind );
    ///                            杠花;
    MahJongKaiGangScore*           GetMahJongKaiGangScore( TGameRoomKind Kind );
    ///                            获取南京麻将状态时间;
    MahJongNanJingStateTime*       GetMahJongNanJingStateTime( TGameRoomKind Kind );
    ///                            获取麻将其它积分;
    MahJongOtherScoreData*         GetMahJongOtherScore( TGameRoomKind Kind );
    ///                            胡牌积分;
    std::map<uint,MahJongHuScore>& GetHuScoreData( void ) { return mMahJongHuData; }
    ///                            获取创建私人房消耗数量;
    //CreatePrivateConsumeItem*      GetCreateConsumeItem( uint );
    ///                            包牌积分;
    PakcCardScore&                 GetPackCardScore( void ) { return m_PackCardScore; }
    ///                            状态执行次数;
    MahJongStateCount&             GetStateCount( void )    { return m_MahJongStateCount; }
    ///                            大赢家加积分;
    WinIntegral&                   GetWinIntegral( void ) { return m_WinIntegral; }
private:
    MahJongCardPool         mNanJingCardPool;
    std::map<std::string,MahJongRoomData>               mMahJongRoomData;
    std::map<uint,MahJongHuScore >                      mMahJongHuData;
    std::vector<FlowerSubsection>                       mFlowerSubsection;
    std::map<TGameRoomKind , MahJongAmerceScore  >      m_MahJongAmerceScore;
    std::map<TGameRoomKind , MahJongKaiGangScore >      m_MahJongKaiGangScore;
    std::map<TGameRoomKind , MahJongMildFlowerScore>    m_MahJongMildFlowerScore;
    std::map<TGameRoomKind , MahJongNanJingStateTime >  m_MahJongStateTime;
    std::map<TGameRoomKind , MahJongOtherScoreData   >  m_MahJongOtherScore;
    //std::map<uint,CreatePrivateConsumeItem>             m_CreatePrivateConsumeItem;
    PakcCardScore                                       m_PackCardScore;
    MahJongStateCount                                   m_MahJongStateCount;
    WinIntegral                                         m_WinIntegral;
};

#define MahJongData            MahJongConfig::instance()
#define MahJongRoom(rhs)       MahJongData.GetMahJongRoomData( rhs )
#define MahJongAmerce( rhs )   MahJongData.GetMahJongAmerceScore( rhs )
#define MahJongMildFlower(rhs) MahJongData.GetMildFlowerScore( rhs )
#define MahJongGang( rhs )     MahJongData.GetMahJongKaiGangScore( rhs )
#define MahJongCardPoolData    MahJongData.GetMahJongCardPool()
#define MahJongFlower(rhs)     MahJongData.GetFlowerSubsection(rhs)
#define MahJongStateTime(rhs)  MahJongData.GetMahJongNanJingStateTime(rhs)
#define MahJongOtherScore(rhs) MahJongData.GetMahJongOtherScore(rhs)

#endif //GAME_SHARE_STATIC_TABLE_MAHJONG_H;