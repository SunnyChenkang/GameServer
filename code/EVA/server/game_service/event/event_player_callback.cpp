#include "event_player_callback.h"
#include "event_define.h"

#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>


GSE_NAMESPACE_BEGIN_DECL

void CEventPlayerCallBack::InitEventCallBack( void )
{
    EventDefine.EventUserLoad.connect    ( &EventPlayerCallBack ,&CEventPlayerCallBack::CallBackUserLoad );
    EventDefine.EventUserLogin.connect   ( &EventPlayerCallBack ,&CEventPlayerCallBack::CallBackUserLogin );
    EventDefine.EventUserOffline.connect ( &EventPlayerCallBack ,&CEventPlayerCallBack::CallBackUserOffline );
    EventDefine.EventChangeScenes.connect( &EventPlayerCallBack ,&CEventPlayerCallBack::CallBackChangeScenes );
}

void CEventPlayerCallBack::CallBackUserLoad( CRecordPlayer& RecordPlayer )
{
    PlayerManager.AllocPlayer( RecordPlayer );
}

void CEventPlayerCallBack::CallBackUserLogin( PB_UserLogin& UserLogin )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( UserLogin.role_id() );
    if ( NULL == pPlayer ) return;

    // 更新玩家信息;
    pPlayer->SetFrontendServiceId( NLNET::TServiceId( UserLogin.frontend_service_id() ) );
    pPlayer->GetRecordPlayerInfo().SetLastHost( UserLogin.client_host() );
    pPlayer->GetRecordPlayerInfo().SetLastLoginTime( NLMISC::CTime::getSecondsSince1970() );
    pPlayer->GetRecordPlayerInfo().SetUpdate();
    pPlayer->GetRecordPlayerInfo().SaveToDataBase();

    // 同步玩家数据;
    ROLE_ID RoleID                      = UserLogin.role_id();
    NLNET::TServiceId GameServiceId     = NLNET::IService::getInstance()->getServiceId();
    NLNET::TServiceId FrontendServiceId = pPlayer->GetFrontendServiceId();

    // 登录成功;
    NLNET::CMessage SendMessage1("MSG_LOGIN_SUCCEED");
    SendMessage1.serial( RoleID );
    SendMessage1.serial( GameServiceId );
    SendMessage1.serial( FrontendServiceId );
    SS_NETWORK->send( "SSE"             , SendMessage1 );
    SS_NETWORK->send( FrontendServiceId , SendMessage1 );

    // 同步客户端数据;
    PB_Player PBPlayer;
    pPlayer->GetRecordPlayerInfo().serial( PBPlayer );
    NLNET::CMessage SendMessage2("MSG_LOGIN_SUCCEED");
    SendMessage2.serial( &PBPlayer );
    SendToClient( RoleID, pPlayer->GetFrontendServiceId() , SendMessage2 );
}

void CEventPlayerCallBack::CallBackUserOffline( ROLE_ID RoleID )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer ) return;

    // 更新玩家信息;
    pPlayer->GetRecordPlayerInfo().SetLastOfflineTime( NLMISC::CTime::getSecondsSince1970() );
    pPlayer->GetRecordPlayerInfo().SetUpdate();
    pPlayer->GetRecordPlayerInfo().SaveToDataBase();
}

void CEventPlayerCallBack::CallBackChangeScenes( CPlayer& Player )
{
    CPlayer* pNewPlayer = PlayerManager.AllocPlayer( Player.GetRecordPlayerInfo().GetRoleID() );
    *pNewPlayer = Player;

    ROLE_ID RoleID = Player.GetRecordPlayerInfo().GetRoleID();
    NLNET::TServiceId GameServiceId     = NLNET::IService::getInstance()->getServiceId();
    NLNET::TServiceId FrontendServiceId = Player.GetFrontendServiceId();

    NLNET::CMessage SendMessage("MSG_LOGIN_SUCCEED");
    SendMessage.serial( RoleID );
    SendMessage.serial( GameServiceId );
    SendMessage.serial( FrontendServiceId );
    SS_NETWORK->send( "SSE"             , SendMessage );
    SS_NETWORK->send( FrontendServiceId , SendMessage );
}

GSE_NAMESPACE_END_DECL