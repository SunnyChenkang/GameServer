#ifndef __RECIVER_THREAD_H_
#define __RECIVER_THREAD_H_

#include "revolver/base_namespace.h"
#include "revolver/base_typedef.h"
#include "revolver/base_thread.h"
#include "revolver/base_singleton.h"

using namespace BASE;

class RecvThread : public CThread
{
public:
    RecvThread( void );
   ~RecvThread( void );

    void execute( void );

};

#define CREATE_RECV_THREAD  CRUDPSingleton<RecvThread>::instance
#define RECV_THREAD         CRUDPSingleton<RecvThread>::instance
#define DESTROY_RECV_THREAD CRUDPSingleton<RecvThread>::destroy

#endif // __RECIVER_THREAD_H_;