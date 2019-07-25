#include "event_dot_callback.h"
#include "event_define.h"

#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>
#include <game_service/item/item_manager.h>

GSE_NAMESPACE_BEGIN_DECL

void CEventDotCallBack::InitEventCallBack( void )
{
    EventDefine.PlayerLoginFinish.connect( &EventDotCallBack , &CEventDotCallBack::CallBackPlyaerLoginFinish   );
    EventDefine.PlayerOffline.connect    ( &EventDotCallBack , &CEventDotCallBack::CallBackPlayerOffline       );
    EventDefine.AddItem.connect          ( &EventDotCallBack , &CEventDotCallBack::CallBackAddItem             );
    EventDefine.SubItem.connect          ( &EventDotCallBack , &CEventDotCallBack::CallBackSubItem             );
}

void CEventDotCallBack::CallBackPlyaerLoginFinish( PB_UserLogin& UserLogin )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( UserLogin.role_id() );
    if ( nullptr == PlayerPtr ) { return; }

    CRecordStmtData Record;
    CRecordPlayerInfo& RecordPlayerInfo = PlayerPtr->GetRecordPlayer().GetRecordBasePlayer();
    Record.GetDBStmt().SetUint32( 0 , UserLogin.role_id() );
    Record.GetDBStmt().SetUint32( 1 , UserLogin.role_kind() );
    Record.GetDBStmt().SetString( 2 , UserLogin.client_host().c_str() );
    Record.GetDBStmt().SetUint32( 3 , RecordPlayerInfo.GetLastOfflineTime() );
    Record.GetDBStmt().SetUint32( 4 , NLMISC::CTime::getSecondsSince1970() );
    Record.GetDBStmt().SetSQL("CALL t_login_dot_insert(?,?,?,?,?)" );
    Record.SaveDB();
}

void CEventDotCallBack::CallBackPlayerOffline( ROLE_ID RoleID )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) { return; }

    CRecordStmtData Record;
    CRecordPlayerInfo& RecordPlayerInfo = PlayerPtr->GetRecordPlayer().GetRecordBasePlayer();
    Record.GetDBStmt().SetUint32( 0 , RecordPlayerInfo.GetRoleID()   );
    Record.GetDBStmt().SetUint32( 1 , RecordPlayerInfo.GetRoleKind() );
    Record.GetDBStmt().SetString( 2 , RecordPlayerInfo.GetLastHost().c_str() );
    Record.GetDBStmt().SetUint32( 3 , RecordPlayerInfo.GetLastLoginTime() );
    Record.GetDBStmt().SetUint32( 4 , NLMISC::CTime::getSecondsSince1970() );
    Record.GetDBStmt().SetSQL( "CALL t_offline_dot_insert(?,?,?,?,?)" );
    Record.SaveDB();
}

void CEventDotCallBack::CallBackAddItem( ROLE_ID RoleID , ITEM_ID ItemID , uint32 ItemCount , uint32 ItemTotalCount , PB_DotItem DotItem )
{
    CRecordStmtData Record;
    Record.GetDBStmt().SetUint32( 0 , ItemID );
    Record.GetDBStmt().SetUint32( 1 , RoleID );
    Record.GetDBStmt().SetUint32( 2 , DotItem );
    Record.GetDBStmt().SetUint32( 3 , ItemCount );
    Record.GetDBStmt().SetUint32( 4 , ItemTotalCount );
    Record.GetDBStmt().SetUint32( 5 , NLMISC::CTime::getSecondsSince1970() );
    Record.GetDBStmt().SetSQL( "CALL t_item_dot_insert(?,?,?,?,?,?)" );
    Record.SaveDB();
}

void CEventDotCallBack::CallBackSubItem( ROLE_ID RoleID , ITEM_ID ItemID , uint32 ItemCount , uint32 ItemTotalCount , PB_DotItem DotItem )
{
    CRecordStmtData Record;
    Record.GetDBStmt().SetUint32( 0 , ItemID );
    Record.GetDBStmt().SetUint32( 1 , RoleID );
    Record.GetDBStmt().SetUint32( 2 , DotItem );
    Record.GetDBStmt().SetUint32( 3 , ItemCount );
    Record.GetDBStmt().SetUint32( 4 , ItemTotalCount );
    Record.GetDBStmt().SetUint32( 5 , NLMISC::CTime::getSecondsSince1970() );
    Record.GetDBStmt().SetSQL( "CALL t_item_dot_insert(?,?,?,?,?,?)" );
    Record.SaveDB();
}

GSE_NAMESPACE_END_DECL