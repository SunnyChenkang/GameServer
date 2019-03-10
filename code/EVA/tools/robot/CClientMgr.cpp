#include "CClientMgr.h"
#include "CClient.h"
#include "CRobotTimer.h"
#include "CCommonLine.h"
#include <nel/misc/sstring.h>
#include <server_share/server_def.h>
#include "msg/send_logic.h"

 
NLMISC::CVariable<uint32>    VAR_PLAYER_NUM("robot", "NbPlayers"  , "memo", 0);
NLMISC::CVariable<uint>      VAR_SECOND_MSG("robot", "SecondMsg"  , "memo", 0);

CClientMgr::CClientMgr( void )
{
    m_Random.srand( NLMISC::CTime::getLocalTime() );
    m_ClientTabMgr.clear();
    m_ClientQueueMgr.clear();
    m_unLoginLimitTime = Config.getVar( "LoginLimitTime" ).asInt();
    m_unLoginCountMax = Config.getVar( "LoginCountMax" ).asInt();
    m_EveryTimeLoginCount = Config.getVar( "EveryTimeLoginCount" ).asInt();
    m_LoginStartAccount = Config.getVar( "LoginStartAccount" ).asInt();
    m_unSendTMailLimitTime = Config.getVar( "SendTMailLimitTime" ).asInt();
    m_unCurrLoginCountMax = m_LoginStartAccount;
}

CClientMgr::~CClientMgr( void )
{

}

CClient* CClientMgr::AllocClient( void )
{
    CClient* pClient = new( std::nothrow )CClient();
    if ( NULL == pClient )
        return NULL;

    m_ClientQueueMgr.push_back( pClient );

    return pClient;
}

bool CClientMgr::InsertClient( DEF::RPC_SESSION SessionID , CClient* pClient )
{
    ClientMgrTab::iterator it = m_ClientTabMgr.find( SessionID );

    if ( it != m_ClientTabMgr.end() )
        return false;

    m_ClientTabMgr[ SessionID ] = pClient;
    return true;
}


CClient* CClientMgr::FindClient( DEF::RPC_SESSION SessionID )
{
    ClientMgrTab::iterator it = m_ClientTabMgr.find( SessionID );
    if ( it == m_ClientTabMgr.end() )
        return NULL;

    VAR_PLAYER_NUM.set(m_ClientTabMgr.size());
    return it->second;
}

void CClientMgr::RemoveClient( DEF::RPC_SESSION  SessionID )
{
    ClientMgrTab::iterator it = m_ClientTabMgr.find( SessionID );
    if ( it == m_ClientTabMgr.end() )
        return;

    safe_delete( it->second );
    m_ClientTabMgr.erase( it );
}

void CClientMgr::ClearClient( void )
{
    ClientMgrTab::iterator it = m_ClientTabMgr.begin();

    for( ; it != m_ClientTabMgr.end(); )
    {
        safe_delete( it->second );
        m_ClientTabMgr.erase( it++ );
    }

    m_ClientQueueMgr.clear();
}

CClient* CClientMgr::GetRandomClient( void )
{
    if ( m_ClientTabMgr.empty() )
        return NULL;

    int count = CLIENT_RANDOM_NUM;

    while ( count-- )
    {
        ClientMgrTab::iterator it = m_ClientTabMgr.begin();
        int dist = std::distance( m_ClientTabMgr.begin() , m_ClientTabMgr.end() );

        int rand_index = ( (dist-1) == 0 ) ? 0 : m_Random.rand(dist - 1);

        std::advance( it , rand_index );

        if ( it->second->IsOnlineState() )
        {
            return it->second;
        }
    }

    return NULL;
}

void CClientMgr::OnUpdate( void )
{
    for ( ClientMgrQueue::iterator it = m_ClientQueueMgr.begin(); it != m_ClientQueueMgr.end(); ++it )
    {
        CClient* pClient = (*it);
        if ( NULL == pClient ) {
            continue;
        }

        pClient->OnUpdate();
    }

    for ( ClientMgrTab::iterator it = m_ClientTabMgr.begin(); it != m_ClientTabMgr.end(); ++it )
    {
        CClient* pClient = it->second;
        if ( NULL == pClient )
            continue;

        pClient->OnUpdate();
    }
}

void CClientMgr::CreateTimer( void )
{
    CTimer* pTimer = new CTimer();

    pTimer->setRemaining( m_unLoginLimitTime , new ClientAutoTimer() );
}

void CClientMgr::AutoLogin( void )
{
    // 删掉旧客户端;
    ClearClient();

    // 创建账号;
    int i = 1;
    while( i <= m_EveryTimeLoginCount )
    {
        if ( m_unCurrLoginCountMax > m_unLoginCountMax ) {
            nlwarning(" To Start Again Robot, m_unCurrLoginCountMax = %d, m_unLoginCountMax = %d \n", m_unCurrLoginCountMax, m_unLoginCountMax );
            m_unCurrLoginCountMax = m_LoginStartAccount;
        }

        char buff[128] = {'\0'};
        NLMISC::smprintf( buff , sizeof( buff ) , "test%d" , m_unCurrLoginCountMax );

        //std::string user_name;
        //for (int index = 0; index < USERNAMELENGTH; ++index )
        //{
        //    user_name += UserNameTable[m_Random.rand(25)];
        //}
        CommonLine->PushLoginAccount( buff );

        ++m_unCurrLoginCountMax;
        ++i;
    }
}

void CClientMgr::CreateTimerSendTMail( void )
{
    CTimer* pTimer = new CTimer();

    pTimer->setRemaining( m_unSendTMailLimitTime , new ClientTMailTimer() );
}

void CClientMgr::AutoSendTMail( void )
{
    CClient* pClient = GetRandomClient();
    if ( NULL != pClient )
    {
        //pClient->GetSendLogic()->SendTemplateMail();
    }
}

void CClientMgr::CreateMsgTimer( void )
{
    CTimer* pTimer = new CTimer();

    pTimer->setRemaining( 1000 , new ClientMsgTimer() );
}

void CClientMgr::SetSecondSendMsgCount( bool bClear/*=false*/ )
{
    if ( bClear )
    {
        VAR_SECOND_MSG.set( 0 );
    }
    else
    {
        VAR_SECOND_MSG.set( VAR_SECOND_MSG.get()+1 );
    }
}

