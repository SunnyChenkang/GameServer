#ifndef recv_logic_h__
#define recv_logic_h__
#include <nel/net/message.h>
#include <nel/net/buf_net_base.h>
#include <nel/net/callback_net_base.h>
#include <nel/misc/random.h>

class CConnect;
class CClient;

typedef void (*SystemHandle)( NLNET::CMessage& );

class RecvLogic
{
public:
    typedef std::map< std::string , SystemHandle > HandleTable;

    RecvLogic( CConnect* );
    ~RecvLogic( void );

    // 处理消息;
    void HandleMessage( NLNET::CMessage& );

private:

    // 处理错误消息;
    void HandleCommonError( NLNET::CMessage& );

    // 处理登陆消息;
    void HandleLogin( NLNET::CMessage& );
    // 处理创建角色;
    void HandleCreatePlayer( NLNET::CMessage& );
    // 处理玩家信息;
    void HandlePlayerInfo( NLNET::CMessage& );
    // 处理房间数据;
    void HandleBlackJackRoomInfo( NLNET::CMessage& );
    // 处理离开房间;
    void HandleLeaveRoom( NLNET::CMessage& );
    // 处理刷新玩家信息;
    void HandleSyncPlayerInfo( NLNET::CMessage& );
    // 处理游戏币排行榜;
    void HandleMoneyTanking( NLNET::CMessage& );
    // 处理广播下注;
    void HandleBlackJackAddPour( NLNET::CMessage& );
    // 处理广播要牌;
    void HandleBlackJackAskForCatds( NLNET::CMessage& );
    // 处理广播分牌;
    void HandleBlackJackSplitCard( NLNET::CMessage& ); 
    // 处理广播玩家信息;
    void HandleBroadcastPlyInfo( NLNET::CMessage& );
    // 处理添加金钱;
    void HandleAddMoney( NLNET::CMessage& );
    // 处理减少金钱;
    void HandleSubMoney( NLNET::CMessage& );
    // 处理领取奖励;
    void HandleGetReward( NLNET::CMessage& );
    // 处理比赛数据;
    void HandleChampionship( NLNET::CMessage& );
    // 处理比赛奖池;
    void HandlePrizePool( NLNET::CMessage& );
    // 处理Ranking Room Top;
    void HandleRankingRoomTop( NLNET::CMessage& );
    // 处理自己的排行榜数据;
    void HandleRankingMyData( NLNET::CMessage& );
    // 处理收到普通邮件;
    void HandleReceiveCommonMail( NLNET::CMessage& );
    // 处理请求邮件返回数据;
    void HandleRecviveRequestMail( NLNET::CMessage& );
    // 处理领取系统邮件奖励;
    void HandleSystemMailReward( NLNET::CMessage& );
    // 处理领取普通有奖奖励;
    void HandleCommonMailReward( NLNET::CMessage& );
    // 处理删除普通邮件;
    void HandleDeleteCommonMail( NLNET::CMessage& );
    // 处理删除系统邮件;
    void HandleDeleteSystemMail( NLNET::CMessage& );
    // 处理查看普通邮件;
    void HandleLookCommonMail( NLNET::CMessage& );
    // 处理好友列表;
    void HandleSynchFriendList( NLNET::CMessage& );
    // 处理好友申请列表;
    void HandleSynchApplyList( NLNET::CMessage& );
    // 处理添加好友;
    void HandleAddFriend( NLNET::CMessage& );
    // 处理删除好友;
    void HandleDeleteFriend( NLNET::CMessage& );
    // 处理删除好友申请;
    void HandleDeleteApplyFriend( NLNET::CMessage& );
    // 处理好友详细信息;
    void HandleFriendDetail( NLNET::CMessage& );
    // 处理申请好友详细信息;
    void HandleApplyDetail( NLNET::CMessage& );
    // 处理奖励好友;
    void HandleRewardFriend( NLNET::CMessage& );
    // 处理聊天;
    void HandleChatRoom( NLNET::CMessage& );
    // 处理牌桌内打赏;
    void HandleGiveTip( NLNET::CMessage& );
    // 处理同局玩家详细信息;
    void HandleRoomPlayerInfo( NLNET::CMessage& );
    // 返回玩家统计数据;
    void HandlePlayerStatisticData( NLNET::CMessage& );
    // 处理邀请好友;
    void HandleInviteFriend( NLNET::CMessage& );
    // 处理绑定Facebook;
    void HandleBindFacebook( NLNET::CMessage& );
    // 处理大转盘;
    void HandlePullRouletteMoney( NLNET::CMessage& );
    // 处理转倍率;
    void HandlePullRouletteRate( NLNET::CMessage& );
    // 处理美金转倍率;
    void HandlePullRouletteRateRMB( NLNET::CMessage& );
    // 处理转盘奖励;
    void HandleRouletteGetMoney( NLNET::CMessage& );
    // 处理商店信息;
    void HandleShopInfo( NLNET::CMessage& );
    // 处理商店购买金币;
    void HandleBuyMoney( NLNET::CMessage& );
    // 处理修改名字;
    void HandlePlayerRename( NLNET::CMessage& );
    // 处理其他玩家详细信息;
    void HandleOtherReqPlayerInfo( NLNET::CMessage& );
    // 处理自己详细信息;
    void HandleSelfReqPlayerInfo( NLNET::CMessage& );
    // 处理其他玩家统计信息;
    void HandleReqPlayerKPI( NLNET::CMessage& );
    // 处理大厅看广告领取奖励;
    void HandleHallAdsDrawAward( NLNET::CMessage& );
    // 处理房间看广告领取奖励;
    void HandleRoomAdsDrawAward( NLNET::CMessage& );
    // 处理德州跟注;
    void HandleCallPour( NLNET::CMessage& );
    // 处理德州加注;
    void HandleRaisePour( NLNET::CMessage& );
    // 处理德州弃牌;
    void HandleFoldCard( NLNET::CMessage& );
    // 处理德州让牌;
    void HandleCheckCard( NLNET::CMessage& );
    // 处理德州充值筹码;
    void HandleResetCoins( NLNET::CMessage& );
    // 处理德州返回游戏;
    void HandleGoBackGame( NLNET::CMessage& );
    // 处理老虎机拉杆;
    void HandleSlotsSpin( NLNET::CMessage& );
    // 处理邮件查看状态;
    void HandleCheckMailState( NLNET::CMessage& );
    // 处理查看比赛参赛人数;
    void HandleSynchRoomRankPlayerNum( NLNET::CMessage& );
    // 处理成就信息;
    void HandleSynchAchievementData( NLNET::CMessage& );
    // 处理已完成成就信息;
    void HandleSynchCompleteAchievementData( NLNET::CMessage& );
    // 处理请求领取成就奖励;
    void HandleDrawAchievementReward( NLNET::CMessage& );
    // 处理21点重新下注;
    void HandleBlackJackResetPour( NLNET::CMessage& );
    // 处理老虎机小游戏;
    void HandleSlotsBonusGameSelect( NLNET::CMessage& );
    // 处理推荐好友;
    void HandleRecommendFriend( NLNET::CMessage& );
    // 进入德州房间广播消息;
    void HandleTexasPokersBroadCastGameInfo( NLNET::CMessage& );
    // Slots进入房间，广播房间消息;
    void HandleSlotsBroadCastGameInfo( NLNET::CMessage& );
    // 处理同步南京麻将游戏信息;
    void HandleMahjongGameInfo( NLNET::CMessage& );
    // 处理南京麻将出牌;
    void HandleMahjongOutCard( NLNET::CMessage& );
    // 处理南京麻将结算;
    void HandleMahjongShowDown( NLNET::CMessage& );
    // 处理同步道具数据;
    void HandleSynchItemData( NLNET::CMessage& );
    // 处理使用道具;
    void HandleUseItem( NLNET::CMessage& );
    // 处理出售道具;
    void HandleSellItem( NLNET::CMessage& );
    // 处理商城购买道具;
    void HandleStoreBuyItem( NLNET::CMessage& );
    // 同步屏蔽列表;
    void HandleSynchBlackList( NLNET::CMessage& );
    // 处理添加屏蔽列表;
    void HandleAddBlackList( NLNET::CMessage& );
    // 处理移除屏蔽列表;
    void HandleDeleteBlackList( NLNET::CMessage& );
    // 处理同步统计信息;
    void HandleSynchStatisticsData( NLNET::CMessage& );
    // 处理任务奖励;
    void HandleMissionReward( NLNET::CMessage& );

private:
    HandleTable m_HandleFun;
    CConnect*   m_Connect;
    NLMISC::CRandom m_Random;
};


#endif // recv_logic_h__