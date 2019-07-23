#include "message_login.h"
#include "persistent_service/login/login_user.h"

PSE_NAMESPACE_BEGIN_DECL

void CallBack_PlayerLogin( NLNET::CMessage& Message, const std::string& ServiceName, NLNET::TServiceId ServiceID )
{
    PB_UserLogin UserLogin;
    Message.serial( &UserLogin );
    LoginUser.UserLoginCallBack( UserLogin );
}

PSE_NAMESPACE_END_DECL