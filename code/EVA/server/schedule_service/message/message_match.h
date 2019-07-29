#ifndef SSE_MESSAGE_MATCH_H_
#define SSE_MESSAGE_MATCH_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

///  匹配游戏;
void CallBack_MatchUserInfo( NLNET::CMessage&, const std::string&, NLNET::TServiceId );
///  匹配游戏完成;
void CallBack_MatchUserFinish( NLNET::CMessage&, const std::string&, NLNET::TServiceId );

static NLNET::TUnifiedCallbackItem SSE_Match_CallBackItem[] =
{
    { "MSG_MATCH_USER" , CallBack_MatchUserInfo },
    { "MSG_MATCH_USER_FINISH" , CallBack_MatchUserFinish },
};

SSE_NAMESPACE_END_DECL

#endif//SSE_MESSAGE_MATCH_H_