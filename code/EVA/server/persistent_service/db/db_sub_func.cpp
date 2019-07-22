#include "db_sub_func.h"
#include "db_main_func.h"
#include "db_connect.h"

PSE_NAMESPACE_BEGIN_DECL

void SubLoadPlayerEntity( void* data )
{
    SyncLoadPlayerData* pSyncLoadData = ( SyncLoadPlayerData* )data;
    if ( NULL == pSyncLoadData ) return;
    pSyncLoadData->m_RecordPlayer.GetRecordBasePlayer().SetRoleID( pSyncLoadData->GetRoleID() );

    /// 查询角色是否存在;
    CDBExecute* pWorker = ThreadsLoadPlayer.GetDBExecute();
    if ( NULL == pWorker ) return;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_IS_EXIST_PLAYER );
    if ( NULL == pStmt   ) return;
    CDBResult* pResult = NULL;
    pStmt->SetUint32( 0 , pSyncLoadData->GetRoleID() );
    pWorker->Query( pStmt , &pResult );
    size_t ResultCount = pResult->GetCount();
    pResult->Release();

    /// 用户创建角色;
    if ( ResultCount <= 0 )
    {
        ThreadsLoadPlayer.PostToMain( new SyncLoadPlayerData( *pSyncLoadData ) , (PROC_MSG)MainCreateRole );
        return;
    }

    /// 加载角色实体;
    SubLoadPlayer    ( pSyncLoadData->m_RecordPlayer );   // 加载玩家信息;
    SubLoadItem      ( pSyncLoadData->m_RecordPlayer );   // 加载道具信息;
    SubLoadStatistics( pSyncLoadData->m_RecordPlayer );   // 加载统计信息;
    SubLoadMission   ( pSyncLoadData->m_RecordPlayer );   // 加载任务信息;

    /// 投递主线程;
    ThreadsLoadPlayer.PostToMain( new SyncLoadPlayerData( *pSyncLoadData ) , (PROC_MSG)MainLoadPlayerEntity );
}

bool SubLoadPlayer( CRecordPlayer& RecordPlayer )
{
    CDBExecute* pWorker = ThreadsLoadPlayer.GetDBExecute();
    if ( NULL == pWorker ) return false;
    CDBStatement* pStmt = pWorker->GetStmt( SQL_STMT_LOAD_PLAYERINFO );
    if ( NULL == pStmt )   return false;

    CRecordPlayerInfo& RecordPlayerInfo = RecordPlayer.GetRecordBasePlayer();

    CDBResult* pResult = NULL;
    pStmt->SetUint32( 0 , RecordPlayerInfo.GetRoleID() );
    pWorker->Query( pStmt , &pResult );
    if ( NULL == pResult ) return false;

    RecordPlayerInfo.SetRoleID         ( pResult->GetUint32( 0 ) );
    RecordPlayerInfo.SetRoleKind       ( pResult->GetUint8 ( 1 ) );
    RecordPlayerInfo.SetLastHost       ( pResult->GetString( 2 ).second );
    RecordPlayerInfo.SetGameTime       ( pResult->GetUint32( 3 ) );
    RecordPlayerInfo.SetLastLoginTime  ( pResult->GetUint32( 4 ) );
    RecordPlayerInfo.SetLastOfflineTime( pResult->GetUint32( 5 ) );
    RecordPlayerInfo.SetCreateTime     ( pResult->GetUint32( 6 ) );
    RecordPlayerInfo.SetNickName       ( pResult->GetString( 7 ).second );
    RecordPlayerInfo.SetHeadID         ( pResult->GetUint16( 8 ) );

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

    CDBResult* pResult = NULL;
    pStmt->SetUint32( 0 , RecordPlayer.GetRecordBasePlayer().GetRoleID() );
    pWorker->Query( pStmt , &pResult );
    if ( NULL == pResult ) return false;

    while ( pResult->NextRow() )
    {
        CRecordItem ItemData;
        ItemData.SetRoleID( RecordPlayer.GetRecordBasePlayer().GetRoleID() );
        ItemData.SetItemID      ( pResult->GetUint32( 0 ) );
        ItemData.SetItemCount   ( pResult->GetUint32( 1 ) );
        ItemData.SetLastTime    ( pResult->GetUint32( 2 ) );
        RecordPlayer.GetRecordItem().insert( std::make_pair(  ItemData.GetItemID() , ItemData ) );
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

    CDBResult* pResult = NULL;
    pStmt->SetUint32( 0 , RecordPlayer.GetRecordBasePlayer().GetRoleID() );
    pWorker->Query( pStmt , &pResult );
    if ( NULL == pResult ) return false;

    while ( pResult->NextRow() )
    {
        CRecordStatistics StatisticsData;
        StatisticsData.SetRoleID( RecordPlayer.GetRecordBasePlayer().GetRoleID() );
        StatisticsData.SetStatisticsID( pResult->GetUint32( 0 ) );
        StatisticsData.SetCount       ( pResult->GetUint32( 1 ) );
        RecordPlayer.GetRecordStatisics().insert( std::make_pair( StatisticsData.GetStatisticsID() , StatisticsData ) );
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

    CDBResult* pResult = NULL;
    pStmt->SetUint32( 0 , RecordPlayer.GetRecordBasePlayer().GetRoleID() );
    pWorker->Query( pStmt , &pResult );
    if ( NULL == pResult ) return false;

    while ( pResult->NextRow() )
    {
        CRecordMission MissionData;
        MissionData.SetRoleID( RecordPlayer.GetRecordBasePlayer().GetRoleID() );
        MissionData.SetMissionID         ( pResult->GetUint32( 0 ) );
        MissionData.SetMissionState      ( pResult->GetUint8 ( 1 ) );
        MissionData.SetMissionTarGet     ( pResult->GetSInt32( 2 ) );
        MissionData.SetMissionReceiveTime( pResult->GetUint32( 3 ) );
        RecordPlayer.GetRecordMission().insert( std::make_pair( MissionData.GetMissionID() , MissionData ));
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