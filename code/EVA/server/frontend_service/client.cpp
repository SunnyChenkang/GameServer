#include "client.h"
#include "frontend_network.h"

FES_NAMESPACE_BEGIN_DECL

CClient::CClient( void ) : m_RSocketID( 0 )
                         , m_WScoketID( NLNET::InvalidSockId )
                         , m_RoleID( 0 )
                         , m_ConnectionTime( 0 )
                         , m_ChannelNet( RUDP_CHANNEL )
                         , m_ClientState( CLIENT_CONNECTION_ABNORMAL )
                         , m_Host("")
                         , m_GameServiceId( NLNET::TServiceId::InvalidId )
{
    
}

void CClient::SendToClient( NLNET::CMessage& message )
{
    switch ( m_ChannelNet )
    {
    case WEB_CHANNEL:
        FrontendNetWork.GetWebNetBase()->send( message , GetWScoketID() );
        break;
    case RUDP_CHANNEL:
        SEND_OBJ()->push( message.buffer() , message.length() , GetRSocketID() );
        break;
    default:
        nlinfo( " not find channel net type" );
        break;
    }
}

FES_NAMESPACE_END_DECL