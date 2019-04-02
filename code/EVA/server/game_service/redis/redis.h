#ifndef GSE_GAMEREDIS_H_
#define GSE_GAMEREDIS_H_

#include <game_service/game_service/game_service_def.h>
#include <server_share/redis/db_redis.h>

GSE_NAMESPACE_BEGIN_DECL

class CRedis : public NLMISC::CSingleton< CRedis >
{
public:
    CRedis( void ) { };
   ~CRedis( void ) { };

    SS_PROPERTY( CDBRedis , GameRedis , public );
};

#define Redis CRedis::getInstance()
#define GameRedis Redis.m_GameRedis

GSE_NAMESPACE_END_DECL

#endif//GSE_GAMEREDIS_H_