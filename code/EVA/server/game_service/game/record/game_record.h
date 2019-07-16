#ifndef GSE_GAME_RECORD_H_
#define GSE_GAME_RECORD_H_

#include <game_service/game_service/game_service_def.h>
#include <server_share/db/redis/db_redis.h>

GSE_NAMESPACE_BEGIN_DECL

class CGameRecord : public NLMISC::CSingleton< CGameRecord >
{
public:
    //   保存战绩信息;
    void SaveGameRecordBaseInfo( PB_GameRecordBseInfo& , ROLE_ID RoleID );
    //   保存回放节点;
    void SaveGameRecordNode( PB_GameRecordNode& , NLMISC::CSString );
};

#define GameRecord CGameRecord::getInstance()

GSE_NAMESPACE_END_DECL

#endif//GSE_GAME_RECORD_H_