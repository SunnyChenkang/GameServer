#ifndef SSE_COMMAND_H_
#define SSE_COMMAND_H_

#include "schedule_service_def.h"

SSE_NAMESPACE_BEGIN_DECL

NLMISC_COMMAND( load_json , " load json info " , "" )
{
    if ( args.size() != 0 ) return false;
    JsonLoad.JsonLoadTable();
    log.displayNL( "load json info succeed !" );
    return true;
}

SSE_NAMESPACE_END_DECL

#endif//SSE_COMMAND_H_