#ifndef GSE_ROOM_TIMER_H_
#define GSE_ROOM_TIMER_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CRoomBase;

// 房间内帧率;
class CRoomFrameMoveTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( CRoomFrameMoveTimer )
public:
    CRoomFrameMoveTimer( CRoomBase* pRoomBase );
    void timerCallback( CTimer* );

    SS_PROPERTY( CRoomBase* , RoomBase , private );
};

// 同步房间信息;
class CRoomSyncInfoTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( CRoomSyncInfoTimer );
public:
    CRoomSyncInfoTimer( void ){ };
    void timerCallback( CTimer* );
};

GSE_NAMESPACE_END_DECL

#endif //GSE_ROOM_TIMER_H_;