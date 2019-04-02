#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "schedule_service.h"

#ifdef NL_OS_WINDOWS
#include <Windows.h>
#endif

using namespace NLMISC;
using namespace NLNET;
using namespace SSE;

// admin modules;
extern void admin_modules_forceLink();
void foo()
{
    admin_modules_forceLink();
}

void CScheduleService::init()
{
    // 注册消息;
    NLNET::CUnifiedNetwork::getInstance()->addCallbackArray( SSE_LOGIN_CallBackItems , SS_ARRAYSIZE( SSE_LOGIN_CallBackItems ) );
    NLNET::CUnifiedNetwork::getInstance()->addCallbackArray( SSE_ROOM_CallBackItems  , SS_ARRAYSIZE( SSE_ROOM_CallBackItems  ) );

    // 注册服务器断开;
    SS_NETWORK->setServiceDownCallback( "SSE" , CallBack_GSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "PSE" , CallBack_PSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "FES" , CallBack_FESDisconnection );
    // 初始化定时器;
    TimerManager->init();
    // 加载多语言;
    CI18N::load( ConfigFile.getVar("Language").asString() );

    // 执行本地命令;
    NLMISC::ICommand::execute( "load_json" , *InfoLog );
}

bool CScheduleService::update( void )
{
    // 更新定时器;
    TimerManager->tickUpdate();
    return true;
}

void CScheduleService::release( void )
{
    // 释放定时器;
    TimerManager->release();
}

NLNET_SERVICE_MAIN( CScheduleService, "SSE", "schedule_service", 49971 , "", "")

