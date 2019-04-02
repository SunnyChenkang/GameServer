#ifndef LSE_DB_CONNECT_H_
#define LSE_DB_CONNECT_H_

#include <logger_service/logger_service/logger_service_def.h>

LSE_NAMESPACE_BEGIN_DECL

class CDBConnect : public NLMISC::CSingleton< CDBConnect >
{
public:
    //   连接数据库;
    void InitDBConnect( NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , uint16 );
    //   启动数据库线程;
    void StartDBThreads( void );
    //   关闭数据库线程;
    void CloseDBThreads( void );
    //   更新子线程;
    void FrameMove( void );

    //  线程池;
    SS_PROPERTY( CDBMysql , DBThreads , public );
};

#define DBConnect    CDBConnect::getInstance()
#define DBThreads    DBConnect.m_DBThreads

LSE_NAMESPACE_END_DECL

#endif//LSE_DB_CONNECT_H_