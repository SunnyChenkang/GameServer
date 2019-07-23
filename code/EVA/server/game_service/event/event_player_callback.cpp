#include "event_player_callback.h"
#include "event_define.h"



GSE_NAMESPACE_BEGIN_DECL

void CEventPlayerCallBack::InitEventCallBack( void )
{
    EventDefine.EventPlayerLoadFinish.connect   ( &EventPlayerCallBack ,&CEventPlayerCallBack::CallBackPlayerLoadFinish     );
    EventDefine.EventPlayerLoginFinish.connect  ( &EventPlayerCallBack ,&CEventPlayerCallBack::CallBackPlyaerLoginFinish    );
    EventDefine.EventPlayerOffline.connect      ( &EventPlayerCallBack ,&CEventPlayerCallBack::CallBackPlayerOffline        );
    EventDefine.EventChangeScenes.connect       ( &EventPlayerCallBack ,&CEventPlayerCallBack::CallBackChangeScenes         );
}

void CEventPlayerCallBack::CallBackPlayerLoadFinish( CRecordPlayer& RecordPlayer )
{
    CPlayerPtr PlayerPtr = PlayerManager.AllocPlayer( RecordPlayer.GetRecordBasePlayer().GetRoleID() );
    if ( nullptr == PlayerPtr ) { return; }
    PlayerPtr->SetRecordPlayer( RecordPlayer );
}

void CEventPlayerCallBack::CallBackPlyaerLoginFinish( PB_UserLogin& UserLogin )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( UserLogin.role_id() );
    if ( nullptr == PlayerPtr ) { return; }

    /// 更新玩家信息;
    CRecordPlayerInfo& RecordPlayerInfo = PlayerPtr->GetRecordPlayer().GetRecordBasePlayer();
    PlayerPtr->SetFrontendServiceID( NLNET::TServiceId( UserLogin.frontend_service_id() ) );
    RecordPlayerInfo.SetLastHost( UserLogin.client_host() );
    RecordPlayerInfo.SetLastLoginTime( NLMISC::CTime::getSecondsSince1970() );
    RecordPlayerInfo.SetUpdate();
    RecordPlayerInfo.SaveToDataBase();

    ROLE_ID RoleID                      = UserLogin.role_id();
    NLNET::TServiceId GameServiceId     = IService::getInstance()->getServiceId();
    NLNET::TServiceId FrontendServiceId = PlayerPtr->GetFrontendServiceID();

    /// 同步登录成功;
    NLNET::CMessage SendMessage1("MSG_LOGIN_FINISH");
    SendMessage1.serial( RoleID );
    SendMessage1.serial( GameServiceId );
    SendMessage1.serial( FrontendServiceId );
    SS_NETWORK->send( "SSE"             , SendMessage1 );
    SS_NETWORK->send( FrontendServiceId , SendMessage1 );

    /// 同步客户端数据;
    PB_Player PBPlayer;
    RecordPlayerInfo.serial( PBPlayer );
    NLNET::CMessage SendMessage2("MSG_LOGIN_FINISH");
    SendMessage2.serial( &PBPlayer );
    SendToClient( RoleID, FrontendServiceId , SendMessage2 );
}

void CEventPlayerCallBack::CallBackPlayerOffline( ROLE_ID RoleID )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) { return; }

    /// 更新玩家信息;
    CRecordPlayerInfo& RecordPlayerInfo = PlayerPtr->GetRecordPlayer().GetRecordBasePlayer();
    RecordPlayerInfo.SetLastOfflineTime( NLMISC::CTime::getSecondsSince1970() );
    RecordPlayerInfo.SetUpdate();
    RecordPlayerInfo.SaveToDataBase();
}

void CEventPlayerCallBack::CallBackChangeScenes( CPlayerPtr Player )
{
    CPlayerPtr PlayerPtr = PlayerManager.AllocPlayer( Player->GetRecordPlayer().GetRecordBasePlayer().GetRoleID() );
    if ( nullptr == PlayerPtr ) { return; }
    PlayerPtr = Player;

    ROLE_ID RoleID                      = PlayerPtr->GetRecordPlayer().GetRecordBasePlayer().GetRoleID();
    NLNET::TServiceId GameServiceId     = IService::getInstance()->getServiceId();
    NLNET::TServiceId FrontendServiceId = PlayerPtr->GetFrontendServiceID();

    /// 同步切换场景;
    NLNET::CMessage SendMessage( "MSG_CHANGE_SCENES" );
    SendMessage.serial( RoleID );
    SendMessage.serial( GameServiceId );
    SendMessage.serial( FrontendServiceId );
    SS_NETWORK->send( "SSE"             , SendMessage );
    SS_NETWORK->send( FrontendServiceId , SendMessage );
}

GSE_NAMESPACE_END_DECL