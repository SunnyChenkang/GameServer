#include "login_user.h"
#include <schedule_service/player/player.h>
#include <schedule_service/player/player_manager.h>
#include <schedule_service/game/game_manager.h>

SSE_NAMESPACE_BEGIN_DECL

void CLoginUser::CallBackPlayerLogin( NLNET::CMessage& Message )
{
    PB_UserLogin UserLogin;
    Message.serial( &UserLogin );

    CGameInfoPtr    GameInfoPtr = nullptr;
    NLNET::CMessage SendMessage("MSG_LOGIN");

    /// 检查是否存DBCache加载数据;
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( UserLogin.role_id() );
    if ( nullptr == PlayerPtr ) { PlayerPtr = PlayerManager.AllocPlayer( UserLogin.role_id() ); }
    if ( nullptr == PlayerPtr ) { return; }

    if ( PlayerPtr->IsDBCacheLoadUser() ) {
        goto load;
    }
    /// 通知逻辑服务器构建玩家;
    SendMessage.serial( &UserLogin );
    SS_NETWORK->send( PlayerPtr->GetGameServiceId() , SendMessage );
    return;

load:
    /// 分配大厅服务器;
    GameInfoPtr = GameManager.GetGameInfoPtr();
    if ( nullptr == GameInfoPtr ) { return; }
    UserLogin.set_game_service_id( GameInfoPtr->GetGameServiceID().get() );
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
    if ( nullptr == PlayerPtr ) return;
    PlayerPtr->SetFrontendServiceId( FrontendServiceId );
    PlayerPtr->SetGameServiceId( GameServiceId );
}

void CLoginUser::CallBackChangeScenes( NLNET::CMessage& Message )
{
    this->CallBackPlayerLoginFinish( Message );
}

SSE_NAMESPACE_END_DECL