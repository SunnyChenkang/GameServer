#ifndef LSE_MESSAGE_SERVICE_H_
#define LSE_MESSAGE_SERVICE_H_

#include <logger_service/logger_service/logger_service_def.h>

LSE_NAMESPACE_BEGIN_DECL

//   游戏服务器断开;
void CallBack_GSEDisconnection( const std::string& , NLNET::TServiceId , void* );
//   网关服务器断开;
void CallBack_FESDisconnection( const std::string& , NLNET::TServiceId , void* );
//   调度服务器断开;
void CallBack_SSEDisconnection( const std::string& , NLNET::TServiceId , void* );
//   数据服务器断开;
void CallBack_PSEDisconnection( const std::string& , NLNET::TServiceId , void* );

LSE_NAMESPACE_END_DECL

#endif//LSE_MESSAGE_SERVICE_H_