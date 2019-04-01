#ifndef FRONTEND_SERVICE_CLIENTTIMER_H_
#define FRONTEND_SERVICE_CLIENTTIMER_H_

#include "frontend_def.h"
#include "client_manager.h"

FES_NAMESPACE_BEGIN_DECL

// 检查连接超时用户;
class CClientConnectionTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( CClientConnectionTimer );
public:
    CClientConnectionTimer( void ) { };
    void timerCallback( CTimer* owner );
};

FES_NAMESPACE_END_DECL

#endif //FRONTEND_SERVICE_CLIENTTIMER_H_;