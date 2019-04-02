#ifndef GSE_MESSAGE_SERVICE_H_
#define GSE_MESSAGE_SERVICE_H_

#include <game_service/game_service/game_service.h>

GSE_NAMESPACE_BEGIN_DECL

//   游戏服务器断开;
void CallBack_GSEDisconnection( const std::string& , NLNET::TServiceId , void* );
//   网关服务器断开;
void CallBack_FESDisconnection( const std::string& , NLNET::TServiceId , void* );
//   存储服务器断开;
void CallBack_PSEDisconnection( const std::string& , NLNET::TServiceId , void* );
//   调度服务器断开;
void CallBack_SSEDisconnection( const std::string& , NLNET::TServiceId , void* );

GSE_NAMESPACE_END_DECL

#endif//GSE_MESSAGE_SERVICE_H_