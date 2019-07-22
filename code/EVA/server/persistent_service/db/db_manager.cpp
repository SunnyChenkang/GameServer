#include "db_manager.h"
#include "db_connect.h"
#include "db_sub_func.h"

#include <persistent_service/player/player_manager.h>

PSE_NAMESPACE_BEGIN_DECL

void CDBManager::RefreshDBItem( TRecordItem& RecordItem )
{
    for ( auto Element : RecordItem )
    {
        RefreshDBItem( Element.second );
    }
}

void CDBManager::RefreshDBMission( TRecordMission& RecordMission )
{
    for ( auto Element : RecordMission )
    {
        RefreshDBMission( Element.second );
    }
}

void CDBManager::RefreshDBStatistics( TRecordStatisics& RecordStatistics )
{
    for ( auto Element : RecordStatistics )
    {
        RefreshDBStatistics( Element.second );
    }
}

void CDBManager::RefreshDBPlayer( CRecordPlayerInfo& rhs )
{
    if ( rhs.IsNullState() ) return;
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( rhs.GetRoleID() );
    if ( nullptr == PlayerPtr ) return;
    PlayerPtr->GetRecordPlayer().SetRecordBasePlayer( rhs );
    switch ( rhs.m_DBState.Bitset )
    {
    case DB_EVENT_INSERT:
        ThreadsPlayerInfo.PostToSub( new CRecordPlayerInfo( rhs ) , ( PROC_MSG )SubInsertPlayer );
        break;
    case DB_EVENT_UPDATE:
        ThreadsPlayerInfo.PostToSub( new CRecordPlayerInfo( rhs ) , ( PROC_MSG )SubUpdatePlayer );
        break;
    case DB_EVENT_DELETE:
        break;
    default:
        break;
    }

    rhs.ResetState();
}

void CDBManager::RefreshDBItem( CRecordItem& rhs )
{
    if ( rhs.IsNullState() )    return;
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( rhs.GetRoleID() );
    if ( nullptr == PlayerPtr ) return;

    TRecordItem& TRecordItemData = PlayerPtr->GetRecordPlayer().GetRecordItem();
    auto res = TRecordItemData.insert( std::make_pair( rhs.GetItemID() , rhs ) );
    if ( !res.second )
    res.first->second = rhs;

    switch ( rhs.m_DBState.Bitset )
    {
    case DB_EVENT_INSERT:
        ThreadsItem.PostToSub( new CRecordItem( rhs ) , ( PROC_MSG )SubInsertItem );
        break;
    case DB_EVENT_UPDATE:
        ThreadsItem.PostToSub( new CRecordItem( rhs ) , ( PROC_MSG )SubUpdateItem );
        break;
    case DB_EVENT_DELETE:
        break;
    default:
        break;
    }

    rhs.ResetState();
}

void CDBManager::RefreshDBMission( CRecordMission& rhs )
{
    if ( rhs.IsNullState() )    return;
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( rhs.GetRoleID() );
    if ( nullptr == PlayerPtr ) return;

    TRecordMission& TRecordMissionData = PlayerPtr->GetRecordPlayer().GetRecordMission();
    auto res = TRecordMissionData.insert( std::make_pair( rhs.GetMissionID() , rhs ) );
    if ( !res.second )
    res.first->second = rhs;

    switch ( rhs.m_DBState.Bitset )
    {
    case DB_EVENT_INSERT:
        ThreadsMission.PostToSub( new CRecordMission( rhs ) , ( PROC_MSG )SubInsertMission );
        break;
    case DB_EVENT_UPDATE:
        ThreadsMission.PostToSub( new CRecordMission( rhs ) , ( PROC_MSG )SubUpdateMission );
        break;
    case DB_EVENT_DELETE:
        break;
    default:
        break;
    }

    rhs.ResetState();
}

void CDBManager::RefreshDBStatistics( CRecordStatistics& rhs )
{
    if ( rhs.IsNullState() )    return;
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( rhs.GetRoleID() );
    if ( nullptr == PlayerPtr ) return;

    TRecordStatisics& TRecordStatisicsData = PlayerPtr->GetRecordPlayer().GetRecordStatisics();
    auto res = TRecordStatisicsData.insert( std::make_pair( rhs.GetStatisticsID() , rhs ) );
    if ( !res.second )
    res.first->second = rhs;

    switch ( rhs.m_DBState.Bitset )
    {
    case DB_EVENT_INSERT:
        ThreadsStatistics.PostToSub( new CRecordStatistics( rhs ) , ( PROC_MSG )SubInsertStatistics );
        break;
    case DB_EVENT_UPDATE:
        ThreadsStatistics.PostToSub( new CRecordStatistics( rhs ) , ( PROC_MSG )SubUpdateStatistics );
        break;
    case DB_EVENT_DELETE:
        break;
    default:
        break;
    }

    rhs.ResetState();
}

void CDBManager::RefreshAllDBData( void )
{
    
}

PSE_NAMESPACE_END_DECL