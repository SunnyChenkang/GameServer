#ifndef SERVER_WWW_THREADS_H_
#define SERVER_WWW_THREADS_H_

#include "www_task.h"
#include <server_share/buffer/buffer_fifo.h>

SS_NAMESPACE_BEGIN_DECL

class CWWWThreads : public NLMISC::IRunnable
{
public:
    CWWWThreads( void );
    virtual ~CWWWThreads( void ) { };

    void PostToMain( CWWWTask* );
    void PostToSub ( CWWWTask* );
    void FrameMove ( void );

    void StartThreads( void );
    void CloseThreads( void );

protected:
    void run( void );

    SS_PROPERTY( volatile bool                  , IsExit           , private );
    SS_PROPERTY( CDoubleBufferFifo< CWWWTask >  , MainThreadsQueue , private );
    SS_PROPERTY( CDoubleBufferFifo< CWWWTask >  , SubThreadsQueue  , private );
    SS_PROPERTY( NLMISC::IThread*               , Threads          , private );
};

SS_NAMESPACE_END_DECL

#endif//SERVER_WWW_THREADS_H_;