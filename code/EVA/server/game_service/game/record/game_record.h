#ifndef GSE_GAME_RECORD_H_
#define GSE_GAME_RECORD_H_

#include <game_service/game_service/game_service_def.h>
#include <server_share/db/redis/db_redis.h>

GSE_NAMESPACE_BEGIN_DECL

class CGameRecord : public NLMISC::CSingleton< CGameRecord >
{
    
};

#define GameRecord CGameRecord::getInstance()

GSE_NAMESPACE_END_DECL

#endif//GSE_GAME_RECORD_H_