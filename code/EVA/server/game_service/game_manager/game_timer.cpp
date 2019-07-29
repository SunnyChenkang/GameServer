#include "game_timer.h"
#include <game_service/game_manager/game_base.h>
#include <game_service/game_manager/game_register.h>
#include <game_service/game_manager/game_manager.h>

GSE_NAMESPACE_BEGIN_DECL

NL_INSTANCE_COUNTER_IMPL( CGameFrameMoveTimer );
NL_INSTANCE_COUNTER_IMPL( CRefreshGameInfo );

void CGameFrameMoveTimer::timerCallback( CTimer* pOwner )
{
    /// 游戏内帧率更新;
    CGameBasePtr GameBasePtr = GameManager.GetGameBasePtr( m_GameID );
    if ( nullptr == GameBasePtr ) { return; }
    GameBasePtr->GameFraveMove();
    pOwner->setRemaining( GameBasePtr->GetFrameMoveTime() , this );
}

void CRefreshGameInfo::timerCallback( CTimer* pOwner )
{
    /// 注册游戏信息;
    NLNET::CMessage SendMessage("MSG_GAME_REGISTER");
    SendMessage.serialCont( GameRegister.GetGameList() );
    SS_NETWORK->send( "SSE" , SendMessage );
}

GSE_NAMESPACE_END_DECL