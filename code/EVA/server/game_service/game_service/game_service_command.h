#ifndef GSE_COMMAND_H_
#define GSE_COMMAND_H_

#include "game_service_def.h"
#include <game_service/game_service/game_service_command.h>
#include <game_service/game_manager/game_register.h>

GSE_NAMESPACE_BEGIN_DECL

/// 加载Json配置文件;
NLMISC_COMMAND( load_json , " load json info " , "" )
{
    if ( args.size() != 0 ) return false;
    JsonLoad.JsonLoadTable();
    log.displayNL( "load json info finish !" );
    return true;
}

/// 加载游戏配置;
NLMISC_COMMAND( load_game , " load game info" , "" )
{
    if ( args.size() != 0 ) return false;
    GameRegister.LoadGameInfo();
    log.displayNL( "load game info finish !" );
    return true;
}

/// 加载多语言表;
NLMISC_COMMAND( load_i18n , "load i18n info " , "" )
{
    if ( args.size() != 0 ) return false;
    CI18N::load( IService::getInstance()->ConfigFile.getVar("Language").asString() );
    log.displayNL( " load i18n info finish ! " );
    return true;
}

GSE_NAMESPACE_END_DECL

#endif//GSE_COMMAND_H_