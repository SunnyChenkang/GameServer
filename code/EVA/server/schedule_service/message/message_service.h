#ifndef SSE_MESSAGE_SERVICE_H_
#define SSE_MESSAGE_SERVICE_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

//   ��Ϸ�������Ͽ�;
void CallBack_GSEDisconnection( const std::string& , NLNET::TServiceId , void* );
//   ���ط������Ͽ�;
void CallBack_FESDisconnection( const std::string& , NLNET::TServiceId , void* );
//   �洢�������Ͽ�;
void CallBack_PSEDisconnection( const std::string& , NLNET::TServiceId , void* );

SSE_NAMESPACE_END_DECL

#endif //SSE_MESSAGE_SERVICE_H_