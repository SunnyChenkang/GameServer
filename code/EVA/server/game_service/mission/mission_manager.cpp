#include "mission_manager.h"
#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>
#include <server_share/time_value/time_value.h>

GSE_NAMESPACE_BEGIN_DECL

void CMissionManager::UpdateMission( ROLE_ID RoleID , MISSION_ID MissionID )
{
    this->UpdateMission( RoleID , MissionID , 1 );
}

void CMissionManager::UpdateMission( ROLE_ID RoleID , MISSION_ID MissionID , uint32 MissionCount )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer )      return;
    CJsonMissionCell* pMissionCell = JsonMissionConfig.GetJsonCell< CJsonMissionCell >( MissionID );
    if ( NULL == pMissionCell ) return;

    // 检查是否有效任务;
    if ( IsInValidMission( MissionID ) )    return;
    // 任务是否完成;
    if ( IsDoneMission( MissionID) )        return;

    // 构造新任务;
    CRecordMission RecordMission;
    RecordMission.SetInsert();
    RecordMission.SetRoleID( RoleID );
    RecordMission.SetMissionID( MissionID );
    RecordMission.SetMissionState( MISSION_STATE_ACCEPT );
    RecordMission.SetMissionTarGet( MissionCount );

    // 重置任务;
    this->ResetMission( RoleID , MissionID );

    // 插入新任务;
    std::pair< TRecordMission::iterator , bool > res = pPlayer->GetRecordMission().insert( std::make_pair( MissionID , RecordMission ) );
    if ( !res.second )
    {
        res.first->second += RecordMission;
        res.first->second.SetUpdate();
    }
    // 检查任务是否完成;
    if ( res.first->second.GetMissionTarGet() >= pMissionCell->GetMissionCount() )
    {
        RecordMission.SetMissionState( MISSION_STATE_DONE );
        RecordMission.SetMissionTarGet( pMissionCell->GetMissionCount() );
    }
    // 保存数据库;
    res.first->second.SaveToDataBase();
}

void CMissionManager::ResetMission( ROLE_ID RoleID , MISSION_ID MissionID )
{
    CJsonMissionCell* pMissionCell = JsonMissionConfig.GetJsonCell< CJsonMissionCell >( MissionID );
    if ( NULL == pMissionCell ) return;
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer )      return;

    // 是否每日重置任务;
    if ( !pMissionCell->GetMissionIsDayRefresh() ) return;
    TRecordMission::iterator it = pPlayer->GetRecordMission().find( MissionID );
    if ( it == pPlayer->GetRecordMission().end() )
        return;

    // 检查是否跨天;
    CTimeValue LastTime( it->second.GetMissionReceiveTime() );
    CTimeValue CurrTime( NLMISC::CTime::getSecondsSince1970() );
    if ( !IsSameDay( LastTime , CurrTime ) )
        return;

    // 重置任务状态;
    it->second.SetMissionTarGet( 0 );
    it->second.SetMissionReceiveTime( NLMISC::CTime::getSecondsSince1970() );
    it->second.SetMissionState( MISSION_STATE_ACCEPT );
    it->second.SaveToDataBase();
}

bool CMissionManager::IsInValidMission( MISSION_ID MissionID )
{
    CJsonMissionCell* pMissionCell = JsonMissionConfig.GetJsonCell< CJsonMissionCell >( MissionID );
    if ( NULL == pMissionCell )
        return true;

    // 检查任务时间;
    uint32 CurrTime = NLMISC::CTime::getSecondsSince1970();
    if ( CurrTime < pMissionCell->GetMissionStartTime() ) return true;
    if ( CurrTime > pMissionCell->GetMissionEndTime()   ) return true;
    return false;
}

bool CMissionManager::IsDoneMission( MISSION_ID MissionID )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( MissionID );
    if ( NULL == pPlayer )
        return false;

    // 检查任务是否完成;
    TRecordMission::iterator it = pPlayer->GetRecordMission().find( MissionID );
    if ( it == pPlayer->GetRecordMission().end() )            return false;
    if ( it->second.GetMissionState() != MISSION_STATE_DONE ) return false;
    return true;
}

GSE_NAMESPACE_END_DECL