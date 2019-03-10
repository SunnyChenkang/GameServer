#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "frontend_service.h"
#include "frontend_network.h"
#include "frontend_message.h"
#ifdef NL_OS_WINDOWS
#include <Windows.h>
#endif

// variable value;
NLMISC::CVariable< uint32 >         VAR_FES_WAIT_CONNECTION_TIMEROUT   ( "FSE", "WaitConnectionTimeOut"    , "", 60*1000 , 0, true );   // 等待垃圾连接时间;
NLMISC::CVariable< uint32 >         VAR_FES_CHECK_WAIT_CONNECTION_TIME ( "FSE", "CheckWaitConnectionTime"  , "", 60*1000 , 0, true );   // 检查垃圾连接时间;
NLMISC::CVariable< uint32 >         VAR_FES_MAX_CLIENTCOUNT            ( "FSE", "MaxClinetCount"           , "", 5000    , 0, true );   // 承载客户端数量;
NLMISC::CVariable< std::string >    VAR_FES_AUTH_SECRET                ( "FSE", "AuthSecret"               , "", "121593025@qq.com" , 0 , true      );   // 验证秘钥;

// admin modules;
extern void admin_modules_forceLink();
void foo()
{
    admin_modules_forceLink();
}

void CFrontEndService::init()
{
    // 启动网络库;
    FrontendNetWork.InitNetHandler( ConfigFile.getVar ("RUDPPort").asInt() , ConfigFile.getVar ("WEBPort").asInt() );
    // 初始化定时器管理器;
    TimerManager->init();
    // 加载配置表;
    JsonLoad.JsonLoadTable();

    // 检查断开连接服务器;
    //SS_NETWORK->setServiceDownCallback( "EGS" , FSE::CallBack_EGSDisconnection );
    //SS_NETWORK->setServiceDownCallback( "PLS" , FSE::CallBack_PLSDisconnection );
    //SS_NETWORK->setServiceDownCallback( "PDS" , FSE::CallBack_PDSDisconnection );
}

bool CFrontEndService::update()
{
    // 更新网络库;
    FrontendNetWork.UpdateNetHandler();
    // 更新定时器;
    TimerManager->tickUpdate();

    return true;
}

void CFrontEndService::release()
{
    // 释放网络库;
    FrontendNetWork.DestroyNetHandler();
    // 释放定时器;
    TimerManager->release();
}

// Reister Main;
using namespace NLNET;
using namespace FES;
NLNET_SERVICE_MAIN ( CFrontEndService, "FES", "frontend_service", 0, LocalCallBackItems , "", "" )