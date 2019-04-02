#ifndef GSE_STATISTICS_MANAGER_H_
#define GSE_STATISTICS_MANAGER_H_

#include <server_share/common/common.h>

GSE_NAMESPACE_BEGIN_DECL

class CStatisticsManager : public NLMISC::CSingleton< CStatisticsManager >
{
public:
    //   更新统计次数;
    void UpdateStatistics( ROLE_ID , STATISTICS_ID );
    void UpdateStatistics( ROLE_ID , STATISTICS_ID , uint32 );

    //   统计是否达成;
    bool IsStatisticsReach( ROLE_ID , STATISTICS_ID , uint32 );
};

#define StatisticsManager CStatisticsManager::getInstance();

GSE_NAMESPACE_END_DECL

#endif//GSE_STATISTICS_MANAGER_H_