#include "www_threads.h"

SS_NAMESPACE_BEGIN_DECL

CWWWThreads::CWWWThreads( void ) : m_IsExit( true )
                                 , m_Threads( NULL )
{
    
}

void CWWWThreads::PostToMain( CWWWTask* pWWWTask )
{
    bool res = m_MainThreadsQueue.PushBack( pWWWTask );
    if ( res ) return;
    SS_SAFE_DELETE(  pWWWTask );
}

void CWWWThreads::PostToSub( CWWWTask* pWWWTask )
{
    bool res = m_SubThreadsQueue.PushBack( pWWWTask );
    if ( res ) return;
    SS_SAFE_DELETE( pWWWTask );
}

void CWWWThreads::FrameMove( void )
{
    while( true )
    {
        CWWWTask* pWWWTask = m_MainThreadsQueue.BackFront();
        if ( NULL == pWWWTask ) break;
        pWWWTask->TaskEnd();
        SS_SAFE_DELETE( pWWWTask );
    }
}

void CWWWThreads::run( void )
{
    while( true )
    {
        if ( m_IsExit ) break;
        CWWWTask* pWWWTask = m_SubThreadsQueue.BackFront();
        if ( NULL == pWWWTask )
        {
            NLMISC::nlSleep( 3 );
            continue;
        }
        pWWWTask->TaskStart();
        PostToMain( pWWWTask );
    }
}

void CWWWThreads::StartThreads( void )
{
    m_Threads = NLMISC::IThread::create( this );
    if ( NULL == m_Threads ) return;
    m_Threads->start();
    m_IsExit = true;
}

void CWWWThreads::CloseThreads( void )
{
    if ( NULL == m_Threads ) return;
    m_IsExit = false;
    m_Threads->wait();
}


SS_NAMESPACE_END_DECL