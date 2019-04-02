#include "db_manager.h"
#include "db_connect.h"
#include "db_sub_func.h"

PSE_NAMESPACE_BEGIN_DECL

CRecordPlayer* CDBManager::GetPlayerInfo( ROLE_ID RoleID )
{
    PLAYER_TABLE::iterator it = m_PlayerTable.find( RoleID );
    if ( it == m_PlayerTable.end() ) return NULL;
    return &( it->second );
}

void PSE::CDBManager::SavePlayerInfo( LoadUserData* UserData )
{
    ROLE_ID RoleID = UserData->GetRecordPlayer().RecordPlayerInfo.GetRoleID();
    PLAYER_TABLE::iterator it = m_PlayerTable.find( RoleID );
    if ( it != m_PlayerTable.end() )
    {
        it->second = UserData->m_RecordPlayer;
        return;
    }
    m_PlayerTable.insert( std::make_pair( RoleID , UserData->m_RecordPlayer ) );
}

bool CDBManager::CreatePlayer( LoadUserData* UserData )
{
    if ( NULL == UserData ) return false;
    if ( NULL != GetPlayerInfo( UserData->GetRoleID() ) ) return false;

    CRecordPlayer RecordPlayer;
    m_PlayerTable.insert( std::make_pair( UserData->GetRoleID() , RecordPlayer ) );

    // 角色基础信息;
    {
        CRecordPlayerInfo RecordPlayerInfo;
        RecordPlayerInfo.SetInsert();
        RecordPlayerInfo.SetRoleID( UserData->GetRoleID() );
        RecordPlayerInfo.SetRoleKind( UserData->GetRoleKind() );
        RecordPlayerInfo.SetLastHost( UserData->GetClientHost() );
        RecordPlayerInfo.SetCreateTime( NLMISC::CTime::getSecondsSince1970() );
        RecordPlayerInfo.SetHeadID  ( JsonCreateRoleConfig.GetHeadID() );
        RecordPlayerInfo.SetNickName( JsonCreateRoleConfig.GetNickName() + NLMISC::toString( UserData->GetRoleID() ) );
        UpdateDBPlayer( RecordPlayerInfo );
    }

    // 添加道具信息;
    std::vector< CAddItemCell >::iterator it  = JsonCreateRoleConfig.m_AddItem.m_JsonArray.begin();
    for ( ; it != JsonCreateRoleConfig.m_AddItem.m_JsonArray.end() ; ++it )
    {
        CRecordItem RecordItem;
        RecordItem.SetInsert();
        RecordItem.SetRoleID( UserData->GetRoleID() ); 
        RecordItem.SetItemID( it->GetItemID() );
        RecordItem.SetItemCount( it->GetItemCount() );
        UpdateDBItem( RecordItem );

        CRecordStmtData RecordStmt;
        RecordStmt.m_Stmt.SetUint32( 0 , RecordItem.GetItemID() );
        RecordStmt.m_Stmt.SetUint32( 1 , RecordItem.GetRoleID() );
        RecordStmt.m_Stmt.SetUint32( 2 , DOT_ADD_CREATE_ROLE );
        RecordStmt.m_Stmt.SetUint32( 3 , RecordItem.GetItemCount() );
        RecordStmt.m_Stmt.SetUint32( 4 , RecordItem.GetItemCount() );
        RecordStmt.m_Stmt.SetUint32( 5 , NLMISC::CTime::getSecondsSince1970() );
        RecordStmt.m_Stmt.SetSQL( "CALL t_item_dot_insert(?,?,?,?,?,?)" );
        RecordStmt.SaveToDataBase();
    }

    return true;
}

void CDBManager::CloseServiceSaveDBData( void )
{
    for ( PLAYER_TABLE::iterator it = m_PlayerTable.begin() ; it != m_PlayerTable.end(); ++it )
    {
        UpdateDBPlayer( it->second.RecordPlayerInfo );
        UpdateDBItem( it->second.RecordItem );
        UpdateDBMission( it->second.RecordMission );
        UpdateDBStatistics( it->second.RecordStatisics );
    }
}

void CDBManager::UpdateDBItem( TRecordItem& RecordItem )
{
    for ( TRecordItem::iterator it = RecordItem.begin(); it != RecordItem.end(); ++it )
    {
        UpdateDBItem( it->second );
    }
}

void CDBManager::UpdateDBMission( TRecordMission& RecordMission )
{
    for ( TRecordMission::iterator it = RecordMission.begin(); it != RecordMission.end(); ++it )
    {
        UpdateDBMission( it->second );
    }
}

void CDBManager::UpdateDBStatistics( TRecordStatisics& RecordStatistics )
{
    for ( TRecordStatisics::iterator it = RecordStatistics.begin(); it != RecordStatistics.end(); ++it )
    {
        UpdateDBStatistics( it->second );
    }
}

void CDBManager::UpdateDBPlayer( CRecordPlayerInfo& RecordPlayerInfo )
{
    CRecordPlayer* pRecordPlayer = GetPlayerInfo( RecordPlayerInfo.GetRoleID() );
    if ( NULL == pRecordPlayer ) return;
    pRecordPlayer->RecordPlayerInfo = RecordPlayerInfo;
    switch ( RecordPlayerInfo.m_DBState.Bitset )
    {
    case DB_EVENT_INSERT:
        ThreadsPlayerInfo.PostToSub( new CRecordPlayerInfo( RecordPlayerInfo ) , ( PROC_MSG )SubInsertPlayer );
        break;
    case DB_EVENT_UPDATE:
        ThreadsPlayerInfo.PostToSub( new CRecordPlayerInfo( RecordPlayerInfo ) , ( PROC_MSG )SubUpdatePlayer );
        break;
    default:
        break;
    }
    RecordPlayerInfo.ResetState();
}

void CDBManager::UpdateDBItem( CRecordItem& RecordItem )
{
    CRecordPlayer* pRecordPlayer = GetPlayerInfo( RecordItem.GetRoleID() );
    if ( NULL == pRecordPlayer ) return;
    pRecordPlayer->RecordItem[ RecordItem.GetItemID() ] = RecordItem;
    switch ( RecordItem.m_DBState.Bitset )
    {
    case DB_EVENT_INSERT:
        ThreadsItem.PostToSub( new CRecordItem( RecordItem ) , ( PROC_MSG )SubInsertItem );
        break;
    case DB_EVENT_UPDATE:
        ThreadsItem.PostToSub( new CRecordItem( RecordItem ) , ( PROC_MSG )SubUpdateItem );
        break;
    default:
        break;
    }
    RecordItem.ResetState();
}

void CDBManager::UpdateDBMission( CRecordMission& RecordMission )
{
    CRecordPlayer* pRecordPlayer = GetPlayerInfo( RecordMission.GetRoleID() );
    if ( NULL == pRecordPlayer ) return;
    pRecordPlayer->RecordMission[ RecordMission.GetMissionID() ] = RecordMission;
    switch ( RecordMission.m_DBState.Bitset )
    {
    case DB_EVENT_INSERT:
        ThreadsMission.PostToSub( new CRecordMission( RecordMission ) , ( PROC_MSG )SubInsertMission );
        break;
    case DB_EVENT_UPDATE:
        ThreadsMission.PostToSub( new CRecordMission( RecordMission ) , ( PROC_MSG )SubUpdateMission );
        break;
    default:
        break;
    }
    RecordMission.ResetState();
}

void CDBManager::UpdateDBStatistics( CRecordStatistics& RecordStatistics )
{
    CRecordPlayer* pRecordPlayer = GetPlayerInfo( RecordStatistics.GetRoleID() );
    if ( NULL == pRecordPlayer ) return;
    pRecordPlayer->RecordStatisics[ RecordStatistics.GetStatisticsID() ] = RecordStatistics;
    switch ( RecordStatistics.m_DBState.Bitset )
    {
    case DB_EVENT_INSERT:
        ThreadsStatistics.PostToSub( new CRecordStatistics( RecordStatistics ) , ( PROC_MSG )SubInsertStatistics );
        break;
    case DB_EVENT_UPDATE:
        ThreadsStatistics.PostToSub( new CRecordStatistics( RecordStatistics ) , ( PROC_MSG )SubUpdateStatistics );
        break;
    default:
        break;
    }
    RecordStatistics.ResetState();
}

PSE_NAMESPACE_END_DECL