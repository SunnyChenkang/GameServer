#include "game_record.h"
#include <game_service/redis/redis.h>

GSE_NAMESPACE_BEGIN_DECL

void CGameRecord::SaveGameRecordBaseInfo( PB_GameRecordBseInfo& PBGameRecordBase , ROLE_ID RoleID )
{
    NLMISC::CSString RedisKey =  NLMISC::toString( RoleID );
    NLMISC::CMemStream Memstream;
    Memstream.serial( &PBGameRecordBase );
    sint32 ListCount = GameRedis.LPushRedisList( RedisKey.c_str() , RedisKey.length() , ( const char* )Memstream.buffer() , Memstream.getPos() );

    // 保留10条数据;
    if ( ListCount < 15 ) return;
    // 保留10条战绩数据为了避免操作频繁15条之后批量删除无效数据;
    GameRedis.DelRedisListRange( RedisKey.c_str() , RedisKey.length() , ListCount-10 , -1 );
}

void CGameRecord::SaveGameRecordNode( PB_GameRecordNode& PBGameRecordNode , NLMISC::CSString UUID )
{
    NLMISC::CMemStream Memstream;
    Memstream.serial( &PBGameRecordNode );
    GameRedis.SetRedisKey( UUID.c_str() , UUID.length() , (const char*)Memstream.buffer() , Memstream.getPos() , 60*60*24*30 );
}

GSE_NAMESPACE_END_DECL
