#include "db_main_func.h"
#include "db_manager.h"
#include <persistent_service/login/login_user.h>
#include <persistent_service/player/player_manager.h>

PSE_NAMESPACE_BEGIN_DECL

void MainLoadPlayerEntity( void* data )
{
    SyncLoadPlayerData* pSyncLoadData = ( SyncLoadPlayerData* )data;
    if ( NULL == pSyncLoadData ){ return; }
    CPlayerPtr PlayerPtr = PlayerManager.AllocPlayer( pSyncLoadData->GetRoleID() );
    if ( nullptr == PlayerPtr ) { return; }

    /// 保存玩家信息;
    PlayerPtr->SetRecordPlayer( pSyncLoadData->m_RecordPlayer );

    /// 玩家登录;
    PB_UserLogin UserLogin;
    UserLogin.set_role_id( pSyncLoadData->GetRoleID() );
    UserLogin.set_client_host( pSyncLoadData->GetClientHost() );
    UserLogin.set_frontend_service_id( pSyncLoadData->GetFrontendServiceID().get() );
    UserLogin.set_game_service_id( pSyncLoadData->GetGameServiceID().get() );
    LoginUser.UserLoginCallBack( UserLogin );
}

void MainCreateRole( void* data )
{
    SyncLoadPlayerData* pSyncLoadData = ( SyncLoadPlayerData* )data;
    if ( NULL == pSyncLoadData ){ return; }
    CPlayerPtr PlayerPtr = PlayerManager.AllocPlayer( pSyncLoadData->GetRoleID() );
    if ( nullptr == PlayerPtr ) { return; }

    /// 自动创建角色;
    for ( sint32 idx = 0; idx < 1; idx++ )
    {
        CRecordPlayerInfo RecordPlayerInfo;
        RecordPlayerInfo.SetInsert();
        RecordPlayerInfo.SetRoleID  ( pSyncLoadData->GetRoleID() );
        RecordPlayerInfo.SetRoleKind( pSyncLoadData->GetRoleKind() );
        RecordPlayerInfo.SetLastHost( pSyncLoadData->GetClientHost() );
        RecordPlayerInfo.SetNickName( "auto create name" );
        RecordPlayerInfo.SetCreateTime( NLMISC::CTime::getSecondsSince1970() );
        RecordPlayerInfo.SetHeadID( 0 );
        DBManager.RefreshDBPlayer( RecordPlayerInfo );
    }

    /// 添加道具;
    for ( auto Element : JsonCreateRoleConfig.m_AddItem.m_JsonArray )
    {
        CRecordItem RecordItem;
        RecordItem.SetInsert();
        RecordItem.SetRoleID( pSyncLoadData->GetRoleID() );
        RecordItem.SetItemID( Element.GetItemID() );
        RecordItem.SetItemCount( Element.GetItemCount() );
        DBManager.RefreshDBItem( RecordItem );
    }

    /// 用户登录;
    PB_UserLogin UserLogin;
    UserLogin.set_role_id( pSyncLoadData->GetRoleID() );
    UserLogin.set_client_host( pSyncLoadData->GetClientHost() );
    UserLogin.set_frontend_service_id( pSyncLoadData->GetFrontendServiceID().get() );
    UserLogin.set_game_service_id( pSyncLoadData->GetGameServiceID().get() );
    LoginUser.UserLoginCallBack( UserLogin );
}

PSE_NAMESPACE_END_DECL

