#include "client_timer.h"

FES_NAMESPACE_BEGIN_DECL

NL_INSTANCE_COUNTER_IMPL( CClientConnectionTimer )
NL_INSTANCE_COUNTER_IMPL( CClientDataRedisTimer  )

void CClientConnectionTimer::timerCallback( CTimer* owner )
{

}

void CClientDataRedisTimer::timerCallback( CTimer* owner )
{

}

FES_NAMESPACE_END_DECL