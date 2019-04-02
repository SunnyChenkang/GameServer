#ifndef PSE_MESSAGE_SERVICE_H_
#define PSE_MESSAGE_SERVICE_H_

#include <persistent_service/persistent_service/persistent_service_def.h>

PSE_NAMESPACE_BEGIN_DECL

//   游戏服务器断开;
void CallBack_GSEDisconnection( const std::string& , NLNET::TServiceId , void* );
//   网关服务器断开;
void CallBack_FESDisconnection( const std::string& , NLNET::TServiceId , void* );
//   调度服务器断开;
void CallBack_SSEDisconnection( const std::string& , NLNET::TServiceId , void* );

PSE_NAMESPACE_END_DECL

#endif // PSE_MESSAGE_SERVICE_H_;