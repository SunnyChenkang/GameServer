#include "event_register.h"
#include "event_player_callback.h"
#include "event_room_callback.h"
#include "event_dot_callback.h"
#include "event_mission_callback.h"
#include "event_statistics_callback.h"

GSE_NAMESPACE_BEGIN_DECL

CEventRegister::CEventRegister( void )
{
    EventPlayerCallBack.InitEventCallBack();
    EventRoomCallBack.InitEventCallBack();
    EventDotCallBack.InitEventCallBack();
    EventMissionCallBack.InitEventCallBack();
    EventStatisticsCallBack.InitEventCallBack();
}

CEventRegister::~CEventRegister( void )
{
    
}

GSE_NAMESPACE_END_DECL