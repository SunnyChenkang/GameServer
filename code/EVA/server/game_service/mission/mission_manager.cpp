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
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) { return; }
    CJsonMissionCell* pMissionCell = JsonMissionConfig.GetJsonCell< CJsonMissionCell >( MissionID );
    if ( NULL == pMissionCell ) { return; }

    /// 检查是否有效任务;
    if ( IsInValidMission( MissionID ) ) { return; }
    /// 任务是否完成;
    if ( IsDoneMission( RoleID , MissionID) )     { return; }
    /// 重置任务信息;
    this->ResetMissionInfo( RoleID , MissionID );

    /// 刷新任务信息;
    CRecordMission* pRecordMission = GetMissionInfo( RoleID , MissionID , true );
    if ( nullptr == pRecordMission ) { return; }
    pRecordMission->SetMissionTarGet( pRecordMission->GetMissionTarGet() + MissionCount );

    /// 检查任务是否完成;

    pRecordMission->SaveDB();
}

void CMissionManager::ResetMissionInfo( ROLE_ID RoleID , MISSION_ID MissionID )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr )    { return; }
    CJsonMissionCell* pMissionCell = JsonMissionConfig.GetJsonCell< CJsonMissionCell >( MissionID );
    if ( nullptr == pMissionCell ) { return; }

    /// 是否每日重置任务;
    if ( !pMissionCell->GetMissionIsDayRefresh() ) { return; }

    /// 重置任务信息;
    CRecordMission* pRecordMission = GetMissionInfo( RoleID , MissionID );
    if ( nullptr == pRecordMission ) { return; }

    /// 检查是否跨天;
    uint32 Time = NLMISC::CTime::getSecondsSince1970();
    CTimeValue LastTime( pRecordMission->GetMissionReceiveTime() );
    CTimeValue CurrTime( Time );
    if ( !IsSameDay( LastTime , CurrTime ) ) { return; }

    /// 更新数据库;
    pRecordMission->SetUpdate();
    pRecordMission->SetMissionTarGet( 0 );
    pRecordMission->SetMissionReceiveTime( Time );
    pRecordMission->SetMissionState( MISSION_STATE_ACCEPT );
    pRecordMission->SaveDB();
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

bool CMissionManager::IsDoneMission( ROLE_ID RoleID , MISSION_ID MissionID )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr )      { return false; }
    CRecordMission* pRecordMission = GetMissionInfo( RoleID , MissionID );
    if ( nullptr == pRecordMission ) { return false; }

    /// 检查任务状态是否完成;
    if ( pRecordMission->GetMissionState() == MISSION_STATE_DONE ) { return true; }
    return false;
}

CRecordMission* CMissionManager::GetMissionInfo( ROLE_ID RoleID , MISSION_ID MissionID , bool IsAdd )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) { return nullptr; }

    TRecordMission& TRecordData = PlayerPtr->GetRecordPlayer().GetRecordMission();
    auto It = TRecordData.find( MissionID );
    if ( It != TRecordData.end() )
    {
        It->second.SetUpdate();
        return &It->second;
    }

    if ( !IsAdd ) return nullptr;
    CRecordMission MissionData;
    MissionData.SetInsert();
    MissionData.SetRoleID( RoleID );
    MissionData.SetMissionID( MissionID );
    auto Res = TRecordData.insert( std::make_pair(MissionID , MissionData) );
    return &Res.first->second;
}

GSE_NAMESPACE_END_DECL