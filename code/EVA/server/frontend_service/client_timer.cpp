#include "client_timer.h"
extern NLMISC::CVariable< uint32 > VAR_FES_CHECK_WAIT_CONNECTION_TIME;
extern SS::CDBMysql* m_FesMysql;

FES_NAMESPACE_BEGIN_DECL

NL_INSTANCE_COUNTER_IMPL( CClientConnectionTimer )

void CClientConnectionTimer::timerCallback( CTimer* owner )
{
    //ClientManager.CheckConnectionTimeOut();
    owner->setRemaining( VAR_FES_CHECK_WAIT_CONNECTION_TIME.get() , this );
}

FES_NAMESPACE_END_DECL