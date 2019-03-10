#include "recv_logic.h"
#include "send_logic.h"
#include "../CClient.h"
#include "../CClientMgr.h"
#include "../CRobotHelper.h"
#include <server_share/script_mgr.h>
#include <game_share/proto_msg/mail_pro.pb.h>
#include <game_share/proto_msg/friend_pro.pb.h>
#include <game_share/proto_msg/msg_texaspoker.pb.h>
#include <game_share/proto_msg/msg_blackjack.pb.h>
#include <game_share/proto_msg/msg_slots.pb.h>
#include <game_share/static_table/static_table_mgr.h>
#include <game_share/proto_msg/msg_mahjong.pb.h>

RecvLogic::RecvLogic( CConnect* rhs )
    : m_Connect( rhs )
{
    m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
}

RecvLogic::~RecvLogic( void )
{

}

void RecvLogic::HandleMessage( NLNET::CMessage& Message )
{
    if( PLAYER_ERROR == Message.getName() ) {

        HandleCommonError( Message );       // 错误处理;
    }
    else if ( LOGIN == Message.getName() ) {

        HandleLogin( Message );             // 处理登陆;
    }
    else if ( PLAYER_NULL == Message.getName() ) {

        HandleCreatePlayer( Message);       // 创建玩家;
    }
    else if ( PLAYER_SYNCLOGINPLAYER == Message.getName() ) {

        HandlePlayerInfo( Message );        // 处理玩家基础信息;
    }
    else if ( PLAYER_BLACKJACKROOMINFO == Message.getName() ) {

        HandleBlackJackRoomInfo( Message );        // 处理所有玩家以及房间数据;
    }
    else if ( PLAYER_LEAVE_ROOM == Message.getName() ) {

        HandleLeaveRoom( Message );         // 处理离开房间;
    }
    else if ( PLAYER_SYNCPLAYERINFO == Message.getName() ) {

        HandlePlayerInfo( Message );        // 处理请求同步玩家信息;
    }
    else if ( PLAYER_RANKINGMONEYOP10 == Message.getName() ) {

        HandleMoneyTanking( Message );      // 处理Ranking Money Top 10;
    }
    else if ( PLAYER_BLACKJACKADDPOUR == Message.getName() ) {

        HandleBlackJackAddPour( Message );  // 处理广播下注;
    }
    else if ( PLAYER_BLACKJACKASKCARD == Message.getName() ) {
        
        HandleBlackJackAskForCatds( Message ); // 处理广播要牌;
    }
    else if ( PLAYER_BLACKJACKSPLITCARD == Message.getName() ) {

        HandleBlackJackSplitCard( Message );  // 处理广播分牌;
    }
    else if ( PLAYER_BROADCAST_PLY_INFO == Message.getName() ) {

        HandleBroadcastPlyInfo( Message );
    }
    else if ( PLAYER_ADDMONEY == Message.getName() ) {

        HandleAddMoney( Message );
    }
    else if ( PLAYER_SUBMONEY == Message.getName() ) {

        HandleSubMoney( Message );
    }
    else if ( PLAYER_GETREWARD == Message.getName() ) {

        HandleGetReward( Message );
    }
    else if ( PLAYER_GETCHAMPIONSHIP == Message.getName() ) {

        HandleChampionship( Message );
    }
    else if ( PLAYER_REQUESTPRIZEPOOL == Message.getName() ) {

        HandlePrizePool( Message );
    }
    else if ( PLAYER_RANKINGROOMTOP == Message.getName() ) {

        HandleRankingRoomTop( Message );
    }
    else if ( PLAYER_RANKINGMYDATA == Message.getName() ) {

        HandleRankingMyData( Message );
    }
    else if ( PLAYER_RECEIVECOMMONMAIL == Message.getName() ) {
        
        HandleReceiveCommonMail( Message );
    }
    else if ( PLAYER_REQUESTMAILDATA == Message.getName() ) {

        HandleRecviveRequestMail( Message );
    }
    else if ( PLAYER_SYSTEM_REWARD == Message.getName() ) {

        HandleSystemMailReward( Message );
    }
    else if ( PLAYER_COMMON_REWARD == Message.getName() ) {

        HandleCommonMailReward( Message );
    }
    else if ( PLAYER_DELETE_COMMONMAIL == Message.getName() ) {

        HandleDeleteCommonMail( Message );
    }
    else if (PLAYER_DELETE_SYSTEMMAIL == Message.getName() ) {

        HandleDeleteSystemMail( Message );
    }
    else if ( PLAYER_LOOK_COMMONMAIL == Message.getName() ) {

        HandleLookCommonMail( Message );
    }
    else if ( PLAYER_SYNCHFRIENDLIST == Message.getName() ) {

        HandleSynchFriendList( Message );
    }
    else if ( PLAYER_SYNCHAPPLYLIST == Message.getName() ) {

        HandleSynchApplyList( Message );
    }
    else if ( PLAYER_ADDFRIEND == Message.getName() ) {

        HandleAddFriend( Message );
    }
    else if ( PLAYER_DELETEFRIEND == Message.getName() ) {

        HandleDeleteFriend( Message );
    }
    else if ( PLAYER_DELETEAPPLYFRIEND == Message.getName() ) {

        HandleDeleteApplyFriend( Message );
    }
    else if ( PLAYER_FRIENDDETAIL == Message.getName() ) {

        HandleFriendDetail( Message );
    }
    else if ( PLAYER_APPLYDETAIL == Message.getName() ) {

        HandleApplyDetail( Message );
    }
    else if ( PLAYER_REWARDFRIEND == Message.getName() ) {

        HandleRewardFriend( Message );
    }
    else if ( PLAYER_CHAT_ROOM == Message.getName() ) {

        HandleChatRoom( Message );
    }
    else if ( PLAYER_RKPI == Message.getName() ) {

        HandlePlayerStatisticData( Message );
    }
    else if ( PLAYER_GIVETIP == Message.getName() ) {

        HandleGiveTip( Message );
    }
    else if ( PLAYER_ROOMPLAYERINFO == Message.getName() ) {

        HandleRoomPlayerInfo( Message );
    }
    else if ( PLAYER_INVITEFRIEND == Message.getName() ) {

        HandleInviteFriend( Message );
    }
    else if ( PLAYER_BIND_FACEBOOK == Message.getName() ) {

        HandleBindFacebook( Message );
    }
    else if ( PLAYER_PULLROULETTEMONEY == Message.getName() ) {

        HandlePullRouletteMoney( Message );
    }
    else if ( PLAYER_PULLROULETTERATE == Message.getName() ) {

        HandlePullRouletteRate( Message );
    }
    else if ( PLAYER_PULLROULETTERATERMB == Message.getName() ) {

        HandlePullRouletteRateRMB( Message );
    }
    else if ( PLAYER_ROULETTEGETMONEY == Message.getName() ) {

        HandleRouletteGetMoney( Message );
    }
    else if ( PLAYER_REQUESTSHOPINFO == Message.getName() ) {

        HandleShopInfo( Message );
    }
    else if ( PLAYER_SHOPBUYMONEY == Message.getName() ) {

        HandleBuyMoney( Message );
    }
    else if ( PLAYER_REQUESTRENAME == Message.getName() ) {

        HandlePlayerRename( Message );
    }
    else if ( PLAYER_REQOTHERPLAYERINFO == Message.getName() ) {

        HandleOtherReqPlayerInfo( Message );
    }
    else if ( PLAYER_REQSELFPLAYERINFO == Message.getName() ) {

        HandleSelfReqPlayerInfo( Message );
    }
    else if ( PLAYER_REQPLAYERKPI == Message.getName() ) {

        HandleReqPlayerKPI( Message );
    }
    else if ( PLAYER_HALLADSDRAWAWARD == Message.getName() ) {

        HandleHallAdsDrawAward( Message );
    }
    else if ( PLAYER_ROOMADSDRAWAWARD == Message.getName() ) {

        HandleRoomAdsDrawAward( Message );
    }
    else if ( PLAYER_TP_CALLPOUR == Message.getName() ) {

        HandleCallPour( Message );
    }
    else if ( PLAYER_TP_RAISEPOUR == Message.getName() ) {

        HandleRaisePour( Message );
    }
    else if ( PLAYER_TP_FOLDCARD == Message.getName() ) {

        HandleFoldCard( Message );
    }
    else if ( PLAYER_TP_CHECKCARD == Message.getName() ) {

        HandleCheckCard( Message );
    }
    else if ( PLAYER_TP_RESETCOINS == Message.getName() ) {

        HandleResetCoins( Message );
    }
    else if ( PLAYER_GOBACKGAME == Message.getName() ) {

        HandleGoBackGame( Message );
    }
    else if ( PLAYER_SLOTSSPIN == Message.getName() ) {

        HandleSlotsSpin( Message );
    }
    else if ( PLAYER_CHECKMAILSTATE == Message.getName() ) {

        HandleCheckMailState( Message );
    }
    else if ( PLAYER_RANKPLAYERNUM == Message.getName() ) {

        HandleSynchRoomRankPlayerNum( Message );
    }
    else if ( PLAYER_SYNCHACHIEVEMENT == Message.getName() ) {

        HandleSynchAchievementData( Message );
    }
    else if ( PLAYER_SYNCHCOMACHIEVEMENT == Message.getName() ) {

        HandleSynchCompleteAchievementData( Message );
    }
    else if ( PLAYER_ACHIEVEMENTDRAWREWARD == Message.getName() ) {

        HandleDrawAchievementReward( Message );
    }
    else if ( PLAYER_BLACKJACKRESETPOUR == Message.getName() ) {

        HandleBlackJackResetPour( Message );
    }
    else if ( PLAYER_SLOTSBONUSGAMESELECT == Message.getName() ) {

        HandleSlotsBonusGameSelect( Message );
    }
    else if ( PLAYER_RECOMMENDFRIEND == Message.getName() ) {

        HandleRecommendFriend( Message );
    }
    else if ( PLAYER_BROAD_JOINTEXASPOKER == Message.getName() ) {

        HandleTexasPokersBroadCastGameInfo( Message );
    }
    else if ( PLAYER_SLOTSBROADCASTGAMEINFO == Message.getName() ) {

        HandleSlotsBroadCastGameInfo( Message );
    }
    else if ( PLAYER_MAHJONGGAMEINFO == Message.getName() ) {

        HandleMahjongGameInfo( Message );
    }
    else if ( PLAYER_MAHJONGOUTCARD == Message.getName() ) {

        HandleMahjongOutCard( Message );
    }
    else if ( PLAYER_MAHJONGSHOWDOWN == Message.getName() )	{

        HandleMahjongShowDown( Message );
    }
    else if ( PLAYER_SYNCHITEMDATA == Message.getName() ) {

        HandleSynchItemData( Message );
    }
    else if ( PLAYER_USE_ITEM == Message.getName() ) {

        HandleUseItem( Message );
    }
    else if ( PLAYER_SELL_ITEM == Message.getName() ) {

        HandleSellItem( Message );
    }
    else if ( PLAYER_STOREBUYITEM == Message.getName() ) {

        HandleStoreBuyItem( Message );
    }
    else if ( PLAYER_SYNCBLACKLIST == Message.getName() ) {

        HandleSynchBlackList( Message );
    }
    else if ( PLAYER_ADDBLACKLIST == Message.getName() ) {

        HandleAddBlackList( Message );
    }
    else if ( PLAYER_DELETEBLACKLIST == Message.getName() ) {

        HandleDeleteBlackList( Message );
    }
    else if ( PLAYER_SYNCHSTATISTICSDATA == Message.getName() ) {

        HandleSynchStatisticsData( Message );
    }
    else if ( PLAYER_MISSIONREWARD == Message.getName() ) {

        HandleMissionReward( Message );
    }
}

void RecvLogic::HandleCommonError( NLNET::CMessage& Message )
{
    DEF::ERROR_TYPE ErrorID;
    Message.serial( ErrorID );

    switch( ErrorID )
    {
        //case CHANGE_NAME_REPEAT:
        //    {
        //        HandleCreatePlayer(Message);
        //        break;
        //    }

    default:
        break;
    }

    nldebug( " handle common error [ %d ] " , ErrorID );
}

void RecvLogic::HandleLogin( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    uint32 svrTime = 0;
    MsgSetSession Session;
    Message.serial( svrTime );
    Message.serial( &Session );

    // 设置状态;
    pClient->SetClientState( client_state_loadplayer );
    // 设置会话ID;
    m_Connect->set_session( Session.session() );
    // 
    m_Connect->SetRandomSeed( Session.seed() );
    // 请求角色基础信息;
    m_Connect->GetSendLogic()->SendPlayerInfo();
    // 关联到管理器;
    ClientMgr->InsertClient( ( uint32 )Session.session() , pClient );

    //nldebug( " recv login succeed [ %s ] " , pClient->GetName().c_str() );
}

void RecvLogic::HandleCreatePlayer( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    // 设置状态;
    pClient->SetClientState( client_state_createrole );
    // 请求创建角色;
    m_Connect->GetSendLogic()->SendCreateRole();
}

void RecvLogic::HandlePlayerInfo( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
     
    MsgPlayerInfo           MsgOut;
     
    Message.serial( &MsgOut );

    // 保存玩家基础数据;
    pClient->OnSavePlayerInfo( MsgOut );
    // 设置客户端状态;
    pClient->SetClientState( client_state_online );

    // 先清除身上所有计时器;
    pClient->ClearTimer();
    pClient->SetMountLuaType(MountLua_Hall);
    ScriptMgr.on_event( ROBOT_EVENT_REGSTEREVENT , LuaParams( (uint32)m_Connect->get_session() ) );

    //nlinfo( "recv player base info succeed [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleBlackJackRoomInfo( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgBlackjackRoomInfo MsgOut;

    Message.serial(&MsgOut);

    for ( int i = 0; i < MsgOut.player_list().size(); ++i )
    {
        if ( pClient->GetRoleID() != MsgOut.player_list(i).player_base().pid() ) { continue; }

        if ( pClient->IsInBlackJack() ) { continue; }

        // 先清除身上所有计时器;
        pClient->ClearTimer();
        pClient->SetMountLuaType(MountLua_BlackJack);
        ScriptMgr.on_event( ROBOT_EVENT_BLACKJACK , LuaParams( (uint32)m_Connect->get_session() ) );
    }
    //nlinfo( "recv black jack room info [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleLeaveRoom( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    pClient->SetRoomType("Hall");
    // 先清除身上所有计时器;
    pClient->ClearTimer();
    pClient->SetMountLuaType(MountLua_Hall);
    ScriptMgr.on_event( ROBOT_EVENT_REGSTEREVENT , LuaParams( (uint32)m_Connect->get_session() ) );
    //nlinfo( "recv leave room [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSyncPlayerInfo( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgPlayerInfo           MsgOut;

    Message.serial( &MsgOut );

    // 保存玩家基础数据;
    pClient->OnSavePlayerInfo( MsgOut );

    //nlinfo( "recv sync player info [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleMoneyTanking( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv ranking money top 10[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleBlackJackAddPour( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv broad cast black jack add pour[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleBlackJackAskForCatds( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv broad cast black jack ask card [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleBlackJackSplitCard( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv broad cast black jack split card [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleBroadcastPlyInfo( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv broad cast black jack player info [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleAddMoney( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgInt MsgOut;

    Message.serial( &MsgOut );

   pClient->AddMoney( MsgOut.value() );

   //nlinfo( "recv add money [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSubMoney( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt MsgOut;
    Message.serial( &MsgOut );

    pClient->AddMoney( -MsgOut.value() );

    //nlinfo( "recv sub money [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleGetReward( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgReward MsgOut;
    Message.serial( &MsgOut );

    pClient->AddMoney( MsgOut.money() );

    //nlinfo( "recv get reward [ %s ]" , pClient->GetName().c_str() );

}

void RecvLogic::HandleChampionship( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv champion ship [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandlePrizePool( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv prize pool [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleRankingRoomTop( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv ranking room top [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleRankingMyData( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv my ranking data [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleReceiveCommonMail( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgCommonMail MsgOut;
    Message.serial( &MsgOut );

    pClient->OnSaveCommonMail(MsgOut);

    //nlinfo( "recv receive common mail [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleRecviveRequestMail( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgMailList MsgOut;
    Message.serial( &MsgOut );

    pClient->RecviveRequestMail( MsgOut );

    //nlinfo( "recv receive request mail [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSystemMailReward( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgGainReward MsgOut;

    Message.serial(&MsgOut);

    pClient->RemoveSystemMail( MsgOut.idx() );
    if ( MsgOut.msg_item().size() > 0 )
    {
        pClient->OnUpdateMailItem( MsgOut );
    }
    if ( MsgOut.money() > 0 )
    {
        pClient->AddMoney( MsgOut.money() );
    }
    if ( MsgOut.rmb() > 0 )
    {
        pClient->AddRMB( MsgOut.rmb() );
    }
    //nlinfo( "recv system mail reward [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleCommonMailReward( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgGainReward MsgOut;

    Message.serial(&MsgOut);

    pClient->RemoveSystemMail( MsgOut.idx() );
    if ( MsgOut.msg_item().size() > 0 )
    {
        pClient->OnUpdateMailItem( MsgOut );
    }
    if ( MsgOut.money() > 0 )
    {
        pClient->AddMoney( MsgOut.money() );
    }
    if ( MsgOut.rmb() > 0 )
    {
        pClient->AddRMB( MsgOut.rmb() );
    }

    //nlinfo( "recv common mail reward [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleDeleteCommonMail( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    DEF::MAIL_ID unMailID = 0;
    Message.serial(unMailID);

    pClient->RemoveCommonMail( unMailID );

    //nlinfo( "recv delete common mail [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleDeleteSystemMail( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    uint unMailID = 0;
    Message.serial(unMailID);

    pClient->RemoveSystemMail( unMailID );

    //nlinfo( "recv system mail [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleLookCommonMail( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv look common mail [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSynchFriendList( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgFriendList MsgOut;
    Message.serial( &MsgOut );

    pClient->OnSaveFriendList( MsgOut );

    //nlinfo( "recv synch friend list [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSynchApplyList( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgFriendList MsgOut;
    Message.serial( &MsgOut );

    pClient->OnSaveApplyFriendList( MsgOut );

    //nlinfo( "recv synch apply list [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleAddFriend( NLNET::CMessage& Message)
{
    DYNAMIC_CLIENT( m_Connect );

    MsgFriendBase MsgOut;
    Message.serial( &MsgOut );

    pClient->AddFriend( MsgOut );

    //nlinfo( "recv add friend [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleDeleteFriend( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    DEF::PID pid = 0;
    Message.serial(pid);

    pClient->DeleteFriend( pid );

    //nlinfo( "recv delete friend [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleDeleteApplyFriend( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    DEF::PID pid = 0;
    Message.serial(pid);

    pClient->DeleteApplyFriend( pid );

    //nlinfo( "recv delete friend [ %s ]" , pClient->GetName().c_str() );

}

void RecvLogic::HandleFriendDetail( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv friend detail [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleApplyDetail( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv apply friend detail [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleRewardFriend( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv reward friend [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleChatRoom( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv room chat [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandlePlayerStatisticData( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv statistic data [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleGiveTip( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv give tip [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleRoomPlayerInfo( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv room player info [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleInviteFriend( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgFriendDetail MsgOut;
    Message.serial( &MsgOut );

    MsgInt SendPack;
    SendPack.set_value( MsgOut.roleid() );

    m_Connect->SendMsg( PLAYER_INVITEENTER, &SendPack );

    //nlinfo( "recv invite friend [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleBindFacebook( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv bind face book [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandlePullRouletteMoney( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv pull roulette money[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandlePullRouletteRate( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv pull roulette rate[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandlePullRouletteRateRMB( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv pull roulette rate rmb[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleRouletteGetMoney( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv roulette get money[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleShopInfo( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv shop info[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleBuyMoney( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv buy money[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandlePlayerRename( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv player rename[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleOtherReqPlayerInfo( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv the other player detailed info [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSelfReqPlayerInfo( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv the other player detailed info [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleReqPlayerKPI( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv the other player statistical info[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleHallAdsDrawAward( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv hall ads draw award[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleRoomAdsDrawAward( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv room ads draw award[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleCallPour( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv call pour[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleRaisePour( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv raise pour[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleFoldCard( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv fold card[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleCheckCard( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv check card[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleResetCoins( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv reset coins[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleGoBackGame( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv texas poker goback game[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSlotsSpin( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv slots spin[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleCheckMailState( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv check mail state[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSynchRoomRankPlayerNum( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv synch room rank players num[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSynchAchievementData( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgAchievementList MsgOut;
    Message.serial( &MsgOut );

    pClient->OnSaveAchievementInfo( MsgOut );

    //nlinfo( "recv add friend [ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSynchCompleteAchievementData( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv synch complete achievement data[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleDrawAchievementReward( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv synch complete achievement data[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleBlackJackResetPour( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv blackjack reset pour[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleSlotsBonusGameSelect( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv slots bonus game select[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleRecommendFriend( NLNET::CMessage& )
{
    DYNAMIC_CLIENT( m_Connect );

    //nlinfo( "recv recommend friend[ %s ]" , pClient->GetName().c_str() );
}

void RecvLogic::HandleTexasPokersBroadCastGameInfo( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgTexasPokerRoomInfo MsgOut;

    Message.serial(&MsgOut);

    for ( int i = 0; i < MsgOut.player_list().size(); ++i )
    {
        if ( pClient->GetRoleID() != MsgOut.player_list(i).player_info().pid() ) { continue; }

        if ( pClient->IsInTexasPoker() ) { continue; }

        // 先清除身上所有计时器;
        pClient->ClearTimer();
        pClient->SetMountLuaType(MountLua_TexasPoker);
        ScriptMgr.on_event( ROBOT_EVENT_TEXASPOKER , LuaParams( (uint32)m_Connect->get_session() ) );
    }
}

void RecvLogic::HandleSlotsBroadCastGameInfo( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgSlotsRoomInfo MsgOut;

    Message.serial(&MsgOut);

    for ( int i = 0; i < MsgOut.player_list().size(); ++i )
    {
        if ( pClient->GetRoleID() != MsgOut.player_list(i).player_base().pid() ) { continue; }

        if ( pClient->IsInSlots() ) { continue; }

        // 先清除身上所有计时器;
        pClient->ClearTimer();
        pClient->SetMountLuaType(MountLua_Slots);
        ScriptMgr.on_event( ROBOT_EVENT_SLOT , LuaParams( (uint32)m_Connect->get_session() ) );
    }

}

void RecvLogic::HandleMahjongGameInfo( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgMahJongRoom MsgOut;

    Message.serial(&MsgOut);

	pClient->OnSaveHandCard( MsgOut );

    for ( int i = 0; i < MsgOut.player_list().size(); ++i )
    {
        if ( pClient->GetRoleID() != MsgOut.player_list(i).player_info().pid() ) { continue; }

        if ( pClient->IsInMahJong() ) { continue; }

        // 先清除身上所有计时器;
        pClient->ClearTimer();
        pClient->SetMountLuaType(MountLua_MahJong);
        ScriptMgr.on_event( ROBOT_EVENT_MAHJONG , LuaParams( (uint32)m_Connect->get_session() ) );
    }
}

void RecvLogic::HandleMahjongOutCard( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgOutCard MsgOut;

    Message.serial(&MsgOut);

    pClient->RemoveHandCard( MsgOut.card() );
}

void RecvLogic::HandleMahjongShowDown( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );

    pClient->GetSendLogic()->MahjongStartReady(); 
}


void RecvLogic::HandleSynchItemData( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgItemCont MsgOut;
    Message.serial(&MsgOut);

    pClient->OnSavePlayerItem( MsgOut );
}

void RecvLogic::HandleUseItem( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgUseItemUpdate MsgOut;
    Message.serial(&MsgOut);

    pClient->OnUpdateUseItem( MsgOut );
}

void RecvLogic::HandleSellItem( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgSellItemUpdate MsgOut;
    Message.serial(&MsgOut);

    pClient->OnUpdateSellItem( MsgOut );
}

void RecvLogic::HandleStoreBuyItem( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgStoreBuyItemInfo MsgOut;
    Message.serial(&MsgOut);

    pClient->OnUpdateBuyItem( MsgOut );
}

void RecvLogic::HandleSynchBlackList( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgBlackListCont MsgOut;
    Message.serial(&MsgOut);

    pClient->OnSaveBlackList( MsgOut );
}

void RecvLogic::HandleAddBlackList( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
}

void RecvLogic::HandleDeleteBlackList( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgInt MsgOut;
    Message.serial(&MsgOut);

    pClient->DeleteBlackList( MsgOut.value() );
}

void RecvLogic::HandleSynchStatisticsData( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgStatisticsList MsgOut;
    Message.serial(&MsgOut);

    pClient->OnSaveStatisticsData( MsgOut );
}

void RecvLogic::HandleMissionReward( NLNET::CMessage& Message )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgMissionReward MsgOut;
    Message.serial(&MsgOut);

    pClient->AddMoney( MsgOut.money() );
    pClient->AddRMB( MsgOut.rmb() );
    pClient->OnUpdateMissionRewardItem( MsgOut );
    pClient->MissionReward( MsgOut );
}

