#include "client_manager.h"
#include "frontend_network.h"
#include "client_timer.h"

extern NLMISC::CVariable< uint32 > VAR_FES_WAIT_CONNECTION_TIMEROUT;
extern NLMISC::CVariable< uint32 > VAR_FES_MAX_CLIENTCOUNT;
extern NLMISC::CVariable< uint32 > VAR_FES_CHECK_WAIT_CONNECTION_TIME;
FES_NAMESPACE_BEGIN_DECL

CClientManager::CClientManager( void )
{
    m_RoleClientTable.clear();
    m_UDPClientTable.clear();
    m_WEBClientTable.clear();
}

CClientPtr CClientManager::AllocUDPClient( ROLE_ID RoleID , SOCKET_ID SocketID )
{
    /// 查找旧数据删掉;
    this->DeleteClientUDP( RoleID );

    /// 创建新客户端实例;
    CClientPtr ClientPtr = std::make_shared< CClient >();
    if ( nullptr == ClientPtr ) { return nullptr; }
    m_RoleClientTable[ RoleID ] = ClientPtr;
    m_UDPClientTable [SocketID] = RoleID;

    /// 设置客户端属性;
    ClientPtr->SetUDPSocketID( SocketID );
    ClientPtr->SetChannelNet( RUDP_CHANNEL );
    ClientPtr->SetConnectionTime( NLMISC::CTime::getSecondsSince1970() );
    return ClientPtr;
}

CClientPtr CClientManager::AllocWebClient( ROLE_ID RoleID , TSockId SocketID )
{
    /// 查找旧数据删掉;
    this->DeleteClientWEB( SocketID );

    /// 创建新客户端实例;
    CClientPtr ClientPtr = std::make_shared< CClient >();
    if ( nullptr == ClientPtr ) { return nullptr; }
    m_RoleClientTable[ RoleID ] = ClientPtr;
    m_WEBClientTable [SocketID] = RoleID;

    /// 设置客户端属性;
    ClientPtr->SetWebSocketID( SocketID );
    ClientPtr->SetChannelNet( WEB_CHANNEL );
    ClientPtr->SetConnectionTime( NLMISC::CTime::getSecondsSince1970() );
    return ClientPtr;
}

CClientPtr CClientManager::FindClientRole( ROLE_ID RoleID )
{
    auto It = m_RoleClientTable.find( RoleID );
    if ( It == m_RoleClientTable.end() ) {
        return nullptr;
    }
    return It->second;
}

CClientPtr CClientManager::FindClientUDP( SOCKET_ID SocketID )
{
    auto It = m_UDPClientTable.find( SocketID );
    if ( It == m_UDPClientTable.end() ) {
        return nullptr;
    }
    return FindClientRole( It->second );
}

CClientPtr CClientManager::FindClientWEB( TSockId SocketID )
{
    auto It = m_WEBClientTable.find( SocketID );
    if ( It == m_WEBClientTable.end() ) {
        return nullptr;
    }
    return FindClientRole( It->second );
}

void CClientManager::DeleteClientRole( ROLE_ID RoleID )
{
    auto It = m_RoleClientTable.find( RoleID );
    if ( It == m_RoleClientTable.end() ) {
        return;
    }

    switch (It->second->GetChannelNet() )
    {
    case RUDP_CHANNEL:
        FrontendNetWork.CloseClientNet( It->second->GetUDPSocketID() );
        break;
    case WEB_CHANNEL:
        FrontendNetWork.CloseClientNet( It->second->GetWebSocketID() );
        break;
    default:
        break;
    }
    m_RoleClientTable.erase( It );
}

void CClientManager::DeleteClientUDP( SOCKET_ID SocketID )
{
    auto It = m_UDPClientTable.find( SocketID );
    if ( It == m_UDPClientTable.end() ) {
        return;
    }
    DeleteClientRole( It->second );
    m_UDPClientTable.erase( It );
}

void CClientManager::DeleteClientWEB( TSockId SocketID )
{
    auto It = m_WEBClientTable.find( SocketID );
    if ( It == m_WEBClientTable.end() ) {
        return;
    }
    DeleteClientRole( It->second );
    m_WEBClientTable.erase( It );
}

void CClientManager::DeleteClient( CClientPtr ClientPtr )
{
    if ( nullptr == ClientPtr ) {
        return;
    }

    switch ( ClientPtr->GetChannelNet() )
    {
    case WEB_CHANNEL:
        DeleteClientWEB( ClientPtr->GetWebSocketID() );
        break;
    case RUDP_CHANNEL:
        DeleteClientUDP( ClientPtr->GetUDPSocketID() );
        break;
    default:
        break;
    }
}

FES_NAMESPACE_END_DECL