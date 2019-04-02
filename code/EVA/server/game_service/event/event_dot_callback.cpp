#include "event_dot_callback.h"
#include "event_define.h"

#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>
#include <game_service/item/item_manager.h>

GSE_NAMESPACE_BEGIN_DECL

void CEventDotCallBack::InitEventCallBack( void )
{
    EventDefine.EventUserLogin.connect  ( &EventDotCallBack , &CEventDotCallBack::CallBackUserLogin   );
    EventDefine.EventUserOffline.connect( &EventDotCallBack , &CEventDotCallBack::CallBackUserOffline );
    EventDefine.EventAddItem.connect    ( &EventDotCallBack , &CEventDotCallBack::CallBackAddItem     );
    EventDefine.EventSubItem.connect    ( &EventDotCallBack , &CEventDotCallBack::CallBackSubItem     );
}

void CEventDotCallBack::CallBackUserLogin( PB_UserLogin& UserLogin )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( UserLogin.role_id() );
    if ( NULL == pPlayer ) return;

    CRecordStmtData Record;
    Record.m_Stmt.SetUint32( 0 , UserLogin.role_id() );
    Record.m_Stmt.SetUint32( 1 , UserLogin.role_kind() );
    Record.m_Stmt.SetString( 2 , UserLogin.client_host().c_str() );
    Record.m_Stmt.SetUint32( 3 , pPlayer->GetRecordPlayerInfo().GetLastOfflineTime() );
    Record.m_Stmt.SetUint32( 4 , NLMISC::CTime::getSecondsSince1970() );
    Record.m_Stmt.SetSQL("CALL t_login_dot_insert(?,?,?,?,?)" );
    Record.SaveToDataBase();
}

void CEventDotCallBack::CallBackUserOffline( ROLE_ID RoleID )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer ) return;

    CRecordStmtData Record;
    Record.m_Stmt.SetUint32( 0 , pPlayer->GetRecordPlayerInfo().GetRoleID()   );
    Record.m_Stmt.SetUint32( 1 , pPlayer->GetRecordPlayerInfo().GetRoleKind() );
    Record.m_Stmt.SetString( 2 , pPlayer->GetRecordPlayerInfo().GetLastHost().c_str() );
    Record.m_Stmt.SetUint32( 3 , pPlayer->GetRecordPlayerInfo().GetLastLoginTime() );
    Record.m_Stmt.SetUint32( 4 , NLMISC::CTime::getSecondsSince1970() );
    Record.m_Stmt.SetSQL( "CALL t_offline_dot_insert(?,?,?,?,?)" );
    Record.SaveToDataBase();
}

void CEventDotCallBack::CallBackAddItem( ROLE_ID RoleID , ITEM_ID ItemID , uint32 ItemCount , uint32 ItemTotalCount , PB_DotItem DotItem )
{
    CRecordStmtData Record;
    Record.m_Stmt.SetUint32( 0 , ItemID );
    Record.m_Stmt.SetUint32( 1 , RoleID );
    Record.m_Stmt.SetUint32( 2 , DotItem );
    Record.m_Stmt.SetUint32( 3 , ItemCount );
    Record.m_Stmt.SetUint32( 4 , ItemTotalCount );
    Record.m_Stmt.SetUint32( 5 , NLMISC::CTime::getSecondsSince1970() );
    Record.m_Stmt.SetSQL( "CALL t_item_dot_insert(?,?,?,?,?,?)" );
    Record.SaveToDataBase();
}

void CEventDotCallBack::CallBackSubItem( ROLE_ID RoleID , ITEM_ID ItemID , uint32 ItemCount , uint32 ItemTotalCount , PB_DotItem DotItem )
{
    CRecordStmtData Record;
    Record.m_Stmt.SetUint32( 0 , ItemID );
    Record.m_Stmt.SetUint32( 1 , RoleID );
    Record.m_Stmt.SetUint32( 2 , DotItem );
    Record.m_Stmt.SetUint32( 3 , ItemCount );
    Record.m_Stmt.SetUint32( 4 , ItemTotalCount );
    Record.m_Stmt.SetUint32( 5 , NLMISC::CTime::getSecondsSince1970() );
    Record.m_Stmt.SetSQL( "CALL t_item_dot_insert(?,?,?,?,?,?)" );
    Record.SaveToDataBase();
}

GSE_NAMESPACE_END_DECL