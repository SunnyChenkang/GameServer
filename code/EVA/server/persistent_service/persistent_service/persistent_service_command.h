#ifndef PSE_COMMAND_H_
#define PSE_COMMAND_H_

#include "persistent_service_def.h"
#include <persistent_service/db/db_manager.h>

PSE_NAMESPACE_BEGIN_DECL

NLMISC_COMMAND( close_service , " close service " , "" )
{
    DBManager.CloseServiceSaveDBData();
    log.displayNL( " all execute db succeed !" );
    return true;
}

NLMISC_COMMAND( load_json , " load json info " , "" )
{
    if ( args.size() != 0 ) return false;
    JsonLoad.JsonLoadTable();
    log.displayNL( "load json info succeed !" );
    return true;
}

PSE_NAMESPACE_END_DECL

#endif//PSE_COMMAND_H_