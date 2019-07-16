#include "message_login.h"
#include <schedule_service/login/login_user.h>

SSE_NAMESPACE_BEGIN_DECL

void CallBack_UserLogin( NLNET::CMessage& Message , const std::string& ServiceName, NLNET::TServiceId ServiceId )
{
    LoginUser.CallBackUserLogin( Message );
}

void CallBack_UserLoginSucceed( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    LoginUser.CallBackUserLoginSucceed( Message );
}

SSE_NAMESPACE_END_DECL