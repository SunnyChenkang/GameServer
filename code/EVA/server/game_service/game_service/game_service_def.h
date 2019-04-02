#ifndef GSE_DEF_H_
#define GSE_DEF_H_

#include <server_share/record/db_record_dot_data.h>
#include <server_share/timer/timer.h>
#include <server_share/common/common.h>
#include <server_share/common/sigslot.h>
#include <server_share/json_table/json_load.h>
#include <server_share/record/db_record_player.h>

#include <game_service/message/message_login.h>
#include <game_service/message/message_room.h>
#include <game_service/message/message_service.h>

GSE_NAMESPACE_BEGIN_DECL

using namespace SS;

// ÏûÏ¢×¢²á; 
static uint32 NetCallBackFuncSize = 0;
static NLNET::TUnifiedCallbackItem CallBackFunItems[512] = { };
#define REGISTER_MAIN_FUNCITEM( SCR_CALLBACK ) \
{ \
    uint32 ArraySize = SS_ARRAYSIZE( SCR_CALLBACK ); \
    for ( sint32 idx = 0; idx < ArraySize; idx++ )  \
{ \
    CallBackFunItems[ NetCallBackFuncSize + idx ] = SCR_CALLBACK[idx]; \
} \
    NetCallBackFuncSize += ArraySize; \
} \

class CPlayer;
typedef std::map< ROLE_ID , CPlayer* > PLAYER_TABLE;

GSE_NAMESPACE_END_DECL

#endif //GSE_DEF_H_