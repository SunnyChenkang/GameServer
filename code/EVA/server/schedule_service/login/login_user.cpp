#include "login_user.h"
#include <schedule_service/player/player.h>
#include <schedule_service/player/player_manager.h>
#include <schedule_service/game/game_manager.h>

SSE_NAMESPACE_BEGIN_DECL

void CLoginUser::CallBackPlayerLogin( NLNET::CMessage& Message )
{
    PB_UserLogin UserLogin;
    Message.serial( &UserLogin );

    /// 检查是否存DBCache加载数据;
    NLNET::CMessage SendMessage( "MSG_LOGIN" );
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( UserLogin.role_id() , true );
    if ( nullptr == PlayerPtr ) { return; }
    if ( PlayerPtr->IsLoadDBCache() ) {
        goto load_cache;
    }

    /// 通知逻辑服务器构建玩家;
    SendMessage.serial( &UserLogin );
    SS_NETWORK->send( PlayerPtr->GetGameServiceId() , SendMessage );
    return;

    /// 分配大厅服务器;
load_cache:
    TServiceId HallGoodSvrID = GameManager.GetGoodServiceID( CSString("Hall") );
    if ( HallGoodSvrID == TServiceId::InvalidId ) { return; }
    UserLogin.set_game_service_id( HallGoodSvrID.get() );
    SendMessage.serial( &UserLogin );
    SS_NETWORK->send( "PSE" , SendMessage );
}

void CLoginUser::CallBackPlayerLoginFinish( NLNET::CMessage& Message )
{
    ROLE_ID RoleID                      = 0;
    NLNET::TServiceId GameServiceId     = NLNET::TServiceId::InvalidId;
    NLNET::TServiceId FrontendServiceId = NLNET::TServiceId::InvalidId;

    Message.serial( RoleID );
    Message.serial( GameServiceId );
    Message.serial( FrontendServiceId );

    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) { return; }
    PlayerPtr->SetGameServiceId( GameServiceId );
    PlayerPtr->SetFrontendServiceId( FrontendServiceId );
}

void CLoginUser::CallBackChangeScenes( NLNET::CMessage& Message )
{
    this->CallBackPlayerLoginFinish( Message );
}

SSE_NAMESPACE_END_DECL