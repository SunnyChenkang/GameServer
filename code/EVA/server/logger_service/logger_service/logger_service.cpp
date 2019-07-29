#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "logger_service.h"
#include <logger_service/db/db_connect.h>

#ifdef NL_OS_WINDOWS
#include <Windows.h>
#endif

// admin modules;
extern void admin_modules_forceLink();
void foo()
{
    admin_modules_forceLink();
}

void CLoggerService::init( void )
{
    /// 注册消息;
    SS_NETWORK->addCallbackArray( LSE_DOT_CallBackItems , SS_ARRAYSIZE( LSE_DOT_CallBackItems ) );

    /// 注册服务器断开;
    SS_NETWORK->setServiceDownCallback( "SSE" , CallBack_SSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "PSE" , CallBack_PSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "GSE" , CallBack_GSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "FES" , CallBack_FESDisconnection );

    /// 数据库启动;
    CSString DBName         = ConfigFile.getVar("DataBaseName").asString();
    CSString DBHost         = ConfigFile.getVar("DataBaseHost").asString();
    CSString DBUser         = ConfigFile.getVar("DataBaseUser").asString();
    CSString DBPassword     = ConfigFile.getVar("DataBasePassword").asString();
    uint32   DBPost         = ConfigFile.getVar("DataBasePort").asInt();
    uint32   DBThreadCount  = ConfigFile.getVar("DataBaseThreadsCount").asInt();
    DBConnect.InitDBConnect( DBHost , DBUser , DBPassword , DBName , DBPost , DBThreadCount );
    DBConnect.StartDBThreads();

    /// 初始化定时器;
    TimerManager->init();
}

bool CLoggerService::update( void )
{
    /// 更新定时器;
    TimerManager->tickUpdate();
    return true;
}

void CLoggerService::release( void )
{
    /// 更新定时器;
    TimerManager->release();
    /// 关闭数据库线程;
    DBConnect.CloseDBThreads();
}

NLNET_SERVICE_MAIN( CLoggerService, "LSE", "logger_service", 49974 , "", "")