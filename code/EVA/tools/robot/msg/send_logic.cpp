#include "send_logic.h"
#include <nel/net/message.h>
#include <game_share/game_def.h>
#include <server_share/server_def.h>
#include <game_share/static_table/static_table_mgr.h>
#include <server_share/script_mgr.h>
#include <game_share/proto_msg/mail_pro.pb.h>
#include <game_share/proto_msg/msg_texaspoker.pb.h>
#include <game_share/proto_msg/msg_slots.pb.h>
#include <game_share/proto_msg/msg_blackjack.pb.h>
#include <game_share/define_pro.pb.h>
#include <game_share/proto_msg/msg_mahjong.pb.h>

#include "../CRobotHelper.h"
#include "../CConnect.h"
#include "../CClient.h"
#include "../CClientMgr.h"
#include "../CRobotName.h"
#include "../CCommonLine.h"

using namespace DEF;
using namespace std;
using namespace NLNET;
using namespace NLMISC;

SendLogic::SendLogic( CConnect* rhs )
    : m_Connect( rhs )
{
}

SendLogic::~SendLogic( void )
{
}

void SendLogic::SendLogin( CSString token )
{
    MsgLogin SendPack;
    SendPack.set_token( token );
    m_Connect->SendMsg( LOGIN , &SendPack );
}

void SendLogic::SendPlayerInfo( void )
{
    DYNAMIC_CLIENT( m_Connect )

    m_Connect->SendMsg( PLAYER_INFO );
}

void SendLogic::SendCreateRole( void )
{
    std::string strName = RobotName->GetRandomName();

    // 随机构造名字;
    while( strName.size() < PLAYERNAME_LENGTH_MIN ) {
        strName += RobotName->GetRandomName();
    }

    MsgCreatePlayer SendPack;
    SendPack.set_name(strName.c_str() );
    m_Connect->SendMsg( PLAYER_CREATE , &SendPack );

    nldebug( " send create role succeed [ %s ] " , strName.c_str() );
}

void SendLogic::EnterGame( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgEnterGame SendPack;

    std::map<std::string, RoomConfigXml>::iterator it = StaticTableMgr.GetGameConfig().rooms.begin();

    int dist = std::distance( it , StaticTableMgr.GetGameConfig().rooms.end() );
    if ( dist > 0 )
    {
        std::string strEnterRoomType = Config.getVar( "EnterRoomType" ).asString ();
        if (strEnterRoomType.empty())
        {
            std::string strEnterGameName = Config.getVar( "EnterGameName" ).asString ();
            if ( strEnterGameName.empty() )
            {
                int rand_index = CommonLine->m_Random.rand(dist-1);
                std::advance( it , rand_index );

                pClient->SetRoomType( it->first );
                SendPack.set_room_type( it->first );
            }
            else
            {
                std::vector<std::string> outList;
                StaticTableMgr.GetRoomTypeByGameName(strEnterGameName,outList);

				if(outList.size()<=0) { return; }

                sint32 randomIndex = CommonLine->m_Random.rand() % ( outList.size() - 1 );
                std::string strres = outList[ randomIndex ];
                pClient->SetRoomType( outList[ randomIndex ] );
                SendPack.set_room_type( outList[ randomIndex ] );
            }
        }
        else
        {
            it = StaticTableMgr.GetGameConfig().rooms.find(strEnterRoomType);
            pClient->SetRoomType( strEnterRoomType );
            SendPack.set_room_type( strEnterRoomType );
        }
    }
    m_Connect->SendMsg( PLAYER_ENTER_GAME, &SendPack );
}

void SendLogic::LeaveRoom( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_LEAVE_ROOM );
}

void SendLogic::SyncPlayerInfo( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_SYNCPLAYERINFO );
}

void SendLogic::MoneyRanking( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_RANKINGMONEYOP10 );
}

void SendLogic::BlackJackAddPour( int rand_count, int rand_pour )
{
    DYNAMIC_CLIENT( m_Connect );

    for ( int i = 0; i < rand_count; ++i )
    {
        MsgInt SendPack;
        SendPack.set_value( rand_pour );

        m_Connect->SendMsg( PLAYER_BLACKJACKADDPOUR, &SendPack );
    }
}

void SendLogic::BlackJackAskCard( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgBool SendPack;
    SendPack.set_val( (bool)CommonLine->m_Random.rand(1) );

    m_Connect->SendMsg( PLAYER_BLACKJACKASKCARD, &SendPack );
}

void SendLogic::BlackJackSplitCard( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_BLACKJACKSPLITCARD );
}

void SendLogic::BlackJackStandCard( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgBool SendPack;
    SendPack.set_val( (bool)CommonLine->m_Random.rand(1) );

    m_Connect->SendMsg( PLAYER_BLACKJACKSTANDCARD, &SendPack );
}

void SendLogic::BlackJackBuySurrender( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgBool SendPack;
    SendPack.set_val( (bool)CommonLine->m_Random.rand(1) );

    m_Connect->SendMsg( PLAYER_BLACKJACKBUYSURRENDER, &SendPack );
}

void SendLogic::BlackJackSkipSurrender( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_BLACKJACKSKIPSURRENDER );
}

void SendLogic::BlackJackDoubleCard( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgBool SendPack;
    SendPack.set_val( (bool)CommonLine->m_Random.rand(1) );

    m_Connect->SendMsg( PLAYER_BLACKJACKDOUBLECARD, &SendPack );
}

void SendLogic::BlackJackClearPour( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_BLACKJACKCLEARPOUR );
}

void SendLogic::PlayerAddMoney( void )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgInt SendPack;

    SendPack.set_value( 10000000 );

    m_Connect->SendMsg( PLAYER_ADDMONEY , &SendPack );
}

void SendLogic::PlayerSubMoney( void )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgInt SendPack;

    SendPack.set_value( 1 );

    m_Connect->SendMsg( PLAYER_SUBMONEY , &SendPack );
}

void SendLogic::GetReward( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_GETREWARD );
}

void SendLogic::GetChampionship( void )
{
    DYNAMIC_CLIENT( m_Connect );

    std::vector<std::string> outList;
    StaticTableMgr.GetChallengesRoomType(outList);

    if (outList.size() <= 0) { return; }

    sint32 randomIndex = CommonLine->m_Random.rand() % ( outList.size() - 1 );


    MsgString SendPack;
    SendPack.set_str( outList[ randomIndex ] );

    m_Connect->SendMsg( PLAYER_RANKINGMYDATA, &SendPack );
}

void SendLogic::RequestPrizePool( void )
{
    DYNAMIC_CLIENT( m_Connect );

    std::vector<std::string> outList;
    StaticTableMgr.GetChallengesRoomType(outList);

    if (outList.size() <= 0) { return; }

    sint32 randomIndex = CommonLine->m_Random.rand() % ( outList.size() - 1 );


    MsgString SendPack;
    SendPack.set_str( outList[ randomIndex ] );

    m_Connect->SendMsg( PLAYER_RANKINGMYDATA, &SendPack );
}

void SendLogic::RankingRoomTop( void )
{
    DYNAMIC_CLIENT( m_Connect );

    std::vector<std::string> outList;
    StaticTableMgr.GetChallengesRoomType(outList);
    if (outList.size() <= 0) { return; }

    sint32 randomIndex = CommonLine->m_Random.rand() % ( outList.size() - 1 );

    MsgString SendPack;
    SendPack.set_str( outList[ randomIndex ] );

    m_Connect->SendMsg( PLAYER_RANKINGMYDATA, &SendPack );
}

void SendLogic::GetRankingMyData( void )
{
    DYNAMIC_CLIENT( m_Connect );

    std::vector<std::string> outList;
    StaticTableMgr.GetChallengesRoomType(outList);

    if (outList.size() <= 0) { return; }
    sint32 randomIndex = CommonLine->m_Random.rand() % ( outList.size() - 1 );


    MsgString SendPack;
    SendPack.set_str( outList[ randomIndex ] );

    m_Connect->SendMsg( PLAYER_RANKINGMYDATA, &SendPack );
}

void SendLogic::RequestSendCommmonMail( int rand_title_count , int rand_content_count )
{
    DYNAMIC_CLIENT( m_Connect );

    std::string strTitle   = "";
    std::string strContent = "";

    CClient* pRandomClient = ClientMgr->GetRandomClient();
    if ( NULL == pRandomClient ) {
        return;
    }
    // 标题;
    while ( strTitle.size() < rand_title_count )
    {
        strTitle += RobotName->GetRandomName();
    }
    // 内容;
    while ( strContent.size() < rand_content_count )
    {
        strContent += RobotName->GetRandomName();
    }
    MsgCommonMail SendPack;
    SendPack.set_recvid( pRandomClient->GetRoleID() );
    SendPack.set_title( strTitle );
    SendPack.set_content( strContent );
    DB_RECORD::CRecordItem* pItem = pClient->GetRandomItem();
    if ( pItem != NULL )
    {
        SendPack.set_item_id( pItem->RecordItemData.item_id );
        SendPack.set_item_count( CommonLine->m_Random.rand( pItem->RecordItemData.num ) );
    }

    m_Connect->SendMsg( PLAYER_SENDCOMMMONMAIL, &SendPack );
}

void SendLogic::RequestMailData( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgRequestMail SendPack;

    for( std::map< DEF::MAIL_ID, MailData >::iterator it = pClient->GetCommonMailMap().begin(); 
        it != pClient->GetCommonMailMap().end(); ++it )
    {
        SendPack.add_commonlist( it->first );
    }

    for( std::map< DEF::MAIL_ID, MailData >::iterator it = pClient->GetSystemMailMap().begin(); 
        it != pClient->GetSystemMailMap().end(); ++it )
    {
        SendPack.add_systemlist( it->first );
    }
    m_Connect->SendMsg( PLAYER_REQUESTMAILDATA, &SendPack );

}

void SendLogic::RequestSystemMailReward( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgGainReward SendPack;

    SendPack.set_idx( pClient->OnGetRandomSystemMailID() );

    m_Connect->SendMsg( PLAYER_SYSTEM_REWARD, &SendPack );
}

void SendLogic::RequestCommonMailReward( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgGainReward SendPack;

    SendPack.set_idx( pClient->OnGetRandomCommonMailID() );

    m_Connect->SendMsg( PLAYER_COMMON_REWARD, &SendPack );
}

void SendLogic::RequestDeleteCommonMail( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgDeleteMail SendPack;

    SendPack.set_idx( pClient->OnGetRandomCommonMailID() );

    m_Connect->SendMsg( PLAYER_DELETE_COMMONMAIL, &SendPack );
}

void SendLogic::RequestDeleteSystemMail( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgDeleteMail SendPack;

    SendPack.set_idx( pClient->OnGetRandomSystemMailID() );

    m_Connect->SendMsg( PLAYER_DELETE_SYSTEMMAIL, &SendPack );
}

void SendLogic::RequestLookCommonMail( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgLookMail SendPack;

    SendPack.set_idx( pClient->OnGetRandomCommonMailID() );

    m_Connect->SendMsg( PLAYER_LOOK_COMMONMAIL, &SendPack );
}

void SendLogic::SynchFriendList( void )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgRequestList SendPack;
    SendPack.set_check( pClient->OnGetFriendListNum() );

    m_Connect->SendMsg( PLAYER_SYNCHFRIENDLIST, &SendPack );
}

void SendLogic::SynchApplyList( void )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgRequestList SendPack;
    SendPack.set_check( pClient->OnGetApplyListNum() );

    m_Connect->SendMsg( PLAYER_SYNCHAPPLYLIST, &SendPack );
}

void SendLogic::AddFriendApply( void )
{
    DYNAMIC_CLIENT( m_Connect );

    CClient* pRandomClient = ClientMgr->GetRandomClient();
    if ( NULL == pRandomClient ) {
        return;
    }

    MsgInt SendPack;
    SendPack.set_value( pRandomClient->GetRoleID() );

    m_Connect->SendMsg( PLAYER_ADDFRIENDAPPLY, &SendPack );

}

void SendLogic::AddFriend( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value( pClient->OnGetRandomApplyFriendID() );

    m_Connect->SendMsg( PLAYER_ADDFRIEND, &SendPack );
}

void SendLogic::DeleteFriend( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value( pClient->OnGetRandomFriendID() );

    m_Connect->SendMsg( PLAYER_DELETEFRIEND, &SendPack );
}

void SendLogic::DeleteApplyFriend( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value( pClient->OnGetRandomApplyFriendID() );

    m_Connect->SendMsg( PLAYER_DELETEAPPLYFRIEND, &SendPack );
}

void SendLogic::RequestFriendDetail( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value( pClient->OnGetRandomFriendID() );

    m_Connect->SendMsg( PLAYER_FRIENDDETAIL, &SendPack );
}

void SendLogic::RequestApplyDetail( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value( pClient->OnGetRandomApplyFriendID() );

    m_Connect->SendMsg( PLAYER_APPLYDETAIL, &SendPack );
}

void SendLogic::RequestRewardFriend( int rand_money )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgFriendGift SendPack;
    SendPack.set_roleid( pClient->OnGetRandomFriendID() );
    SendPack.set_money( rand_money );

    m_Connect->SendMsg( PLAYER_REWARDFRIEND, &SendPack );
}

void SendLogic::ChatRoom( int rand_count )
{
    DYNAMIC_CLIENT( m_Connect );

    std::string strText = "";
    while( strText.size() < rand_count ) {
        strText += RobotName->GetRandomName();
    }

    MsgChat SendPack;
    SendPack.set_text(strText);

    m_Connect->SendMsg( PLAYER_CHAT_ROOM, &SendPack );
}

void SendLogic::GiveTips( void )
{
    DYNAMIC_CLIENT( m_Connect );
    CClient* pRandomClient = ClientMgr->GetRandomClient();
    if ( NULL == pRandomClient ) {
        return;
    }

    MsgTip SendPack;
    SendPack.set_src_pid( pClient->GetRoleID() );
    SendPack.set_dec_pid( pRandomClient->GetRoleID() );
    SendPack.set_tip_type( CommonLine->m_Random.rand( 3 ) );

    m_Connect->SendMsg( PLAYER_GIVETIP, &SendPack );
}

void SendLogic::RoomPlayerInfo( void )
{
    DYNAMIC_CLIENT( m_Connect );
    CClient* pRandomClient = ClientMgr->GetRandomClient();
    if ( NULL == pRandomClient ) {
        return;
    }

    MsgInt SendPack;
    SendPack.set_value( pRandomClient->GetRoleID() );

    m_Connect->SendMsg( PLAYER_ROOMPLAYERINFO, &SendPack );
}

void SendLogic::InviteFriend( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value( pClient->OnGetRandomFriendID() );

    m_Connect->SendMsg( PLAYER_INVITEFRIEND, &SendPack );
}

void SendLogic::SendTemplateMail( void )
{
    DYNAMIC_CLIENT( m_Connect );

    std::string str_title   = "";
    std::string str_content = "";
    int rand_title_count = CommonLine->m_Random.rand( 10 );
    int rand_content_count = CommonLine->m_Random.rand( 100 );
    uint32 curr_time = CTime::getSecondsSince1970();
    uint32 past_time = curr_time+(CommonLine->m_Random.rand( 7 ) * DAY_SECONDS );

    // 标题;
    while ( str_title.size() < rand_title_count ) {
        str_title += RobotName->GetRandomName();
    }
    // 内容;
    while ( str_content.size() < rand_content_count ) {
        str_content += RobotName->GetRandomName();
    }

    MsgSystemTemplate SendPack;
    SendPack.set_name( pClient->GetName() );
    SendPack.set_title( str_title );
    SendPack.set_content( str_content );
    SendPack.set_sendtime( curr_time );
    SendPack.set_pasttime( past_time );
    SendPack.set_reward( CommonLine->m_Random.rand( 10 ) * 1000 );

    m_Connect->SendMsg( PLAYER_SENDTEMPLATEMAIL, &SendPack );
}

void SendLogic::BindFacebook( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_BIND_FACEBOOK );
}

void SendLogic::PullRouletteMoney( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_PULLROULETTEMONEY );
}

void SendLogic::PullRouletteRate( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_PULLROULETTERATE );
}

void SendLogic::PullRouletteRateRMB( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_PULLROULETTERATERMB );
}

void SendLogic::RouletteGetMoney( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_ROULETTEGETMONEY );
}

void SendLogic::RequestShopInfo( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_REQUESTSHOPINFO );
}

void SendLogic::RequestBuyMoney( void )
{
}

void SendLogic::PlayerRename( void )
{
    DYNAMIC_CLIENT( m_Connect );

    std::string strName = RobotName->GetRandomName();

    // 随机构造名字;
    while( strName.size() < PLAYERNAME_LENGTH_MIN ) {
        strName += RobotName->GetRandomName();
    }

    MsgString SendPack;
    SendPack.set_str( strName.c_str() );

    m_Connect->SendMsg( PLAYER_REQUESTRENAME, &SendPack );
}

void SendLogic::ReqOtherPlayerInfo( void )
{
    DYNAMIC_CLIENT( m_Connect );

    CClient* pRandomClient = ClientMgr->GetRandomClient();
    if ( NULL == pRandomClient ) {
        return;
    }

    MsgInt SendPack;
    SendPack.set_value( pRandomClient->GetRoleID() );

    m_Connect->SendMsg( PLAYER_REQOTHERPLAYERINFO, &SendPack );
}

void SendLogic::ReqSelfPlayerInfo( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_REQSELFPLAYERINFO );
}

void SendLogic::ReqPlayerKPI( void )
{
    DYNAMIC_CLIENT( m_Connect );

    CClient* pRandomClient = ClientMgr->GetRandomClient();
    if ( NULL == pRandomClient ) {
        return;
    }

    MsgInt SendPack;
    SendPack.set_value( pRandomClient->GetRoleID() );

    m_Connect->SendMsg( PLAYER_REQPLAYERKPI, &SendPack );
}

void SendLogic::HallAdsDrawAward( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_HALLADSDRAWAWARD );
}

void SendLogic::RoomAdsDrawAward( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_ROOMADSDRAWAWARD );
}

void SendLogic::CkeckSendMsgTime( void )
{
    DYNAMIC_CLIENT( m_Connect );
    uint32 curr_time = CTime::getSecondsSince1970();
    if ( curr_time - m_Connect->GetSendMsgLimitTime() > SENDMSGLIMITTIME )
    {
        nlwarning( " limit_time = %d " , curr_time - m_Connect->GetSendMsgLimitTime() );
        PlayerAddMoney();
    }
}

void SendLogic::CallPour( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_TP_CALLPOUR );
}

void SendLogic::RaisePour( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgRaisePour SendPack;
    SendPack.set_roleid( pClient->GetRoleID() );
    SendPack.set_pour( CommonLine->m_Random.rand( 1000 ) );
    m_Connect->SendMsg( PLAYER_TP_RAISEPOUR, &SendPack );
}

void SendLogic::FoldCard( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_TP_FOLDCARD );
}

void SendLogic::CheckCard( void )
{
    DYNAMIC_CLIENT( m_Connect );
    MsgInt SendPack;
    SendPack.set_value( pClient->GetRoleID() );

    m_Connect->SendMsg( PLAYER_TP_CHECKCARD, &SendPack );
}

void SendLogic::ResetCoins( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_TP_RESETCOINS );
}

void SendLogic::GoBackGame( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_GOBACKGAME );
}

void SendLogic::SlotsSpin( void )
{
    DYNAMIC_CLIENT( m_Connect );

    uint32 lines_count = 20;

    SlotsRoomConfigXml* pConfig = StaticTableMgr.GetSlotsRoomConfig( pClient->GetRoomType() );
    if ( NULL != pConfig )
    {
        MachineConfigXml* pMachineConfig = SlotsMachineConfiger.GetMachineConfig(pConfig->use_machine);
        if ( NULL != pMachineConfig )
        {
            SlotsData*  pSlotsData = SlotsMachineConfiger.GetSlotsData( pMachineConfig->data_file );
            if ( NULL != pSlotsData )
            {
                lines_count = pSlotsData->GetWinningLine().size();
            }
        }
    }
    MsgSlotsPull SendPack;
    SendPack.set_bet( CommonLine->m_Random.rand(500) );
    SendPack.set_lines( lines_count );

    m_Connect->SendMsg( PLAYER_SLOTSSPIN, &SendPack );

}

void SendLogic::CheckMailState( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgCheckState SendPack;

    for( std::map< DEF::MAIL_ID, MailData >::iterator it = pClient->GetCommonMailMap().begin(); 
        it != pClient->GetCommonMailMap().end(); ++it )
    {
        SendPack.add_commonlist( it->first );
    }

    for( std::map< DEF::MAIL_ID, MailData >::iterator it = pClient->GetSystemMailMap().begin(); 
        it != pClient->GetSystemMailMap().end(); ++it )
    {
        SendPack.add_systemlist( it->first );
    }
    m_Connect->SendMsg(PLAYER_CHECKMAILSTATE, &SendPack);
}

void SendLogic::SynchRoomRankPlayerNum( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg(PLAYER_RANKPLAYERNUM);
}

void SendLogic::SynchAchievementData( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value( pClient->GetCRC32Achievement());

    m_Connect->SendMsg(PLAYER_SYNCHACHIEVEMENT, &SendPack);
}

void SendLogic::SynchCompleteAchievementData( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg(PLAYER_SYNCHCOMACHIEVEMENT);
}

void SendLogic::DrawAchievementReward( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value(pClient->GetRandomAchievementID());
    m_Connect->SendMsg(PLAYER_ACHIEVEMENTDRAWREWARD, &SendPack);
}

void SendLogic::BlackJackResetPour( int rand_pour )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgBlackJackPourList SendPack;

    MsgPour *pMsgPour = SendPack.add_pour_list();

    pMsgPour->set_pour(rand_pour);
    pMsgPour->set_num(CommonLine->m_Random.rand(5));

    m_Connect->SendMsg(PLAYER_BLACKJACKRESETPOUR, &SendPack);

}

void SendLogic::SlotsBonusGameSelect( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg(PLAYER_SLOTSBONUSGAMESELECT);
}

void SendLogic::RequestRecommendFriend( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg(PLAYER_RECOMMENDFRIEND);
}

void SendLogic::SynchStatisticsData( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg(PLAYER_SYNCHSTATISTICSDATA);
}


void SendLogic::UpdateDynamicMsg( void )
{
    DYNAMIC_CLIENT( m_Connect );

    std::string strDynamicMsg;
    while ( strDynamicMsg.size() < CommonLine->m_Random.rand(DynamicMaxSize) )
    {
        strDynamicMsg += RobotName->GetRandomName();
    }
    MsgString SendPack;
    SendPack.set_str( strDynamicMsg );
    m_Connect->SendMsg(PLAYER_UPDATEDYNAMICMSG,&SendPack);
}

void SendLogic::ReHeadPortrait( int rand_index )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value(rand_index);

    m_Connect->SendMsg(PLAYER_REHEADPORTRAIT,&SendPack);
}

void SendLogic::GetSlotsJackpots( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg(PLAYER_SLOTSJACKPOTS);
}

void SendLogic::TPChallApplyGame( void )
{
    DYNAMIC_CLIENT( m_Connect );

    std::vector<std::string> outList;
    StaticTableMgr.GetChallengesRoomType(outList);

    if (outList.size() <= 0) { return; }
    sint32 randomIndex = CommonLine->m_Random.rand() % ( outList.size() - 1 );

    MsgApplyGame SendPack;
    SendPack.set_room_type( outList[ randomIndex ] );

    m_Connect->SendMsg(PLAYER_TPCHALLAPPLYGAME, &SendPack);
}

void SendLogic::TPChallCancelApplyGame( void )
{
    DYNAMIC_CLIENT( m_Connect );

    std::vector<std::string> outList;
    StaticTableMgr.GetChallengesRoomType(outList);

    if (outList.size() <= 0) { return; }
    sint32 randomIndex = CommonLine->m_Random.rand() % ( outList.size() - 1 );

    MsgCancelApply SendPack;
    SendPack.set_room_type( outList[ randomIndex ] );

    m_Connect->SendMsg(PLAYER_TPCHALLCANCELAPPLYGAME);
}

void SendLogic::TPChallRoomData( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg(PLAYER_TPCHALLROOMDATA);
}

void SendLogic::TPChallRequestQuit( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg(PLAYER_TPCHALLREQUESTQUIT);
}

void SendLogic::PrivateChat( void )
{
    DYNAMIC_CLIENT( m_Connect );

    CClient* pRandomClient = ClientMgr->GetRandomClient();
    if ( NULL == pRandomClient ) {
        return;
    }

    std::string strText = "";
    while( strText.size() < PLAYER_CHAT_LENGTH ) {
        strText += RobotName->GetRandomName();
    }

    MsgChat SendPack;
    SendPack.set_pid( pRandomClient->GetRoleID() );
    SendPack.set_text( strText );

    m_Connect->SendMsg(PLAYER_PRIVATECHAT,&SendPack);
}

void SendLogic::MahjongUserOperate( int rand_index )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgUserOperate SendPack;
    SendPack.set_wik( (TMahJongASK)rand_index );
    m_Connect->SendMsg(PLAYER_MAHJONGUSEROPERATE, &SendPack);
}

void SendLogic::MahjongOutCard( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MahJongCard* pMahJongCard = pClient->GetRandonHandCard();
    if( NULL == pMahJongCard )
        return;

    MsgOutCard SendPack;
    SendPack.set_card( pMahJongCard->card );
    SendPack.set_index( pMahJongCard->value );
    m_Connect->SendMsg(PLAYER_MAHJONGOUTCARD, &SendPack);
}

void SendLogic::MahjongStartReady( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg(PLAYER_MAHJONGSTARTREADY);
}

void SendLogic::MahjongCancelReady( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg(PLAYER_MAHJONGCANCEREADY);
}

void SendLogic::SynchItemData( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgRequestList SendPack;
    SendPack.set_check( pClient->GetCRC32Item() );

    m_Connect->SendMsg(PLAYER_SYNCHITEMDATA, &SendPack);
}

void SendLogic::UseItem( void )
{
    DYNAMIC_CLIENT( m_Connect );

    DB_RECORD::CRecordItem* pItem = pClient->GetRandomItem();
    if ( NULL != pItem )
    {
        MsgUseItem SendPack;
        SendPack.set_item_id( pItem->RecordItemData.item_id );
        SendPack.set_item_count( pItem->RecordItemData.num );
        SendPack.set_use_count( CommonLine->m_Random.rand(pItem->RecordItemData.num) );

        m_Connect->SendMsg(PLAYER_USE_ITEM, &SendPack);
    }
}

void SendLogic::SellItem( void )
{
    DYNAMIC_CLIENT( m_Connect );

    DB_RECORD::CRecordItem* pItem = pClient->GetRandomItem();
    if ( NULL != pItem )
    {
        MsgSellItem SendPack;
        SendPack.set_item_id( pItem->RecordItemData.item_id );
        SendPack.set_item_count( pItem->RecordItemData.num );
        SendPack.set_sell_count( CommonLine->m_Random.rand(pItem->RecordItemData.num) );

        m_Connect->SendMsg(PLAYER_SELL_ITEM, &SendPack);
    }

}

void SendLogic::StoreBuyItem( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgStoreBuyItem SendPack;

    TStaticData::iterator it = StaticTableMgr.m_StoreItemData.begin();

    int dist = std::distance( it , StaticTableMgr.m_StoreItemData.end() );
    if ( dist > 0 )
    {
        int rand_index = CommonLine->m_Random.rand(dist-1);
        std::advance( it , rand_index );

        SendPack.set_template_id( it->first );
        SendPack.set_count( CommonLine->m_Random.rand(100));

        m_Connect->SendMsg( PLAYER_STOREBUYITEM, &SendPack );
    }
}

void SendLogic::BindMobileNumberCheck( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgUpdateValue SendPack;

    std::string strMobileNumber;
    while ( strMobileNumber.size() < MOBILENUMBERSIZE )
    {
        strMobileNumber += CommonLine->m_Random.rand(9);
    }

    SendPack.set_str_0( strMobileNumber );

    m_Connect->SendMsg( PLAYER_BINDMOBILENUMBER, &SendPack );
}

void SendLogic::ChatPaoMaDeng( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgChat SendPack;

    std::string strText = "";
    while( strText.size() < PAOMADENG_CHAT_LENGTH ) {
        strText += RobotName->GetRandomName();
    }

    SendPack.set_text( strText );
    m_Connect->SendMsg( PLAYER_CHATPAOMADENG, &SendPack );

}

void SendLogic::GetSendMoneyLimit( void )
{
    DYNAMIC_CLIENT( m_Connect );

    m_Connect->SendMsg( PLAYER_GETSENDMONEYLIMIT );
}

void SendLogic::SearchPID( void )
{
    DYNAMIC_CLIENT( m_Connect );

    int rand_length = CommonLine->m_Random.rand( 10 );
    string str= "";

    while ( str.size() < rand_length )
    {
        char buf[10]={0};
        sprintf(buf, "%d", CommonLine->m_Random.rand( 9 ));

        str += buf;
    }

    MsgInt SendPack;
    SendPack.set_value( atoiInt64(str.c_str()) );
    m_Connect->SendMsg( PLAYER_SEARCHPID, &SendPack );
}

void SendLogic::SyncBlackList( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgRequestList SendPack;
    SendPack.set_check( pClient->OnGetBlackListNum() );
    m_Connect->SendMsg( PLAYER_SYNCBLACKLIST, &SendPack );

}

void SendLogic::DeleteBlackList( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value( pClient->OnGetRandomBlackListPID() );

    m_Connect->SendMsg( PLAYER_DELETEBLACKLIST, &SendPack );

}

void SendLogic::AddBlackList( void )
{
    DYNAMIC_CLIENT( m_Connect );

    CClient* pRandomClient = ClientMgr->GetRandomClient();
    if ( NULL == pRandomClient ) {
        return;
    }

    MsgInt SendPack;
    SendPack.set_value( pRandomClient->GetRoleID() );

    m_Connect->SendMsg( PLAYER_ADDBLACKLIST, &SendPack );
}

void SendLogic::SynchMissionData( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value( pClient->GetCRC32Mission() );

    m_Connect->SendMsg( PLAYER_SYNCHMISSIONDATA, &SendPack );
}

void SendLogic::RestoreScoreData( void )
{
    DYNAMIC_CLIENT( m_Connect );

    MsgInt SendPack;
    SendPack.set_value( pClient->GetRandomStatisticsID() );

    m_Connect->SendMsg( PLAYER_SYNCHMISSIONDATA, &SendPack );
}
