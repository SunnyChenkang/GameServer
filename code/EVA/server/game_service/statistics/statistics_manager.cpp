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
    CJsonStatisticsCell* pStatisticsCell = JsonStatisticsConfig.GetJsonCell< CJsonStatisticsCell >( StatisticsID );
    if ( NULL == pStatisticsCell )  return;
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer )          return;

    // 构造新统计信息;
    CRecordStatistics RecordStatistics;
    RecordStatistics.SetInsert();
    RecordStatistics.SetRoleID( RoleID );
    RecordStatistics.SetStatisticsID( StatisticsID );
    RecordStatistics.SetCount( Count );
    std::pair< TRecordStatisics::iterator , bool > res = pPlayer->GetRecordStatisics().insert( std::make_pair( StatisticsID , RecordStatistics ) );
    if ( !res.second )
    {
        res.first->second += RecordStatistics;
        res.first->second.SetUpdate();
    }

    // 保存数据库;
    res.first->second.SaveToDataBase();
}

bool CStatisticsManager::IsStatisticsReach( ROLE_ID RoleID , STATISTICS_ID StatisticsID , uint32 Count )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer )
        return false;

    TRecordStatisics::iterator it = pPlayer->GetRecordStatisics().find( StatisticsID );
    if ( it == pPlayer->GetRecordStatisics().end() )
        return false;

    return ( it->second.GetStatisticsID() >= Count );
}

GSE_NAMESPACE_END_DECL