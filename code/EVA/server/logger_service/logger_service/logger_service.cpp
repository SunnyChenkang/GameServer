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

// reister main;
using namespace NLMISC;
using namespace NLNET;
using namespace LSE;

void CLoggerService::init( void )
{
    // 注册消息;
    NLNET::CUnifiedNetwork::getInstance()->addCallbackArray( LSE_DOT_CallBackItems , SS_ARRAYSIZE( LSE_DOT_CallBackItems ) );

    // 注册服务器断开;
    SS_NETWORK->setServiceDownCallback( "SSE" , CallBack_SSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "PSE" , CallBack_PSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "GSE" , CallBack_GSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "FES" , CallBack_FESDisconnection );

    // 数据库启动;
    NLMISC::CSString DBName     = ConfigFile.getVar("DataBaseName").asString();
    NLMISC::CSString DBHost     = ConfigFile.getVar("DataBaseHost").asString();
    NLMISC::CSString DBUser     = ConfigFile.getVar("DataBaseUser").asString();
    NLMISC::CSString DBPassword = ConfigFile.getVar("DataBasePassword").asString();
    NLMISC::CSString DBPost     = ConfigFile.getVar("DataBasePort").asString();
    nlinfo( "DataBaseName = %s "     , DBName.c_str() );
    nlinfo( "DataBaseHost = %s "     , DBHost.c_str() );
    nlinfo( "DataBaseUser = %s "     , DBUser.c_str() );
    nlinfo( "DataBasePassword = %s " , DBPassword.c_str() );
    nlinfo( "DataBasePort = %s "     , DBPost.c_str() );
    DBConnect.InitDBConnect( DBHost , DBUser , DBPassword , DBName , DBPost.atoui() );
    DBConnect.StartDBThreads();

    // 初始化定时器;
    TimerManager->init();
}

bool CLoggerService::update( void )
{
    TimerManager->tickUpdate();
    DBConnect.FrameMove();
    return true;
}

void CLoggerService::release( void )
{
    TimerManager->release();
    DBConnect.CloseDBThreads();
}

NLNET_SERVICE_MAIN( CLoggerService, "LSE", "logger_service", 49974 , "", "")