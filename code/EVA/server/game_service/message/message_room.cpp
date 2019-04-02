#include "message_room.h"
#include <game_service/room/room_manager.h>

GSE_NAMESPACE_BEGIN_DECL

void CallBack_CreateRoom( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    ROLE_ID RoleID = 0;
    PB_CreateRoom CreateRoom;
    Message.serial( RoleID );
    Message.serial( &CreateRoom );
    RoomManager.CreateRoom( RoleID , CreateRoom );
}

GSE_NAMESPACE_END_DECL