#include "client_manager.h"
#include "client.h"
#include "frontend_network.h"
#include "client_timer.h"

extern NLMISC::CVariable< uint32 > VAR_FES_WAIT_CONNECTION_TIMEROUT;
extern NLMISC::CVariable< uint32 > VAR_FES_MAX_CLIENTCOUNT;
extern NLMISC::CVariable< uint32 > VAR_FES_CHECK_WAIT_CONNECTION_TIME;
FES_NAMESPACE_BEGIN_DECL

CClientManager::CClientManager( void )
{
    m_RUDPSocketTable.clear();
    m_WEBSocketTable.clear();
    m_ClientTable.clear();
    //m_ConnectionTimer.setRemaining( VAR_FES_CHECK_WAIT_CONNECTION_TIME.get() , new CClientConnectionTimer() );
}

CClient* CClientManager::AllocClient( SOCKET_ID SocketID )
{
    // 检查客户端数量;
    if ( GetClientCount() >= VAR_FES_MAX_CLIENTCOUNT.get() )
    {
        nlinfo( " client connection number exceeding normal value %d" , VAR_FES_MAX_CLIENTCOUNT.get() );
        return NULL;
    }

    CClient* pClient = new ( std::nothrow ) CClient();
    if ( NULL == pClient ) return NULL;
    std::pair< RUDPSOCKETTABLE::iterator , bool > res = m_RUDPSocketTable.insert( std::make_pair( SocketID , pClient ) );
    if ( !res.second )
    {
        SS_SAFE_DELETE( pClient );
        return pClient;
    }
    pClient->SetRSocketID( SocketID );
    pClient->SetChannelNet( RUDP_CHANNEL );
    pClient->SetConnectionTime( NLMISC::CTime::getSecondsSince1970() );
    return pClient;
}

CClient* CClientManager::AllocClient( NLNET::TSockId SocketID )
{
    // 检查客户端数量;
    if ( GetClientCount() >= VAR_FES_MAX_CLIENTCOUNT.get() )
    {
        nlinfo( " client connection number exceeding normal value %d" , VAR_FES_MAX_CLIENTCOUNT.get() );
        return NULL;
    }

    CClient* pClient = new ( std::nothrow ) CClient();
    if ( NULL == pClient ) return NULL;
    std::pair< WEBSOCKETTABLE::iterator , bool > res = m_WEBSocketTable.insert( std::make_pair( SocketID , pClient ));
    if ( !res.second )
    {
        SS_SAFE_DELETE( pClient );
        return NULL;
    }

    pClient->SetWScoketID( SocketID );
    pClient->SetChannelNet( WEB_CHANNEL );
    pClient->SetConnectionTime( NLMISC::CTime::getSecondsSince1970() );

    return pClient;
}

CClient* CClientManager::FindClient( SOCKET_ID SocketID )
{
    RUDPSOCKETTABLE::iterator it = m_RUDPSocketTable.find( SocketID );
    if ( it == m_RUDPSocketTable.end() ) return NULL;
    return it->second;
}

CClient* CClientManager::FindClient( NLNET::TSockId& ScoketID )
{
    WEBSOCKETTABLE::iterator it = m_WEBSocketTable.find( ScoketID );
    if ( it == m_WEBSocketTable.end() ) return NULL;
    return it->second;
}

CClient* CClientManager::FindClientRoleID( ROLE_ID RoleID )
{
    CLIENTTABLE::iterator it = m_ClientTable.find( RoleID );
    if ( it == m_ClientTable.end() ) return NULL;
    return it->second;
}

void CClientManager::DeleteClient( SOCKET_ID SocketID )
{
    RUDPSOCKETTABLE::iterator it = m_RUDPSocketTable.find ( SocketID );
    if ( it == m_RUDPSocketTable.end() ) return;
    this->DeleteClient( it->second );
}

void CClientManager::DeleteClient( NLNET::TSockId& SocketID )
{
    WEBSOCKETTABLE::iterator it = m_WEBSocketTable.find ( SocketID );
    if ( it == m_WEBSocketTable.end() ) return;
    this->DeleteClient( it->second );
}

void CClientManager::DeleteClient( CClient* pClient )
{
    if ( NULL == pClient ) return;

    // 删除关联表;
    m_ClientTable.erase( pClient->GetRoleID() );

    // 删除客户端;
    switch ( pClient->GetChannelNet() )
    {
    case RUDP_CHANNEL: 
        m_RUDPSocketTable.erase( pClient->GetRSocketID() );
        FrontendNetWork.CloseClientNet( pClient->GetRSocketID() );
        break;
    case WEB_CHANNEL:
        m_WEBSocketTable.erase( pClient->GetWScoketID() );
        FrontendNetWork.CloseClientNet( pClient->GetWScoketID() );
        break;
    default:
        break;
    }

    SS_SAFE_DELETE( pClient );
}

FES_NAMESPACE_END_DECL