#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "game_service.h"
#include "game_service_command.h"
#include <game_service/event/event_register.h>
#include <game_service/redis/redis.h>

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
    NLMISC::CSString RedisHost      = ConfigFile.getVar("RedisHost").asString();
    NLMISC::CSString RedisPort      = ConfigFile.getVar("RedisPort").asString();
    NLMISC::CSString RedisTimeOut   = ConfigFile.getVar("RedisTimeOut").asString();
    NLMISC::CSString RedisPassword  = ConfigFile.getVar("RedisPassword").asString();
    nlinfo( "RedisHost     %s" , RedisHost.c_str()     );
    nlinfo( "RedisPort     %d" , RedisPort.atosi()     );
    nlinfo( "RedisTimeOut  %d" , RedisTimeOut.atosi()  );
    nlinfo( "RedisPassword %s" , RedisPassword.c_str() );
    GameRedis.Connect( RedisHost.c_str() , RedisPort.atoui() , RedisTimeOut.atoui() , RedisPassword.c_str() );

    // 注册消息;
    NLNET::CUnifiedNetwork::getInstance()->addCallbackArray( GSE_LOGIN_CallBackItems , SS_ARRAYSIZE( GSE_LOGIN_CallBackItems ) );
    NLNET::CUnifiedNetwork::getInstance()->addCallbackArray( SSE_ROOM_CallBackItems  , SS_ARRAYSIZE( SSE_ROOM_CallBackItems  ) );

    // 注册断开函数;
    SS_NETWORK->setServiceDownCallback( "GSE" , CallBack_GSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "FES" , CallBack_FESDisconnection );
    SS_NETWORK->setServiceDownCallback( "PSD" , CallBack_PSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "SSE" , CallBack_SSEDisconnection );

    // 注册事件;
    EventRegister.getInstance();
    // 初始化定时器;
    TimerManager->init();
    // 加载多语言;
    CI18N::load( ConfigFile.getVar("Language").asString() );

    // 执行本地命令;
    NLMISC::ICommand::execute( "load_room" , *InfoLog );
    NLMISC::ICommand::execute( "load_json" , *InfoLog );
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
    // 关闭REDIS;
    GameRedis.Close();
}

NLNET_SERVICE_MAIN( CGameService, "GSE", "game_service", 0  , "", "")


