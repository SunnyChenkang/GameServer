#ifndef GSE_GAME_TIMER_H_
#define GSE_GAME_TIMER_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

/// 游戏帧率定时器;
class CGameFrameMoveTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( CGameFrameMoveTimer );
public:
    CGameFrameMoveTimer( ROLE_ID RoomID );
    void timerCallback( CTimer* );
    SS_PROPERTY( ROOM_ID , RoomID , private );
};

GSE_NAMESPACE_END_DECL

#endif//GSE_GAME_TIMER_H_