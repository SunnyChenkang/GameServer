#include "db_redis.h"

SS_NAMESPACE_BEGIN_DECL

#define REDIS_NORMAL_JUDGE( redis ) \
if ( NULL == redis ) \
{ \
    return NetError; \
} \
if ( REDIS_REPLY_ERROR == redis->type ) \
{ \
    freeReplyObject( redis ); \
    return NormalError; \
} \

#ifdef __cplusplus
extern "C" {
#endif
    int __redisAppendCommand(redisContext *c, const char *cmd, size_t len);
#ifdef __cplusplus
}
#endif

static sint32 IntLen( sint32 Idx )
{
    sint32 len = 0;
    if ( Idx < 0 ) {
    len++;
    Idx = -1;
    }
    do 
    {
        len++;
        Idx /= 10;
    } while ( Idx );
    return len;
}

static size_t Bulklen( size_t len )
{
    return 1+IntLen(len) + 2 + len + 2;
}

CDBRedis::CDBRedis( void ) : m_RedisContext( NULL )
                           , m_Host( "" )
                           , m_Port( 0 )
                           , m_TimeOut( 0 )
{
    
}

bool CDBRedis::Connect( const char* host , sint32 port , uint32 timeout , const char* password )
{
    Close();

    m_Host = host;
    m_Port = port;
    m_TimeOut = timeout;

    struct timeval tval;
    tval.tv_sec = timeout / 1000;
    tval.tv_usec= timeout % 1000 * 1000;

    m_RedisContext = redisConnectWithTimeout( host , port , tval );

    if ( NULL == m_RedisContext )
    {
        nlinfo( " redis connection host fail: %s , port: %d" , m_Host.c_str() , m_Port );
        return false;
    }
    if ( NULL != m_RedisContext && m_RedisContext->err )
    {
        nlinfo( " redis connection host fail: %s , port: %d error: %s" , m_Host.c_str() , m_Port , m_RedisContext->errstr );
        return false;
    }

    if ( NULL != password )
    {
        redisReply* pRedis = NULL;
        pRedis = ( redisReply* )Command( "AUTH %s" , password );
        sint32 RedisType = pRedis->type;
        freeReplyObject( pRedis );
        if ( RedisType == REDIS_REPLY_ERROR )
        {
            return false;
        }
    }

    return true;
}

void CDBRedis::Close( void )
{
    if ( NULL == m_RedisContext ) { return; }

    redisFree( m_RedisContext );
    m_RedisContext = NULL;
}

void* CDBRedis::Command( const char* format , ... )
{
    va_list Args;
    void*   pRedis = NULL;

    if ( NULL != m_RedisContext )
    {
        va_start( Args , format );
        pRedis = redisvCommand( m_RedisContext , format , Args );
        va_end( Args );
    }

    if ( NULL != pRedis ) { return pRedis; }

    // 重新连接;

    if ( NULL != m_RedisContext )
    {
        va_start( Args , format );
        pRedis = redisvCommand( m_RedisContext , format , Args );
        va_end( Args );
    }

    return pRedis;
}

void* CDBRedis::CommandArgv(const std::vector< NLMISC::CSString >& RedisOper , const std::vector< NLMISC::CSString >& RedisParam )
{
    char*  pCmd  = NULL;
    sint32 Len = 0;
    void*  pRedis = NULL;
    sint32 Pos;
    sint32 Totlen = 0;

    // 格式化命令;
    Totlen = 1 + IntLen( RedisOper.size() + RedisParam.size() ) + 2;
    for ( uint32 idx = 0; idx < RedisOper.size(); idx++ )
    {
        Totlen += Bulklen( RedisOper[idx].length() );
    }
    for ( uint32 idx = 0; idx < RedisParam.size(); idx++ )
    {
        Totlen += Bulklen( RedisParam[idx].length() );
    }

    pCmd = ( char* )malloc( Totlen + 1 );
    if ( NULL == pCmd ) return NULL;

    Pos = NLMISC::smprintf( pCmd , Totlen+ 1 , "*%zu\r\n" , RedisOper.size() + RedisParam.size() );

    // push cmd;
    for ( uint32 idx = 0; idx < RedisOper.size(); idx++ )
    {
        Pos += NLMISC::smprintf( pCmd + Pos , Totlen+1 , "*%zu\r\n" , RedisOper[idx].length() );
        memcpy( pCmd + Pos , RedisOper[idx].c_str() , RedisOper[idx].length() );
        Pos += RedisOper[idx].length();
        pCmd[Pos++] = '\r';
        pCmd[Pos++] = '\n';
    }

    // push param;
    for ( uint32 idx = 0; idx < RedisParam.size(); idx++ )
    {
        Pos += NLMISC::smprintf( pCmd + Pos , Totlen + 1 , "*%zu\r\n" , RedisParam[idx].length() );
        memcpy( pCmd + Pos , RedisParam[idx].c_str() , RedisParam[idx].length() );
        Pos += RedisParam[idx].length();
        pCmd[Pos++] = '\r';
        pCmd[Pos++] = '\n';
    }

    pCmd[ Pos ] = '\0';
    Len = Totlen;

    // 执行命令;
    pRedis = ExecCommand( pCmd , Len );
    if ( NULL == pRedis )
    {
        if ( Connect( m_Host.c_str() , m_Port , m_TimeOut ) )
        {
            pRedis = ExecCommand( pCmd , Len );
        }
    }

    free( pCmd );
    return pRedis;
}

void* SS::CDBRedis::ExecCommand( const char* pCmd , sint32 CmdLen )
{
    void* pRedis = NULL;
    if ( NULL == m_RedisContext ) return NULL;

    // 执行命令;
    if ( __redisAppendCommand( m_RedisContext , pCmd , CmdLen ) )
    {
        return NULL;
    }

    // 查看执行结果;
    if ( m_RedisContext->flags & REDIS_BLOCK )
    {
        if ( redisGetReply( m_RedisContext , &pRedis ) != REDIS_OK ) { return NULL; }
    }

    return pRedis;
}

sint32 CDBRedis::SetRedisKey( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisValue , sint32 RedisValueLen , uint32 RedisLifeTime )
{
    redisReply* pRedis = NULL;
    if ( 0 == RedisLifeTime )
    {
        pRedis = ( redisReply* )Command( "SET %b %b" , pRedisKey , ( size_t )RedisKeyLen , pRedisValue , (size_t )RedisValueLen );
    }
    else
    {
        pRedis = ( redisReply* )Command( "SET %b %b EX %u" , pRedisKey , ( size_t )RedisKeyLen , pRedisValue , ( size_t )RedisValueLen , RedisLifeTime );
    }

    REDIS_NORMAL_JUDGE( pRedis );
    freeReplyObject( pRedis );
    return 0;
}

sint32 CDBRedis::SetRedisKey( NLMISC::CSString RedisKey , NLMISC::CSString RedisValue , uint32 RedisLifeTime /*= 0 */ )
{
    return this->SetRedisKey( RedisKey.c_str() , RedisKey.length() , RedisValue.c_str() , RedisValue.length() , RedisLifeTime );
}

sint32 CDBRedis::SetRedisKey( NLMISC::CSString RedisKey , uint32 RedisValue , uint32 RedisLifeTime /*= 0 */ )
{
    return this->SetRedisKey( RedisKey , NLMISC::CSString( RedisValue ) , RedisLifeTime );
}

sint32 CDBRedis::SetRedisKey(NLMISC::CSString RedisKey , uint64 RedisValue , uint32 RedisLifeTime /*= 0 */)
{
    return this->SetRedisKey( RedisKey , NLMISC::toString( RedisValue ) , RedisLifeTime );
}

sint32 CDBRedis::SetRedisAppend( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisValue , sint32 pRedisValueLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "APPEND %b %b" , pRedisKey , ( size_t )RedisKeyLen , pRedisValue , ( size_t )pRedisValueLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = ( sint32 )pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::SetRedisKeyLifeTime( const char* pRedisKey , sint32 RedisKeyLen , uint32 RedisLifeTime )
{
    redisReply* pRedis = NULL;
    if ( 0 == RedisLifeTime )
    {
        pRedis = ( redisReply* )Command( "PERSIST %b" , pRedisKey , ( size_t )RedisKeyLen );
    }
    else
    {
        pRedis = ( redisReply* )Command( "EXPIER %b %u" , pRedisKey , ( size_t )RedisKeyLen , RedisLifeTime );
    }

    REDIS_NORMAL_JUDGE( pRedis );
    freeReplyObject( pRedis );
    return 0;
}

sint32 CDBRedis::GetRedisKey( const char* pRedisKey , sint32 RedisKeyLen , char* pRedisValue , sint32 RedisValueLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "GET %b" , pRedisKey , ( size_t )RedisKeyLen );
    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->len;
    if ( len > RedisValueLen )
    {
        len = SpaceNotEnough;
    }
    else
    {
        memcpy( pRedisValue , pRedis->str , len );
    }
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::GetRedisKey( NLMISC::CSString RedisKey , char* pRedisValue , sint32 RedisValueLen )
{
    return this->GetRedisKey( RedisKey.c_str() , RedisKey.length() , pRedisValue , RedisValueLen );
}

sint32 CDBRedis::GetRedisKey( NLMISC::CSString RedisKey , NLMISC::CSString& RedisValue )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "GET %b" , RedisKey.c_str() , ( size_t )RedisKey.length() );
    REDIS_NORMAL_JUDGE( pRedis );
    if( pRedis->len <= 0 )
    {
        return pRedis->len;
    }
    RedisValue.append( pRedis->str , pRedis->len );
    freeReplyObject( pRedis );
    return pRedis->len;
}

sint32 CDBRedis::GetRedisLen( const char* pRedisKey , sint32 RedisKeyLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "STRLEN %b" , pRedisKey , ( size_t )RedisKeyLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = ( sint32 )pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::GetRedisKeyLifeTime( const char* pRedisKey , sint32 RedisKeyLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "TTL %b" , pRedisKey , ( size_t )RedisKeyLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = (sint32)pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::DeleteRedisKey( const char* pRedisKey , sint32 RedisKeyLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "DEL %b" , pRedisKey , ( size_t )RedisKeyLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = ( sint32 )pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::HasRedisKey(const char* pRedisKey , sint32 RedisKeyLen)
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "EXISTS %b" , pRedisKey , ( size_t )RedisKeyLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = (sint32)pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::SetRedisMultiKey(const std::vector<NLMISC::CSString>& RedisKeyValue)
{
    redisReply* pRedis = NULL;
    std::vector< NLMISC::CSString > VstrOper;
    VstrOper.push_back( NLMISC::CSString("MSET") );
    pRedis = ( redisReply* )CommandArgv( VstrOper , RedisKeyValue );
    REDIS_NORMAL_JUDGE( pRedis );
    freeReplyObject( pRedis );
    return 0;
}

sint32 CDBRedis::GetRedisMultiKey(const std::vector<NLMISC::CSString>& RedisKey , std::vector<NLMISC::CSString>& RedisValue)
{
    redisReply* pRedis = NULL;
    std::vector<NLMISC::CSString> VstrOper;
    VstrOper.push_back( NLMISC::CSString("MGET") );
    pRedis = ( redisReply* )CommandArgv( VstrOper , RedisValue );

    REDIS_NORMAL_JUDGE( pRedis );
    RedisValue.clear();
    for ( uint32 idx = 0; idx < pRedis->elements; idx++ )
    {
        RedisValue.push_back( NLMISC::CSString(pRedis->element[idx]->str ) );
    }

    freeReplyObject( pRedis );
    return 0;
}

sint32 CDBRedis::DelRedisMultiKey(const std::vector<NLMISC::CSString>& RedisKey)
{
    redisReply* pRedis = NULL;
    std::vector< NLMISC::CSString > VstrOper;
    VstrOper.push_back( NLMISC::CSString("DEL") );
    pRedis = ( redisReply* )CommandArgv( VstrOper , RedisKey );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::SetRedisHashField( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisField , sint32 RedisFieldLen , const char* pRedisValue , sint32 RedisValueLen)
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command("HSET %b %b %b" , pRedisKey , (size_t)RedisKeyLen , pRedisField , (size_t)RedisFieldLen , pRedisValue , (size_t)RedisValueLen );

    REDIS_NORMAL_JUDGE( pRedis );
    freeReplyObject( pRedis );
    return 0;
}

sint32 CDBRedis::GetRedisHashField( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisField , sint32 RedisFieldLen , char* pRedisValue , sint32 RedisValueLen)
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "HGET %b %b" , pRedisKey , (size_t)RedisKeyLen , pRedisField , (size_t)RedisFieldLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->len;
    if ( len > RedisValueLen )
    {
        len = SpaceNotEnough;
    }
    else
    {
        memcpy( pRedisValue , pRedis->str , len );
    }
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::DelRedisHashField( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisField , sint32 RedisFieldLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command("HDEL %b %b" , pRedisKey , (size_t)RedisKeyLen ,pRedisField , (size_t)RedisFieldLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->integer;
    freeReplyObject( pRedis );

    return len;
}

sint32 CDBRedis::HasRedisHashKey( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisField , sint32 RedisFieldLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "HEXISTS %b %b" , pRedisKey , (size_t)RedisKeyLen , pRedisField , (size_t)RedisFieldLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->integer;
    freeReplyObject( pRedis );

    return len;
}

sint32 CDBRedis::GetRedisHaskAll( const char* pRedisKey , sint32 RedisKeyLen , std::vector< NLMISC::CSString >& VstrFieldValue )
{
    redisReply* pRedis =  NULL;
    pRedis = ( redisReply* )Command("HGETALL %b" , pRedisKey , (size_t)RedisKeyLen );

    REDIS_NORMAL_JUDGE( pRedis );
    VstrFieldValue.clear();
    for ( uint32 idx = 0; idx < pRedis->elements; idx++ )
    {
        VstrFieldValue.push_back( NLMISC::CSString( pRedis->element[idx]->str ) );
    }
    freeReplyObject( pRedis );
    return 0;
}

sint32 CDBRedis::GetRedisHashFieldCount( const char* pRedisKey , sint32 RedisKeyLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "HLEN %b" , pRedisKey , (size_t)RedisKeyLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::SetMultiHashField( const char* pRedisKey , sint32 RedisKeyLen , const std::vector< NLMISC::CSString >& VstrFieldValue )
{
    redisReply* pRedis = NULL;
    std::vector< NLMISC::CSString > VstrOper;
    VstrOper.push_back( NLMISC::CSString("HMSET") );
    VstrOper.push_back( NLMISC::CSString( pRedisKey ) );
    pRedis = ( redisReply* )CommandArgv( VstrOper , VstrFieldValue );

    REDIS_NORMAL_JUDGE( pRedis );
    freeReplyObject( pRedis );
    return 0;
}

sint32 CDBRedis::GetMultiHashField( const char* pRedisKey , sint32 RedisKeyLen , const std::vector< NLMISC::CSString >& RedisField , std::vector< NLMISC::CSString >& RedisValue )
{
    redisReply* pRedis = NULL;
    std::vector< NLMISC::CSString > VstrOper;
    VstrOper.push_back( NLMISC::CSString("HMGET") );
    VstrOper.push_back( NLMISC::CSString( pRedisKey ) );
    pRedis = ( redisReply* )CommandArgv( VstrOper , RedisField );

    REDIS_NORMAL_JUDGE( pRedis );
    // 获取结果;
    RedisValue.clear();
    for ( sint32 idx = 0; idx < pRedis->elements; idx++ )
    {
        VstrOper.push_back( NLMISC::CSString( pRedis->element[idx]->str ) );
    }
    freeReplyObject( pRedis );
    return 0;
}

sint32 CDBRedis::DelMultiHashField( const char* pRedisKey , sint32 RedisKeyLen , const std::vector< NLMISC::CSString >& VstrFieldValue )
{
    redisReply* pRedis = NULL;
    std::vector< NLMISC::CSString > VstrOper;
    VstrOper.push_back( "HDEL" );
    VstrOper.push_back( NLMISC::CSString( pRedisKey ) );
    pRedis = ( redisReply* )CommandArgv( VstrOper , VstrFieldValue );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::LPushRedisList( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisValue , sint32 RedisValueLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command("LPUSH %b %b" , pRedisKey , (size_t)RedisKeyLen , pRedisValue , (size_t)RedisValueLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::LPoPRedisList( const char* pRedisKey , sint32 RedisKeyLen , char* pRedisValue , sint32 RedisValueLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command("LPOP %b" , pRedisKey , (size_t)RedisKeyLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = (sint32)pRedis->len;
    if ( len > RedisValueLen )
    {
        len = SpaceNotEnough;
    }
    else
    {
        memcpy( pRedisValue , pRedis->str , len );
    }
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::LPoPRedisList( const char* pRedisKey , sint32 RedisKeyLen , NLMISC::CSString& RedisValue )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "LPOP %b" , pRedisKey , (size_t)RedisKeyLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->len;
    RedisValue.append( pRedis->str , pRedis->len );
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::RPushRedisList( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisValue , sint32 RedisValueLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "RPUSH %b %b" , pRedisKey , (size_t)RedisKeyLen , pRedisValue , (size_t)RedisValueLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::RPoPRedisList( const char* pRedisKey , sint32 RedisKeyLen , char* pRedisValue , sint32 RedisValueLen )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "RPOP %b" , pRedisKey , (size_t)RedisKeyLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = ( sint32 )pRedis->len;
    if ( len > RedisValueLen )
    {
        len = SpaceNotEnough;
    }
    else
    {
        memcpy( pRedisValue , pRedis->str , len );
    }
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::DelRedisListRange( const char* pRedisKey , sint32 RedisKeyLen , sint32 RedisStart , sint32 RedisEnd )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "LTRIM %b %d %d" , pRedisKey , RedisKeyLen , RedisStart , RedisEnd );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 CDBRedis::GetRedisIndexList(const char* pRedisKey , sint32 RedisKeyLen , sint32 Index , char* pRedisValue , sint32 RedisValueLen)
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "LINDEX %b %d" , pRedisKey , ( size_t )RedisKeyLen , Index );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->len;
    if ( len > RedisValueLen )
    {
        len = SpaceNotEnough;
    }
    else
    {
        memcpy( pRedisValue , pRedis->str , len );
    }
    freeReplyObject( pRedis );
    return len;
}

sint32 SS::CDBRedis::GetRedisListLen(const char* pRedisKey , sint32 RedisKeyLen)
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "LLEN %b" , pRedisKey , ( size_t )RedisKeyLen );

    REDIS_NORMAL_JUDGE( pRedis );
    sint32 len = pRedis->integer;
    freeReplyObject( pRedis );
    return len;
}

sint32 SS::CDBRedis::GetRedisRangeList(const char* pRedisKey , sint32 RedisKeyLen , sint32 Start , sint32 End , std::vector<NLMISC::CSString>& VstrList )
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command( "LRANGE %b %d %d" , pRedisKey , ( size_t )RedisKeyLen , Start , End );

    REDIS_NORMAL_JUDGE( pRedis );
    VstrList.clear();
    for ( sint32 idx = 0; idx < pRedis->elements; idx++ )
    {
        VstrList.push_back( NLMISC::CSString( pRedis->element[idx]->str ) );
    }

    freeReplyObject( pRedis );
    return 0;
}

sint32 SS::CDBRedis::SetRedisList(const char* pRedisKey , sint32 RedisKeyLen , sint32 Index , const char* pRedisValue , sint32 RedisValueLen)
{
    redisReply* pRedis = NULL;
    pRedis = ( redisReply* )Command("LSET %b %d %b" , pRedisKey , ( size_t )RedisKeyLen , Index , pRedisValue , RedisValueLen );

    REDIS_NORMAL_JUDGE( pRedis );
    return 0;
}

SS_NAMESPACE_END_DECL

