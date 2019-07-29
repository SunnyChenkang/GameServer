#ifndef SSE_MESSAGE_GAME_H_
#define SSE_MESSAGE_GAME_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

///  ◊¢≤·”Œœ∑–≈œ¢;
void CallBack_RegisterGameInfo( NLNET::CMessage&, const std::string&, NLNET::TServiceId );

static NLNET::TUnifiedCallbackItem SSE_GAME_CallBackItem[] =
{
    { "MSG_GAME_REGISTER",              CallBack_RegisterGameInfo   },
};

SSE_NAMESPACE_END_DECL

#endif//SSE_MESSAGE_GAME_H_