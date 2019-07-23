#ifndef FRONTEND_SERVICE_CLIENT_H_
#define FRONTEND_SERVICE_CLIENT_H_

#include "frontend_def.h"

FES_NAMESPACE_BEGIN_DECL

class CClient
{
public:
    CClient( void );
   ~CClient( void ){ };

    SS_PROPERTY( SOCKET_ID      , UDPSocketID    , private );
    SS_PROPERTY( TSockId        , WebSocketID    , private );
    SS_PROPERTY( TChannelNet    , ChannelNet     , private );
    SS_PROPERTY( TClientState   , ClientState    , private );
    SS_PROPERTY( uint32         , ConnectionTime , private );
    SS_PROPERTY( ROLE_ID        , RoleID         , private );
    SS_PROPERTY( CSString       , Host           , private );
    SS_PROPERTY( TServiceId     , GameServiceId  , private );

    ///  发送消息到客户端;
    void SendToClient( NLNET::CMessage& );
};

typedef shared_ptr< CClient > CClientPtr;

FES_NAMESPACE_END_DECL

#endif // FRONTEND_SERVICE_CLIENT_H_