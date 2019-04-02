#ifndef GSE_MESSAGE_LOGIN_H_
#define GSE_MESSAGE_LOGIN_H_

#include <game_service/game_service/game_service.h>

GSE_NAMESPACE_BEGIN_DECL

//   同步数据数据;
void CallBack_UserLoad( NLNET::CMessage& , const std::string& , NLNET::TServiceId );
//   用户登录;
void CallBack_UserLogin( NLNET::CMessage&, const std::string&, NLNET::TServiceId );
//   用户离线;
void CallBack_UserOffline( NLNET::CMessage&, const std::string& , NLNET::TServiceId );
//   切换场景;
void CallBack_ChangeScenes( NLNET::CMessage&, const std::string& , NLNET::TServiceId );

//   注册消息;
static NLNET::TUnifiedCallbackItem GSE_LOGIN_CallBackItems[] =
{
    { "MSG_LOADROLE"        , CallBack_UserLoad     },      // 用户加载;
    { "MSG_LOGIN"           , CallBack_UserLogin    },      // 用户登录;
    { "MSG_OFFLINE"         , CallBack_UserOffline  },      // 用户离线;
    { "MSG_CHANGE_SCENES"   , CallBack_ChangeScenes },      // 切换场景;
};

GSE_NAMESPACE_END_DECL

#endif //GSE_MESSAGE_LOGIN_H_