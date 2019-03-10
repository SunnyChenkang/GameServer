#include "revolver/base_reactor_instance.h"
#include "reciver_thread.h"

RecvThread::RecvThread( void )
{

}
RecvThread::~RecvThread( void )
{

}

void RecvThread::execute( void )
{
    while ( !get_terminated() )
    {
        REACTOR_INSTANCE()->event_loop();
    }

    // 停止线程运行;
    REACTOR_INSTANCE()->stop_event_loop();
    // 关闭线程;
    clear_thread();
}