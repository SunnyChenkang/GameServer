#include "db_sub_func.h"
#include "db_main_func.h"
#include "db_connect.h"

PSE_NAMESPACE_BEGIN_DECL

void SubLoadPlayerEntity( void* data )
{
    LoadUserData* pRecord = ( LoadUserData* )data;
    if ( NULL == pRecord ) return;
    pRecord->m_RecordPlayer.RecordPlayerInfo.SetRoleID( pRecord->GetRoleID() );

    // 查询角色是否存在;
    CDBExecute* pWorker = ThreadsLoadPlayer.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_IS_EXIST_PLAYER );
    if ( NULL == pStmt   ) return;
    CDBResult* pResult = NULL;
    pStmt->SetUint32( 0 , pRecord->m_RecordPlayer.RecordPlayerInfo.GetRoleID() );
    pWorker->Query( pStmt , &pResult );
    size_t ResultCount = pResult->GetCount();
    pResult->Release();

    // 用户创建角色;
    if ( ResultCount <= 0 )
    {
        ThreadsLoadPlayer.PostToMain( new LoadUserData( *pRecord ) , (PROC_MSG)MainCreateRole );
        return;
    }

    // 加载角色实体;
    SubLoadPlayer    ( pRecord->m_RecordPlayer );   // 玩家基础信息;
    SubLoadItem      ( pRecord->m_RecordPlayer );   // 加载道具信息;
    SubLoadStatistics( pRecord->m_RecordPlayer );   // 加载统计信息;
    SubLoadMission   ( pRecord->m_RecordPlayer );   // 加载任务信息;
    ThreadsLoadPlayer.PostToMain( new LoadUserData( *pRecord ) , (PROC_MSG)MainLoadPlayerEntity );
}

bool SubLoadPlayer( CRecordPlayer& RecordPlayer )
{
    CDBExecute* pWorker = ThreadsLoadPlayer.GetDBExecute();
    if ( NULL == pWorker ) return false;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_LOAD_PLAYERINFO );
    if ( NULL == pStmt )   return false;

    CDBResult* pResult = NULL;
    pStmt->SetUint32( 0 , RecordPlayer.RecordPlayerInfo.GetRoleID() );
    pWorker->Query( pStmt , &pResult );
    if ( NULL == pResult ) return false;

    sint32 idx = 0;
    RecordPlayer.RecordPlayerInfo.SetRoleID         ( pResult->GetUint32( idx++ ) );
    RecordPlayer.RecordPlayerInfo.SetRoleKind       ( pResult->GetUint8 ( idx++ ) );
    RecordPlayer.RecordPlayerInfo.SetLastHost       ( pResult->GetString( idx++ ).second );
    RecordPlayer.RecordPlayerInfo.SetGameTime       ( pResult->GetUint32( idx++ ) );
    RecordPlayer.RecordPlayerInfo.SetLastLoginTime  ( pResult->GetUint32( idx++ ) );
    RecordPlayer.RecordPlayerInfo.SetLastOfflineTime( pResult->GetUint32( idx++ ) );
    RecordPlayer.RecordPlayerInfo.SetCreateTime     ( pResult->GetUint32( idx++ ) );
    RecordPlayer.RecordPlayerInfo.SetNickName       ( pResult->GetString( idx++ ).second );
    RecordPlayer.RecordPlayerInfo.SetHeadID         ( pResult->GetUint16( idx++ ) );

    pResult->Release();
    pResult = NULL;
    return true;
}

bool SubLoadItem( CRecordPlayer& RecordPlayer )
{
    CDBExecute* pWorker = ThreadsLoadPlayer.GetDBExecute();
    if ( NULL == pWorker ) return false;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_LOAD_ITEM );
    if ( NULL == pStmt )   return false;

    CRecordItem ItemData;
    ItemData.SetRoleID( RecordPlayer.RecordPlayerInfo.GetRoleID() );

    CDBResult* pResult = NULL;
    pStmt->SetUint32( 0 , RecordPlayer.RecordPlayerInfo.GetRoleID() );
    pWorker->Query( pStmt , &pResult );
    if ( NULL == pResult ) return false;

    while ( pResult->NextRow() )
    {
        sint32 idx = 0;
        ItemData.SetItemID      ( pResult->GetUint32( idx++ ) );
        ItemData.SetItemCount   ( pResult->GetUint32( idx++ ) );
        ItemData.SetLastTime    ( pResult->GetUint32( idx++ ) );
        RecordPlayer.RecordItem.insert( std::make_pair(  ItemData.GetItemID() , ItemData ) );
    }

    pResult->Release();
    pResult = NULL;
    return true;
}

bool SubLoadStatistics( CRecordPlayer& RecordPlayer )
{
    CDBExecute* pWorker = ThreadsLoadPlayer.GetDBExecute();
    if ( NULL == pWorker ) return false;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_LOAD_STATISTICS );
    if ( NULL == pStmt )   return false;

    CRecordStatistics StatisticsData;
    StatisticsData.SetRoleID( RecordPlayer.RecordPlayerInfo.GetRoleID() );

    CDBResult* pResult = NULL;
    pStmt->SetUint32( 0 , RecordPlayer.RecordPlayerInfo.GetRoleID() );
    pWorker->Query( pStmt , &pResult );
    if ( NULL == pResult ) return false;

    while ( pResult->NextRow() )
    {
        sint32 idx = 0;
        StatisticsData.SetStatisticsID( pResult->GetUint32( idx++ ) );
        StatisticsData.SetCount       ( pResult->GetUint32( idx++ ) );
        RecordPlayer.RecordStatisics.insert( std::make_pair( StatisticsData.GetStatisticsID() , StatisticsData ) );
    }

    pResult->Release();
    pResult = NULL;
    return true;
}

bool SubLoadMission( CRecordPlayer& RecordPlayer )
{
    CDBExecute* pWorker = ThreadsLoadPlayer.GetDBExecute();
    if ( NULL == pWorker ) return false;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_LOAD_MISSION );
    if ( NULL == pStmt )   return false;

    CRecordMission MissionData;
    MissionData.SetRoleID( RecordPlayer.RecordPlayerInfo.GetRoleID() );

    CDBResult* pResult = NULL;
    pStmt->SetUint32( 0 , RecordPlayer.RecordPlayerInfo.GetRoleID() );
    pWorker->Query( pStmt , &pResult );
    if ( NULL == pResult ) return false;

    while ( pResult->NextRow() )
    {
        sint32 idx = 0;
        MissionData.SetMissionID         ( pResult->GetUint32( idx++ ) );
        MissionData.SetMissionState      ( pResult->GetUint8( idx++ ) );
        MissionData.SetMissionTarGet     ( pResult->GetSInt32( idx++ ) );
        MissionData.SetMissionReceiveTime( pResult->GetUint32( idx++ ) );
    }

    pResult->Release();
    pResult = NULL;
    return true;
}

void SubInsertPlayer( void* data )
{
    CRecordPlayerInfo*  pRecord = ( CRecordPlayerInfo* )data;
    if ( NULL == pRecord )  return;
    CDBExecute* pWorker = ThreadsPlayerInfo.GetDBExecute();
    if ( NULL == pWorker )  return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_INSERT_PLAYERINFO );
    if ( NULL == pStmt )    return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pStmt->SetUInt8 ( 1 , pRecord->GetRoleKind() );
    pStmt->SetString( 2 , pRecord->GetLastHost().c_str() );
    pStmt->SetUint32( 3 , pRecord->GetGameTime() );
    pStmt->SetUint32( 4 , pRecord->GetLastLoginTime() );
    pStmt->SetUint32( 5 , pRecord->GetLastOfflineTime() );
    pStmt->SetString( 6 , pRecord->GetNickName().c_str() );
    pStmt->SetUint16( 7 , pRecord->GetHeadID() );
    pWorker->Execute( pStmt );
}

void SubUpdatePlayer( void* data )
{
    CRecordPlayerInfo* pRecord = ( CRecordPlayerInfo* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsPlayerInfo.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_UPDATE_PLAYERINFO );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pStmt->SetString( 1 , pRecord->GetLastHost().c_str() );
    pStmt->SetUint32( 2 , pRecord->GetGameTime() );
    pStmt->SetUint32( 3 , pRecord->GetLastLoginTime() );
    pStmt->SetUint32( 4 , pRecord->GetLastOfflineTime() );
    pStmt->SetString( 5 , pRecord->GetNickName().c_str() );
    pStmt->SetUint16( 6 , pRecord->GetHeadID() );
    pWorker->Execute( pStmt );
}

void SubDeletePlayer( void* data )
{
    CRecordPlayerInfo* pRecord = ( CRecordPlayerInfo* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsPlayerInfo.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_DELETE_PLAYERINFO );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pWorker->Execute( pStmt );
}

void SubInsertItem( void* data )
{
    CRecordItem* pRecord = ( CRecordItem* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsItem.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_INSERT_ITEM );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pStmt->SetUint32( 1 , pRecord->GetItemID() );
    pStmt->SetUint32( 2 , pRecord->GetItemCount() );
    pStmt->SetUint32( 3 , pRecord->GetLastTime() );
    pWorker->Execute( pStmt );
}

void SubUpdateItem( void* data )
{
    CRecordItem* pRecord = ( CRecordItem* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsItem.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_UPDATE_ITEM );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pStmt->SetUint32( 1 , pRecord->GetItemID() );
    pStmt->SetUint32( 2 , pRecord->GetItemCount() );
    pStmt->SetUint32( 3 , pRecord->GetLastTime() );
    pWorker->Execute( pStmt );
}

void SubDeleteItem( void* data )
{
    CRecordItem* pRecord = ( CRecordItem* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsItem.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_DELETE_ITEM );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pWorker->Execute( pStmt );
}

void SubInsertStatistics( void* data )
{
    CRecordStatistics* pRecord = ( CRecordStatistics* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsStatistics.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_INSERT_STATISTICS );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pStmt->SetUint32( 1 , pRecord->GetStatisticsID() );
    pStmt->SetSInt32( 2 , pRecord->GetCount() );
    pWorker->Execute( pStmt );
}

void SubUpdateStatistics( void* data )
{
    CRecordStatistics* pRecord = ( CRecordStatistics* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsStatistics.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_UPDATE_STATISTICS );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pStmt->SetUint32( 1 , pRecord->GetStatisticsID() );
    pStmt->SetSInt32( 2 , pRecord->GetCount() );
    pWorker->Execute( pStmt );
}

void SubDeleteStatistics( void* data )
{
    CRecordStatistics* pRecord = ( CRecordStatistics* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsStatistics.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_DELETE_STATISTICS );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pWorker->Execute( pStmt );
}

void SubInsertMission( void* data )
{
    CRecordMission* pRecord = ( CRecordMission* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsMission.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_DELETE_MISSION );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pStmt->SetUint32( 1 , pRecord->GetMissionID() );
    pStmt->SetUInt8 ( 2 , pRecord->GetMissionState() );
    pStmt->SetSInt32( 3 , pRecord->GetMissionTarGet() );
    pStmt->SetUint32( 4 , pRecord->GetMissionReceiveTime() );
    pWorker->Execute( pStmt );
}

void SubUpdateMission( void* data )
{
    CRecordMission* pRecord = ( CRecordMission* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsMission.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_UPDATE_MISSION );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pStmt->SetUint32( 1 , pRecord->GetMissionID() );
    pStmt->SetUInt8 ( 2 , pRecord->GetMissionState() );
    pStmt->SetSInt32( 3 , pRecord->GetMissionTarGet() );
    pStmt->SetUint32( 4 , pRecord->GetMissionReceiveTime() );
    pWorker->Execute( pStmt );
}

void SubDeleteMission( void* data )
{
    CRecordMission* pRecord = ( CRecordMission* )data;
    if ( NULL == pRecord ) return;
    CDBExecute* pWorker = ThreadsMission.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_DELETE_MISSION );
    if ( NULL == pStmt )   return;

    pStmt->SetUint32( 0 , pRecord->GetRoleID() );
    pWorker->Execute( pStmt );
}

PSE_NAMESPACE_END_DECL