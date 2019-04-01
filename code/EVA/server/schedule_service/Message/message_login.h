#ifndef SSE_MESSAGE_LOGIN_H_
#define SSE_MESSAGE_LOGIN_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

//   用户登录;
void CallBack_UserLogin( NLNET::CMessage&, const std::string&, NLNET::TServiceId );
//   用户登录成功;
void CallBack_UserLoginSucceed( NLNET::CMessage& , const std::string& , NLNET::TServiceId );

// 注册消息;
static NLNET::TUnifiedCallbackItem SSE_LOGIN_CallBackItems[] =
{
    { "MSG_LOGIN" ,                     CallBack_UserLogin          },
    { "MSG_LOGIN_SUCCEED",              CallBack_UserLoginSucceed   },
};

SSE_NAMESPACE_END_DECL

#endif // SSE_MESSAGE_LOGIN_H_;