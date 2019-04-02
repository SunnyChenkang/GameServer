#include "room_timer.h"
#include "room_base.h"
#include "room_register.h"

GSE_NAMESPACE_BEGIN_DECL

NL_INSTANCE_COUNTER_IMPL( CRoomFrameMoveTimer );
NL_INSTANCE_COUNTER_IMPL( CRoomSyncInfoTimer  );

CRoomFrameMoveTimer::CRoomFrameMoveTimer( CRoomBase* pRoomBase )
{
    m_RoomBase = pRoomBase;
}

void CRoomFrameMoveTimer::timerCallback( CTimer* pOwner )
{
    m_RoomBase->FrameMove();
    pOwner->setRemaining( m_RoomBase->GetFrameMoveTime() , this );
}

void CRoomSyncInfoTimer::timerCallback( CTimer* pOwner )
{
    RoomRegister.UpdateRoomInfo();
    pOwner->setRemaining( 3000 , this );
}

GSE_NAMESPACE_END_DECL