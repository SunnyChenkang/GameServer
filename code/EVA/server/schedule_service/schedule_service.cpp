#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "schedule_service.h"

#ifdef NL_OS_WINDOWS
#include <Windows.h>
#endif

// Reister Main;
using namespace NLNET;
using namespace SSE;

// variable value;
NLMISC::CVariable< uint32 > VAR_SSE_MAX_USERCOUNT("SSE" , "MaxPlayer" , "" , 0 , 0 , true );

// admin modules;
extern void admin_modules_forceLink();
void foo()
{
    admin_modules_forceLink();
}

void CScheduleService::init()
{
    // 注册消息;
    REGISTER_MAIN_FUNCITEM( SSE_LOGIN_CallBackItems );
    // 初始化定时器;
    TimerManager->init();
    // 加载配置表;
    JsonLoad.JsonLoadTable();
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

NLNET_SERVICE_MAIN( CScheduleService, "SSE", "schedule_service", 49971 , CallBackFunItems , "", "")

