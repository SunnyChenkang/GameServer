#ifndef SSE_DEF_H_
#define SSE_DEF_H_

#include <server_share/timer/timer.h>
#include <server_share/common/common.h>
#include <server_share/json_table/json_load.h>

#include <schedule_service/message/message_login.h>
#include <schedule_service/message/message_room.h>
#include <schedule_service/message/message_service.h>

SSE_NAMESPACE_BEGIN_DECL

using namespace SS;

// Íæ¼ÒÁÐ±í;
class CPlayer;
typedef std::map< ROLE_ID , CPlayer* > PLAYER_TABLE;

SSE_NAMESPACE_END_DECL

#endif //SSE_DEF_H_
