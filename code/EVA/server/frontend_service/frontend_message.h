#ifndef FRONTEND_SERVICE_MESSAGE_H_
#define FRONTEND_SERVICE_MESSAGE_H_

#include "frontend_def.h"

FES_NAMESPACE_BEGIN_DECL

// RUDP;
void CallBack_RUDPLogin( NLNET::CMessage& , SOCKET_ID );
static TRUDPCallbackItem RUDPCallBackItems[] =
{
    { "MSG_LOGIN" ,  CallBack_RUDPLogin },
};


// WEB;
void CallBack_WebLogin( NLNET::CMessage& , NLNET::TSockId , NLNET::CCallbackNetBase& );
static TWEBCallbackItem WEBCallBackItems[] =
{
    { "LOGIN" , CallBack_WebLogin },
};


// LOCAL
void CallBack_S2C( NLNET::CMessage& , const std::string&, NLNET::TServiceId );
static NLNET::TUnifiedCallbackItem LocalCallBackItems[] =
{
    { "S2C" , CallBack_S2C } ,
};

class CClient;

// EGS DISCONNECT CALLBACK;
void CallBack_EGSDisconnection( const std::string& , NLNET::TServiceId , void* );
// PLS DISCONNECT CALLBACK;
void CallBack_PLSDisconnection( const std::string& , NLNET::TServiceId , void* );
// PDS DISCONNECT CALLBACK;
void CallBack_PDSDisconnection( const std::string& , NLNET::TServiceId , void* );

// AUTH ACCOUNT;
bool CallBack_AuthAccount( NLNET::CMessage& , CClient* );

FES_NAMESPACE_END_DECL

#endif //FRONTEND_SERVICE_MESSAGE_H_