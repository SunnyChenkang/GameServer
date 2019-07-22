#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "persistent_service.h"
#include "persistent_service_command.h"
#include <persistent_service/db/db_connect.h>

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
using namespace PSE;

void CPersistentService::init()
{
    // 注册消息;
    NLNET::CUnifiedNetwork::getInstance()->addCallbackArray( PSE_LOGIN_CallBackItems , SS_ARRAYSIZE( PSE_LOGIN_CallBackItems ) );
    NLNET::CUnifiedNetwork::getInstance()->addCallbackArray( PSE_DB_CallBackItems    , SS_ARRAYSIZE( PSE_DB_CallBackItems ) );

    // 注册服务器断开;
    SS_NETWORK->setServiceDownCallback( "SSE" , CallBack_SSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "GSE" , CallBack_GSEDisconnection );
    SS_NETWORK->setServiceDownCallback( "FES" , CallBack_FESDisconnection );

    // 启动数据库;
    NLMISC::CSString DBName     = ConfigFile.getVar("DataBaseName").asString();
    NLMISC::CSString DBHost     = ConfigFile.getVar("DataBaseHost").asString();
    NLMISC::CSString DBUser     = ConfigFile.getVar("DataBaseUser").asString();
    NLMISC::CSString DBPassword = ConfigFile.getVar("DataBasePassword").asString();
    NLMISC::CSString DBPort     = ConfigFile.getVar("DataBasePort").asString();
    DBConnect.InitDBConnect( DBHost , DBUser , DBPassword , DBName , DBPort.atosi() );
    DBConnect.StartDBThreads();

    // 加载多语言;
    CI18N::load( ConfigFile.getVar("Language").asString() );
    // 初始化定时器;
    TimerManager->init();
    // 执行本地命令;
    NLMISC::ICommand::execute( "load_json" , *InfoLog );
}

bool CPersistentService::update( void )
{
    // 更新定时器;
    TimerManager->tickUpdate();
    // 更新数据库;
    DBConnect.FrameMove();
    return true;
}

void CPersistentService::release( void )
{
    // 释放定时器;
    TimerManager->release();
    // 执行本地命令;
    NLMISC::ICommand::execute( "close_service" , *InfoLog );
    // 释放数据库;
    DBConnect.CloseDBThreads();
}

NLNET_SERVICE_MAIN( CPersistentService, "PSE", "persistent_service", 50004 , "", "")