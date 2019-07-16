#include "db_mysql.h"

bool SS::CDBMysql::Connect( NLMISC::CSString Host , NLMISC::CSString User, NLMISC::CSString PassWord, NLMISC::CSString DBName, uint16 Port , INIT_SQL_WORKER Worker )
{
    bool result = m_MainWorker.Connect( Host , User , PassWord , DBName , Port );
    if ( !result ) return result;
    if ( NULL != Worker ) { (*Worker)(&m_MainWorker); }

    m_Host      = Host;
    m_User      = User;
    m_Password  = PassWord;
    m_DBName    = DBName;
    m_Port      = Port;
    m_Worker    = Worker;

    return result;
}

void SS::CDBMysql::CloseThreads( void )
{
    while ( SubEventSize() > 0 ) { NLMISC::nlSleep( 3 ); }
    if ( NULL == m_Threads ) return;
    m_Threads->wait();
    m_Exit = true;
}

void SS::CDBMysql::StartThreads( void )
{
    m_Threads = NLMISC::IThread::create( this );
    if ( NULL == m_Threads ) return;
    m_Threads->start();
    m_Exit = false;
}

void SS::CDBMysql::FrameMove( void )
{
    while ( true )
    {
        DBExecuteData* pMessage = m_SubThreads.BackFront();
        if ( NULL == pMessage ) break;
        if ( NULL == pMessage->func ) break;
        ( *pMessage->func )( pMessage->data );
        SS_SAFE_DELETE( pMessage->data );
        SS_SAFE_DELETE( pMessage );
    }
}

void SS::CDBMysql::run( void )
{
    mysql_thread_init();

    bool result = m_SubWorker.Connect( m_Host.c_str() , m_User.c_str() , m_Password.c_str(), m_DBName.c_str(), m_Port );
    if ( !result )
    {
        nlerror( "mysql connect failes host=%s , user=%s , pwd = %s , db = %s , port = %d " , m_Host.c_str() , m_User.c_str() , m_Password.c_str() , m_DBName.c_str() , m_Port );
        return;
    }

    if ( NULL != m_Worker ) { (*m_Worker)(&m_SubWorker); }

    while ( true )
    {
        DBExecuteData* pMessage = m_MainThreads.BackFront();
        if ( NULL != pMessage && NULL != pMessage->func )
        {
            ( *pMessage->func )( pMessage->data );
            SS_SAFE_DELETE( pMessage->data );
            SS_SAFE_DELETE( pMessage );
        }
        else if ( m_Exit ) { break; }
        else
        {
            NLMISC::nlSleep( 3 );
        }
    }
    mysql_thread_end();
}

void SS::CDBMysql::PostToMain( CRecordBase* pRecordBase , PROC_MSG CallBack )
{
    DBExecuteData* pExecuteData = new  ( std::nothrow ) DBExecuteData();
    if ( NULL == pExecuteData )
    {
        SS_SAFE_DELETE( pRecordBase );
        return;
    }
    pExecuteData->data = pRecordBase;
    pExecuteData->func = CallBack;
    bool Result = m_SubThreads.PushBack( pExecuteData );
    if ( Result ) return;

    SS_SAFE_DELETE( pRecordBase  );
    SS_SAFE_DELETE( pExecuteData );
}

void SS::CDBMysql::PostToSub( CRecordBase* pRecordBase , PROC_MSG CallBack )
{
    DBExecuteData* pExecuteData = new ( std::nothrow ) DBExecuteData();
    if ( NULL == pExecuteData )
    {
        SS_SAFE_DELETE( pRecordBase );
        return;
    }

    pExecuteData->data = pRecordBase;
    pExecuteData->func = CallBack;
    bool Result = m_MainThreads.PushBack( pExecuteData );
    if ( Result ) return;
    SS_SAFE_DELETE( pRecordBase  );
    SS_SAFE_DELETE( pExecuteData );
}
