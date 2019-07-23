#ifndef FRONTEND_SERVICE_MESSAGE_H_
#define FRONTEND_SERVICE_MESSAGE_H_

#include "frontend_def.h"

FES_NAMESPACE_BEGIN_DECL

class CClient;

// RUDP;
void CallBack_RUDPLogin( NLNET::CMessage& , SOCKET_ID );
static TRUDPCallbackItem RUDPCallBackItems[] =
{
    { "MSG_LOGIN"           ,  CallBack_RUDPLogin },
};


// WEB;
void CallBack_WebLogin( NLNET::CMessage& , NLNET::TSockId );
static TWEBCallbackItem WEBCallBackItems[] =
{
    { "MSG_LOGIN" , CallBack_WebLogin },
};


// LOCAL
void CallBack_S2C( NLNET::CMessage& , const std::string&, NLNET::TServiceId );
void CallBack_LoginSucceed( NLNET::CMessage& , const std::string&, NLNET::TServiceId );
void CallBack_ClientDelete( NLNET::CMessage& , const std::string&, NLNET::TServiceId );

static NLNET::TUnifiedCallbackItem LocalCallBackItems[] =
{
    { "S2C"                 , CallBack_S2C } ,
    { "MSG_LOGIN_SUCCEED"   , CallBack_LoginSucceed },
    { "MSG_CLIENT_DELETE"   , CallBack_ClientDelete },
};

// SSE DISCONNECT CALLBACK;
void CallBack_SSEDisconnection( const std::string& , NLNET::TServiceId , void* );
// GSE DISCONNECT CALLBACK;
void CallBack_GSEDisconnection( const std::string& , NLNET::TServiceId , void* );
// PSE DISCONNECT CALLBACK;
void CallBack_PSEDisconnection( const std::string& , NLNET::TServiceId , void* );

FES_NAMESPACE_END_DECL

#endif //FRONTEND_SERVICE_MESSAGE_H_