#ifndef SSE_MESSAGE_SERVICE_H_
#define SSE_MESSAGE_SERVICE_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

///   游戏服务器连接;
void  CallBack_GSEConnection( const std::string& , NLNET::TServiceId , void* );
///   网关服务器连接;
void  CallBack_FESConnection( const std::string& , NLNET::TServiceId , void* );
///   存储服务器连接;
void  CallBack_PSEConnection( const std::string& , NLNET::TServiceId , void* );

///   游戏服务器断开;
void CallBack_GSEDisconnection( const std::string& , NLNET::TServiceId , void* );
///   网关服务器断开;
void CallBack_FESDisconnection( const std::string& , NLNET::TServiceId , void* );
///   存储服务器断开;
void CallBack_PSEDisconnection( const std::string& , NLNET::TServiceId , void* );

SSE_NAMESPACE_END_DECL

#endif //SSE_MESSAGE_SERVICE_H_