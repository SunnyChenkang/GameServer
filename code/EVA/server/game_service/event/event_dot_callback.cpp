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
    Record.m_Stmt.SetUint32( 0 , UserLogin.role_id() );
    Record.m_Stmt.SetUint32( 1 , UserLogin.role_kind() );
    Record.m_Stmt.SetString( 2 , UserLogin.client_host().c_str() );
    Record.m_Stmt.SetUint32( 3 , PlayerPtr->GetRecordPlayer().GetRecordBasePlayer().GetLastOfflineTime() );
    Record.m_Stmt.SetUint32( 4 , NLMISC::CTime::getSecondsSince1970() );
    Record.m_Stmt.SetSQL("CALL t_login_dot_insert(?,?,?,?,?)" );
    Record.SaveToDataBase();
}

void CEventDotCallBack::CallBackPlayerOffline( ROLE_ID RoleID )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) { return; }

    CRecordStmtData Record;
    CRecordPlayerInfo& RecordPlayerInfo = PlayerPtr->GetRecordPlayer().GetRecordBasePlayer();
    Record.m_Stmt.SetUint32( 0 , RecordPlayerInfo.GetRoleID()   );
    Record.m_Stmt.SetUint32( 1 , RecordPlayerInfo.GetRoleKind() );
    Record.m_Stmt.SetString( 2 , RecordPlayerInfo.GetLastHost().c_str() );
    Record.m_Stmt.SetUint32( 3 , RecordPlayerInfo.GetLastLoginTime() );
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