#include "db_connect.h"
#include "db_worker.h"

PSE_NAMESPACE_BEGIN_DECL

void CDBConnect::InitDBConnect( NLMISC::CSString Host , NLMISC::CSString User , NLMISC::CSString Password , NLMISC::CSString DBName , uint16 DBPort )
{
    m_ThreadsLoadPlayer.Connect( Host , User , Password , DBName , DBPort , (INIT_SQL_WORKER)InitLoadPlayer         );
    m_ThreadsPlayerInfo.Connect( Host , User , Password , DBName , DBPort , (INIT_SQL_WORKER)InitPlayerInfoWoker    );
    m_ThreadsItem.Connect      ( Host , User , Password , DBName , DBPort , (INIT_SQL_WORKER)InitItemWorker         );
    m_ThreadsMission.Connect   ( Host , User , Password , DBName , DBPort , (INIT_SQL_WORKER)InitMissionWorker      );
    m_ThreadsStatistics.Connect( Host , User , Password , DBName , DBPort , (INIT_SQL_WORKER)InitStatisticsWorker   );
}

void CDBConnect::StartDBThreads( void )
{
    m_ThreadsLoadPlayer.StartThreads();
    m_ThreadsPlayerInfo.StartThreads();
    m_ThreadsItem.StartThreads();
    m_ThreadsMission.StartThreads();
    m_ThreadsStatistics.StartThreads();
}

void CDBConnect::CloseDBThreads( void )
{
    m_ThreadsLoadPlayer.CloseThreads();
    m_ThreadsPlayerInfo.CloseThreads();
    m_ThreadsItem.CloseThreads();
    m_ThreadsMission.CloseThreads();
    m_ThreadsStatistics.CloseThreads();
}

void CDBConnect::FrameMove(void)
{
    m_ThreadsLoadPlayer.FrameMove();
    m_ThreadsPlayerInfo.FrameMove();
    m_ThreadsItem.FrameMove();
    m_ThreadsMission.FrameMove();
    m_ThreadsStatistics.FrameMove();
}

PSE_NAMESPACE_END_DECL

