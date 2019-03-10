#ifndef SSE_DEF_H_
#define SSE_DEF_H_

#include <server_share/timer/timer.h>
#include <server_share/common/common.h>
#include <server_share/json_table/json_load.h>
#include "message/message_login.h"

SSE_NAMESPACE_BEGIN_DECL

// Íæ¼ÒÁÐ±í;
class CPlayer;
typedef std::map< ROLE_ID , CPlayer* > PLAYER_TABLE;

SSE_NAMESPACE_END_DECL

#endif SSE_DEF_H_
