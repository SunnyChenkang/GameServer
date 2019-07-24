#ifndef SERVER_SHARED_DBMYSQL_H_
#define SERVER_SHARED_DBMYSQL_H_

#include "db_def.h"
#include "db_connect.h"
#include "db_execute.h"

SS_NAMESPACE_BEGIN_DECL

class CDBMysql : NLMISC::IRunnable
{
public:
    CDBMysql( void ) : m_Exit( true )
                     , m_Threads( NULL )
    {
        mysql_library_init( 0 , NULL , NULL );
        mysql_thread_init();
    };
    virtual ~CDBMysql( void )
    {
        mysql_thread_end();
        mysql_library_end();
    };

    //   connect;
    bool Connect( NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , uint16 , INIT_SQL_WORKER );
    //   start threads;
    void StartThreads( void );
    //   close;
    void CloseThreads( void );
    //   update;
    void FrameMove( void );
    //   post main threads;
    void PostToMain( CRecordBase* , PROC_MSG );
    //   post sub threads;
    void PostToSub ( CRecordBase* , PROC_MSG );

    //   sub  threads event size;
    uint32 SubEventSize ( void ){ return m_MainThreads.Size(); }
    //   main threads event size;
    uint32 MainEventSize( void ){ return m_SubThreads.Size();  }

    //   db execute;
    CDBExecute* GetDBExecute( bool isMain = false ) { return isMain ? &m_MainWorker : &m_SubWorker; }

private:
    CDBExecute  m_MainWorker;
    CDBExecute  m_SubWorker;

protected:
    //   run;
    void run( void );

    SS_PROPERTY( NLMISC::IThread*   , Threads                       , private );
    SS_PROPERTY( NLMISC::CSString   , Host                          , private );
    SS_PROPERTY( NLMISC::CSString   , User                          , private );
    SS_PROPERTY( NLMISC::CSString   , Password                      , private );
    SS_PROPERTY( NLMISC::CSString   , DBName                        , private );
    SS_PROPERTY( uint16             , Port                          , private );
    SS_PROPERTY( bool               , Exit                          , private );
    SS_PROPERTY( INIT_SQL_WORKER    , Worker                        , private );
    SS_PROPERTY( CDoubleBufferFifo<DBExecuteData> , MainThreads     , private );
    SS_PROPERTY( CDoubleBufferFifo<DBExecuteData> , SubThreads      , private );
};

SS_NAMESPACE_END_DECL

#endif //SERVER_SHARED_DBMYSQL_H_