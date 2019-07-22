#ifndef PSE_DB_CONNECT_H_
#define PSE_DB_CONNECT_H_

#include <persistent_service/persistent_service/persistent_service_def.h>

PSE_NAMESPACE_BEGIN_DECL

class CDBConnect : public NLMISC::CSingleton< CDBConnect >
{
public:
    ///  连接数据库;
    void InitDBConnect( NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , uint16 );
    ///  启动数据库线程;
    void StartDBThreads( void );
    ///  关闭数据库线程;
    void CloseDBThreads( void );
    ///  更新子线程数据;
    void FrameMove( void );

    SS_PROPERTY( CDBMysql , ThreadsLoadPlayer   , public );    /// 加载玩家实体线程;( select )
    SS_PROPERTY( CDBMysql , ThreadsPlayerInfo   , public );    /// 玩家基础数据线程;( insert update delete )
    SS_PROPERTY( CDBMysql , ThreadsItem         , public );    /// 道具线程;        ( insert update delete )
    SS_PROPERTY( CDBMysql , ThreadsMission      , public );    /// 任务线程;        ( insert update delete )
    SS_PROPERTY( CDBMysql , ThreadsStatistics   , public );    /// 统计线程;        ( insert update delete )
};

#define DBConnect           PSE::CDBConnect::instance()

#define ThreadsLoadPlayer   DBConnect.m_ThreadsLoadPlayer
#define ThreadsPlayerInfo   DBConnect.m_ThreadsPlayerInfo
#define ThreadsMission      DBConnect.m_ThreadsMission
#define ThreadsItem         DBConnect.m_ThreadsItem
#define ThreadsStatistics   DBConnect.m_ThreadsStatistics

PSE_NAMESPACE_END_DECL

#endif // PSE_DBCONNECT_H_