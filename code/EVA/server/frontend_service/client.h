#ifndef FRONTEND_SERVICE_CLIENT_H_
#define FRONTEND_SERVICE_CLIENT_H_

#include "frontend_def.h"

FES_NAMESPACE_BEGIN_DECL

class CClient
{
public:
    CClient( void );
   ~CClient( void ){ };

    // 发送消息到客户端;
    void SendToClient( NLNET::CMessage& );

    SS_PROPERTY( SOCKET_ID         , RSocketID      , private );
    SS_PROPERTY( NLNET::TSockId    , WScoketID      , private );
    SS_PROPERTY( TChannelNet       , ChannelNet     , private );
    SS_PROPERTY( TClientState      , ClientState    , private );
    SS_PROPERTY( uint32            , ConnectionTime , private );
    SS_PROPERTY( ROLE_ID           , RoleID         , private );
    SS_PROPERTY( NLMISC::CSString  , Host           , private );
    SS_PROPERTY( NLNET::TServiceId , GameServiceId  , private );
};

FES_NAMESPACE_END_DECL

#endif // FRONTEND_SERVICE_CLIENT_H_