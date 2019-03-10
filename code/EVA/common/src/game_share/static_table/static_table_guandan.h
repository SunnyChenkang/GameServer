#ifndef GAME_SHARE_STATIC_TABLE_GUANDAN_H
#define GAME_SHARE_STATIC_TABLE_GUANDAN_H

#include "static_tabel_struct.h"
// 掼蛋状态时间;
struct GuanDanStateTime
{
    uint32 WaitTime;           // 等待时间;
    uint32 WaitTimeOut;        // 等待超时时间;
    uint32 StartTime;          // 开始时间;
    uint32 CheckStartTime;     // 检查开始时间;
    uint32 BankerTime;         // 标记庄家时间;
    uint32 BrandTime;          // 发送手牌时间;
    uint32 SendGiftTime;       // 进贡时间;
    uint32 RecvGiftTime;       // 回贡时间;
    uint32 SendGiftFinishTime; // 进贡完成时间;
    uint32 RecvGiftFinishTime; // 回贡完成时间;
    uint32 ActionTime;         // 自由活动时间;
    uint32 OutCardTime;        // 出牌时间;
    uint32 ShowDwonTime;       // 游戏开始结算时间;
    uint32 EndTime;            // 退出游戏（显示大结算）时间
    uint32 RelieveTime;        // 解散房间时间
    uint32 AutoCardTime;       // 自动出牌时间
    uint32 TrustTime;          // 进入托管时间
    uint32 AutoSendGiftTime;   // 自动进贡时间
    uint32 AutoPassCardTime;   // 自动过牌时间
    uint32 MSGGameMaxTime;     // 智力运动会游戏最大时间，超过这个时间游戏会结束
    uint32 MSGRoleMachineTime; // 智力运动会，玩家托管进入挂机状态时间，如果有一个玩家进入这个状态，游戏结束，该玩家不加分

    GuanDanStateTime( void )
    {
        memset( this , 0 , sizeof( GuanDanStateTime ) );
    }
};

// 抗贡条件;
struct GuanDanResistInfo
{
    uint32 CardValue;
    uint32 CardCount;
    GuanDanResistInfo( void )
    {
        memset( this , 0 , sizeof( GuanDanResistInfo ) );
    }
};

// 完成奖励;
struct GuanDanRewardRole
{
    uint32 GameCount;
    uint32 RewardMoney;
    uint32 RewardRmb;
    std::vector< ItemEntity > RewardItem;
    GuanDanRewardRole( void )
        : GameCount( 0 )
        , RewardMoney( 0 )
        , RewardRmb( 0 )
    {
        RewardItem.clear();
    }
};

// 掼蛋配牌
struct GuanDanCardPool 
{
    std::vector< std::vector<uint8> > HandCardPool;		// 手牌列表，一共有四个，如果不是四个认为非法

    GuanDanCardPool( void )
    {
        ResetData();
    }

    void ResetData( void )
    {
        HandCardPool.clear();
    }

    // 转换，策划填写的牌不按CardList中的值
    uint8 SwitchToCardValue( NLMISC::CSString& );

    // 加载配置
    bool LoadCardConfig( void );

    // 判断是否是合法的配置
    bool IsValidConfig( void ) const;
};

// 降级配置
struct GuanDanReduceSeries
{
    uint32 ReduceSeries;

    GuanDanReduceSeries()
    {
        memset( this , 0 , sizeof( GuanDanReduceSeries ) );
    }
};

// 状态执行次数;
struct GuandanStateCount
{
    int CheckStartGame;
    int CheckShowDownEochGame;
    int CheckGameOverEochGame;
    
    GuandanStateCount( void )
        : CheckStartGame( 0 )
        , CheckShowDownEochGame( 0 )
        , CheckGameOverEochGame( 0 )
    {

    }
};


class CGuanDanConfig : public NLMISC::CSingleton<CGuanDanConfig>
{
public:
     CGuanDanConfig( void );
    ~CGuanDanConfig( void );

    //   重置数据;
    void ResetData( void );
    //   加载表;
    bool LoadConfig( void );

    //   获取状态运行时间;
    const GuanDanStateTime&  GetStateTime( void ) const  { return mGuanDanStateTime; }
    //   获取抗贡信息;
    const GuanDanResistInfo& GetResistInfo( void ) const { return mGuanDanResistInfo; }
    //   获取十连奖励;
    const GuanDanRewardRole& GetRewardRole( void ) const { return mGuanDanRewardRole; }

    const GuanDanCardPool& GetGuanDanCardPool( void )    { return mGuanDanCardPool; }

    const GuandanStateCount& GetStateCount()             { return mGuandanStateCount;}
    //   获取降级信息
    const GuanDanReduceSeries& GetReduceSeries( void )   { return mGuandanReduceSeries; }

    //   获取大师分

private:
    GuanDanStateTime        mGuanDanStateTime;
    GuanDanResistInfo       mGuanDanResistInfo;
    GuanDanRewardRole       mGuanDanRewardRole;
    GuanDanCardPool         mGuanDanCardPool;
    GuandanStateCount       mGuandanStateCount;
    GuanDanReduceSeries     mGuandanReduceSeries;
};

#define GuanDanConfig  CGuanDanConfig::instance()

#endif // GAME_SHARE_STATIC_TABLE_GUANDAN_H;