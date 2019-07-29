#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "server_share/uuid/uuid.h"
#include "game_service.h"
#include "game_service_command.h"
#include <game_service/event/event_register.h>
#include <server_share/uuid/uuid.h>

using namespace NLMISC;
using namespace NLNET;
using namespace GSE;

// admin modules;
extern void admin_modules_forceLink();
void foo()
{
    admin_modules_forceLink();
}

void CGameService::init( void )
{
    // 连接REDIS;
    CSString RedisHost      = ConfigFile.getVar("RedisHost").asString();
    CSString RedisPort      = ConfigFile.getVar("RedisPort").asString();
    CSString RedisPassword  = ConfigFile.getVar("RedisPass").asString();

    // 注册消息;
    SS_NETWORK->addCallbackArray( GSE_LOGIN_CallBackItems , SS_ARRAYSIZE( GSE_LOGIN_CallBackItems ) );

    // 注册断开函数;
    SS_NETWORK->setServiceDownCallback( "GSE" , CallBack_GSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "FES" , CallBack_FESDisconnection );
    SS_NETWORK->setServiceDownCallback( "PSD" , CallBack_PSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "SSE" , CallBack_SSEDisconnection );

    // 注册事件;
    EventRegister.getInstance();
    // 初始化定时器;
    TimerManager->init();

    // 执行本地命令;
    NLMISC::ICommand::execute( "load_json" , *InfoLog );
    NLMISC::ICommand::execute( "load_i18n" , *InfoLog );
    NLMISC::ICommand::execute( "load_game" , *InfoLog );
}

bool CGameService::update( void )
{
    // 更新定时器;
    TimerManager->tickUpdate();
    return true;
}

void CGameService::release( void )
{
    // 释放定时器;
    TimerManager->release();
}

NLNET_SERVICE_MAIN( CGameService, "GSE", "game_service", 0  , "", "")