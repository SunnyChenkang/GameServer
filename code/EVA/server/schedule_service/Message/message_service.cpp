#include "message_service.h"
#include <schedule_service/room/room_manager.h>

SSE_NAMESPACE_BEGIN_DECL

void CallBack_GSEDisconnection( const std::string& ServiceName , NLNET::TServiceId ServiceId , void* )
{
    RoomManager.DeleteRoomInfo( ServiceId );
}

void CallBack_FESDisconnection( const std::string& ServiceName , NLNET::TServiceId ServiceId , void* )
{
    
}

void CallBack_PSEDisconnection( const std::string& ServiceName , NLNET::TServiceId ServiceId , void* )
{
    
}

SSE_NAMESPACE_END_DECL