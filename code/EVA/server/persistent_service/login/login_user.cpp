#include "login_user.h"

#include <persistent_service/db/db_connect.h>
#include <persistent_service/db/db_sub_func.h>

#include <persistent_service/player/player_manager.h>

PSE_NAMESPACE_BEGIN_DECL

void CLoginUser::UserLoginCallBack( PB_UserLogin& UserLogin )
{
    /// 是否数据库加载用户;
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( UserLogin.role_id() );
    if ( nullptr == PlayerPtr )
    {
        ThreadsLoadPlayer.PostToSub( new SyncLoadPlayerData( UserLogin ) , (PROC_MSG)SubLoadPlayerEntity );
        return;
    }

    /// 同步数据GSE数据;
    TServiceId GameServiceID( UserLogin.game_service_id() );
    NLNET::CMessage SendMessage1( "MSG_LOADROLE" );
    SendMessage1.serial( PlayerPtr->GetRecordPlayer() );
    SS_NETWORK->send( GameServiceID , SendMessage1 );

    /// 用户登录;
    NLNET::CMessage SendMessage2("MSG_LOGIN");
    SendMessage2.serial( &UserLogin );
    SS_NETWORK->send( GameServiceID , SendMessage2 );
}

PSE_NAMESPACE_END_DECL