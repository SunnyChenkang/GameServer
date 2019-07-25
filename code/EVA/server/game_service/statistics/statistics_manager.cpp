#include "statistics_manager.h"
#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>

GSE_NAMESPACE_BEGIN_DECL

void CStatisticsManager::UpdateStatistics( ROLE_ID RoleID , STATISTICS_ID StatisticsID )
{
    this->UpdateStatistics( RoleID , StatisticsID , 1 );
}

void CStatisticsManager::UpdateStatistics( ROLE_ID RoleID , STATISTICS_ID StatisticsID , uint32 Count )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr )     { return; }
    CJsonStatisticsCell* pStatisticsCell = JsonStatisticsConfig.GetJsonCell< CJsonStatisticsCell >( StatisticsID );
    if ( NULL == pStatisticsCell )  { return; }

    CRecordStatistics* pRecordStatistics = GetStatistics( RoleID , StatisticsID , true );
    if ( nullptr == pRecordStatistics ) { return; }
    pRecordStatistics->SetCount( pRecordStatistics->GetCount() + Count );

    /// ±£´æÊý¾Ý¿â;
    pRecordStatistics->SaveDB();
}

bool CStatisticsManager::IsStatisticsReach( ROLE_ID RoleID , STATISTICS_ID StatisticsID , uint32 Count )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr )         { return false; }
    CRecordStatistics* pRecordStatistics = GetStatistics( RoleID , StatisticsID , false );
    if ( nullptr == pRecordStatistics ) { return false; }

    return ( pRecordStatistics->GetCount() >= Count );
}

CRecordStatistics* CStatisticsManager::GetStatistics( ROLE_ID RoleID , STATISTICS_ID StatisticsID , bool IsAdd /*= false */ )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) { return nullptr; }

    TRecordStatisics& TRecordData = PlayerPtr->GetRecordPlayer().GetRecordStatisics();
    auto It = TRecordData.find( StatisticsID );
    if ( It != TRecordData.end() )
    {
        It->second.SetUpdate();
        return &It->second;
    }

    if ( !IsAdd ) return nullptr;
    CRecordStatistics StatisticsData;
    StatisticsData.SetInsert();
    StatisticsData.SetRoleID( RoleID );
    StatisticsData.SetStatisticsID( StatisticsID );
    auto Res = TRecordData.insert( std::make_pair(StatisticsID , StatisticsData) );
    return &Res.first->second;
}

GSE_NAMESPACE_END_DECL