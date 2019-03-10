#include "CPlayerStatistics.h"
#include <game_share/static_table/static_table_mgr.h>


using namespace ATTRIB_TYPE;
using namespace StaticData;


CPlayerStatistics::CPlayerStatistics( void )
{
    m_Statistics.clear();
    m_Random.rand( NLMISC::CTime::getSecondsSince1970() );
}

CPlayerStatistics::~CPlayerStatistics( void )
{

}

void CPlayerStatistics::OnSaveStatisticsData( MsgStatisticsList& data )
{
    for (int i = 0; i < data.statistics_list().size(); i++ )
    {
        const MsgStatisticsInfo& msg_statistics = data.statistics_list(i);

        DB_RECORD::CRecordStatistics StatisticsData;
        StatisticsData.statistics_id = msg_statistics.statistics_id();
        StatisticsData.count         = msg_statistics.count();

        m_Statistics[ StatisticsData.statistics_id ] = StatisticsData;
    }
}

uint32 CPlayerStatistics::GetRandomStatisticsID( void )
{
    DB_RECORD::TRecordStatistics::iterator it = m_Statistics.begin();

    if ( it != m_Statistics.end() )
    {
        int dist = std::distance( it , m_Statistics.end() );
        if ( dist <= 0 ) { 
            return 0;
        }

        int rand_index = ( (dist-1) == 0 ) ? 0 : m_Random.rand(dist - 1);

        std::advance( it , rand_index );

        return it->first;
    }
    return 0;
}
