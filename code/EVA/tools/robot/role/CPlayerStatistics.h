#ifndef CPlayerStatistics_h
#define CPlayerStatistics_h

#include <game_share/game_def.h>
#include <server_share/database/db_logic_chunk.h>
#include <nel/misc/random.h>
#include "../CRobotHelper.h"

class CPlayerStatistics
{
public:

    CPlayerStatistics( void );
    virtual ~CPlayerStatistics( void );

    // 保存任务;
    void OnSaveStatisticsData( MsgStatisticsList& data );

    // 任务领取完奖励;
    uint32 GetRandomStatisticsID( void );
private:

protected:
    // 统计信息;
    DB_RECORD::TRecordStatistics     m_Statistics;
    // 随机数;
    NLMISC::CRandom                  m_Random;
};

#endif // CPlayerStatistics_h