#include "message_login.h"
#include "../login/login_user.h"

SSE_NAMESPACE_BEGIN_DECL

void CallBack_UserLogin( NLNET::CMessage& Message , const std::string& ServiceName, NLNET::TServiceId ServiceID )
{
    LoginUser.UserLoginCallBack( Message );
}

SSE_NAMESPACE_END_DECL