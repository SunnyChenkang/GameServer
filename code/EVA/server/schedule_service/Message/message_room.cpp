#include "message_room.h"
#include <schedule_service/room/room_manager.h>

SSE_NAMESPACE_BEGIN_DECL

void CallBack_RegisterRoomInfo( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    RoomManager.RegisterRoomInfo( Message );
}

void CallBack_CreateRoom( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    RoomManager.CreateRoom( Message );
}

SSE_NAMESPACE_END_DECL