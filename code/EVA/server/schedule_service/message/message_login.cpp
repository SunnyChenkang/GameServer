#include "message_login.h"
#include <schedule_service/login/login_user.h>

SSE_NAMESPACE_BEGIN_DECL

void CallBack_PlayerLogin( NLNET::CMessage& Message , const std::string& ServiceName, NLNET::TServiceId ServiceId )
{
    LoginUser.CallBackPlayerLogin( Message );
}

void CallBack_PlayerLoginFinish( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    LoginUser.CallBackPlayerLoginFinish( Message );
}

void CallBack_ChangeScenes( NLNET::CMessage& Message , const std::string& , NLNET::TServiceId )
{
    LoginUser.CallBackChangeScenes( Message );
}

SSE_NAMESPACE_END_DECL