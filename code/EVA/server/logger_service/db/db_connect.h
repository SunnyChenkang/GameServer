#ifndef LSE_DB_CONNECT_H_
#define LSE_DB_CONNECT_H_

#include <logger_service/logger_service/logger_service_def.h>

LSE_NAMESPACE_BEGIN_DECL

class CDBConnect : public NLMISC::CSingleton< CDBConnect >
{
public:
    typedef std::vector< CDBMysql > DB_MYSQL_TABLE;

    CDBConnect( void );
   ~CDBConnect( void );

    ///  连接数据库;
    void InitDBConnect( NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , uint16 , uint16 );
    ///  启动数据库线程;
    void StartDBThreads( void );
    ///  关闭数据库线程;
    void CloseDBThreads( void );
    ///  更新子线程;
    void FrameMove( void );

    ///  获取DB;
    CDBMysql& GetDBMysql( sint8 idx ) { return m_DBThreads[idx]; }
    ///  获取线程ID;
    sint8 GetThreadsIdx( void );

    SS_PROPERTY( DB_MYSQL_TABLE , DBThreads     , public  );    /// 线程池;
    SS_PROPERTY( CRandom        , Random        , private );
};

#define DBConnect    CDBConnect::getInstance()

LSE_NAMESPACE_END_DECL

#endif//LSE_DB_CONNECT_H_