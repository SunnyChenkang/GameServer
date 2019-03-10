#include "CRobotTimer.h"
#include "CConnect.h"
#include "CClient.h"
#include "CRobotHelper.h"
#include "CClientMgr.h"
#include <server_share/script_mgr.h>

NL_INSTANCE_COUNTER_IMPL( ClientEventTimer );
void ClientEventTimer::timerCallback( CTimer* owner )
{
    owner->setRemaining( m_Time , this );
    LuaParams score_param = ScriptMgr.run( m_UseLuaName , m_UseFunName , LuaParams( (uint32)m_Client->get_session() ) , 0 );
}

NL_INSTANCE_COUNTER_IMPL( ClientBlackJackEventTimer );
void ClientBlackJackEventTimer::timerCallback( CTimer* owner )
{
    owner->setRemaining( m_Time , this );
    LuaParams score_param = ScriptMgr.run( m_UseLuaName , m_UseFunName , LuaParams( (uint32)m_Client->get_session() ) , 0 );
}

NL_INSTANCE_COUNTER_IMPL( ClientSlotEventTimer );
void ClientSlotEventTimer::timerCallback( CTimer* owner )
{
    owner->setRemaining( m_Time , this );
    LuaParams score_param = ScriptMgr.run( m_UseLuaName , m_UseFunName , LuaParams( (uint32)m_Client->get_session() ) , 0 );
}

NL_INSTANCE_COUNTER_IMPL( ClientTexaspokerEventTimer );
void ClientTexaspokerEventTimer::timerCallback( CTimer* owner )
{
    owner->setRemaining( m_Time , this );
    LuaParams score_param = ScriptMgr.run( m_UseLuaName , m_UseFunName , LuaParams( (uint32)m_Client->get_session() ) , 0 );
}

NL_INSTANCE_COUNTER_IMPL( ClientMahJongEventTimer );
void ClientMahJongEventTimer::timerCallback( CTimer* owner )
{
    owner->setRemaining( m_Time , this );
    LuaParams score_param = ScriptMgr.run( m_UseLuaName , m_UseFunName , LuaParams( (uint32)m_Client->get_session() ) , 0 );
}

NL_INSTANCE_COUNTER_IMPL( ClientAutoTimer );

void ClientAutoTimer::timerCallback( CTimer* owner )
{
    owner->setRemaining( ClientMgr->GetLimitTime() , this );

    ClientMgr->AutoLogin();
}


NL_INSTANCE_COUNTER_IMPL( ClientTMailTimer );

void ClientTMailTimer::timerCallback( CTimer* owner )
{
    owner->setRemaining( ClientMgr->GetSendTMailLimitTime(), this );
    ClientMgr->AutoSendTMail();
}

NL_INSTANCE_COUNTER_IMPL( ClientMsgTimer );

void ClientMsgTimer::timerCallback( CTimer* owner )
{
    owner->setRemaining( 1000, this );
    ClientMgr->SetSecondSendMsgCount(true);
}
