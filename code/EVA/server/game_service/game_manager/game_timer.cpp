#include "game_timer.h"
#include <game_service/game_manager/game_base.h>
#include <game_service/game_manager/game_manager.h>

GSE_NAMESPACE_BEGIN_DECL

NL_INSTANCE_COUNTER_IMPL( CGameFrameMoveTimer );

CGameFrameMoveTimer::CGameFrameMoveTimer( ROOM_ID RoomID )
{
    m_RoomID = RoomID;
}

void CGameFrameMoveTimer::timerCallback( CTimer* pOwner )
{
    CGameBasePtr GameBasePtr = GameManager.GetGameBasePtr( m_RoomID );
    if ( nullptr == GameBasePtr ) { return; }
    GameBasePtr->FraveMove();
    /// 下次定时器触发;
    pOwner->setRemaining( GameBasePtr->GetFrameMoveTime() , this );
}

GSE_NAMESPACE_END_DECL