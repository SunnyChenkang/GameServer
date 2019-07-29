#ifndef GSE_MESSAGE_MATCH_H_
#define GSE_MESSAGE_MATCH_H_

#include <game_service/game_service/game_service.h>

GSE_NAMESPACE_BEGIN_DECL

///  匹配游戏;
void CallBack_MatchUserInfo( NLNET::CMessage&, const std::string&, NLNET::TServiceId );
///  匹配游戏完成;
void CallBack_MatchUserFinish( NLNET::CMessage&, const std::string&, NLNET::TServiceId );

static NLNET::TUnifiedCallbackItem GSE_Match_CallBackItem[] =
{
    { "MSG_MATCH_USER" , CallBack_MatchUserInfo },
    { "MSG_MATCH_USER_FINISH" , CallBack_MatchUserFinish },
};

GSE_NAMESPACE_END_DECL

#endif//GSE_MESSAGE_MATCH_H_