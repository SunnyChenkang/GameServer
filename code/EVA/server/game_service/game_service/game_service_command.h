#ifndef GSE_COMMAND_H_
#define GSE_COMMAND_H_

#include "game_service_def.h"
#include <game_service/game_service/game_service_command.h>
#include <game_service/room/room_register.h>

GSE_NAMESPACE_BEGIN_DECL

NLMISC_COMMAND( load_room , " load room info " , "" )
{
    if ( args.size() != 0 ) return false;
    RoomRegister.LoadRoomInfo();
    log.displayNL( "load room info succeed !" );
    return true;
}

NLMISC_COMMAND( load_json , " load json info " , "" )
{
    if ( args.size() != 0 ) return false;
    JsonLoad.JsonLoadTable();
    log.displayNL( "load json info succeed !" );
    return true;
}

GSE_NAMESPACE_END_DECL

#endif//GSE_COMMAND_H_