#ifndef SSE_COMMAND_H_
#define SSE_COMMAND_H_

#include "schedule_service_def.h"
#include <schedule_service/game/game_manager.h>

SSE_NAMESPACE_BEGIN_DECL

NLMISC_COMMAND( load_json , " load json info " , "" )
{
    if ( args.size() != 0 ) return false;
    JsonLoad.JsonLoadTable();
    log.displayNL( "load json info finish !" );
    return true;
}

NLMISC_COMMAND( load_game , " load game info " , "" )
{
    if ( args.size() != 1 ) return false;
    GameManager.LoadGameInfo( NLNET::TServiceId( args[0] ) );
    log.displayNL( " load game info finish ! " );
    return true;
}

NLMISC_COMMAND( load_hall , " load hall info " , "" )
{
    if ( args.size() != 0 ) return false;
    GameManager.LoadHallInfo();
    log.displayNL( " load hall info finish ! " );
    return true;
}


SSE_NAMESPACE_END_DECL

#endif//SSE_COMMAND_H_