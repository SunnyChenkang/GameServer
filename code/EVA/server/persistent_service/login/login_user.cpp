#include "login_user.h"

#include <persistent_service/db/db_manager.h>
#include <persistent_service/db/db_connect.h>
#include <persistent_service/db/db_sub_func.h>

PSE_NAMESPACE_BEGIN_DECL

void CLoginUser::UserLoginCallBack( PB_UserLogin& UserLogin )
{
    // 数据库加载玩家数据;
    CRecordPlayer* pRecordPlayer = DBManager.GetPlayerInfo( UserLogin.role_id() );
    if ( NULL == pRecordPlayer )
    {
        ThreadsLoadPlayer.PostToSub( new LoadUserData( UserLogin ) , (PROC_MSG)SubLoadPlayerEntity );
        return;
    }

    // 同步数据GSE数据;
    NLNET::CMessage SendMessage1( "MSG_LOADROLE" );
    SendMessage1.serial( *pRecordPlayer );
    SS_NETWORK->send( NLNET::TServiceId( UserLogin.game_service_id() ) , SendMessage1 );

    // 用户登录;
    NLNET::CMessage SendMessage2("MSG_LOGIN");
    SendMessage2.serial( &UserLogin );
    SS_NETWORK->send( NLNET::TServiceId( UserLogin.game_service_id() ) , SendMessage2 );
}

PSE_NAMESPACE_END_DECL