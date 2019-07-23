#ifndef SSE_MESSAGE_LOGIN_H_
#define SSE_MESSAGE_LOGIN_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

///  Íæ¼ÒµÇÂ¼;
void CallBack_PlayerLogin( NLNET::CMessage&, const std::string&, NLNET::TServiceId );
///  Íæ¼ÒµÇÂ¼Íê³É;
void CallBack_PlayerLoginFinish( NLNET::CMessage& , const std::string& , NLNET::TServiceId );
///  Íæ¼ÒÇÐ»»³¡¾°;
void CallBack_ChangeScenes( NLNET::CMessage& , const std::string& , NLNET::TServiceId );

static NLNET::TUnifiedCallbackItem SSE_LOGIN_CallBackItems[] =
{
    { "MSG_LOGIN" ,                     CallBack_PlayerLogin          },
    { "MSG_LOGIN_FINISH",               CallBack_PlayerLoginFinish    },
    { "MSG_CHANGE_SCENES",              CallBack_ChangeScenes         },
};

SSE_NAMESPACE_END_DECL

#endif // SSE_MESSAGE_LOGIN_H_;