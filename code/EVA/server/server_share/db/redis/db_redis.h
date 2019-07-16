#ifndef SS_DBREDIS_H_
#define SS_DBREDIS_H_

#include <server_share/db/redis/db_redis_def.h>
#include <server_share/common/common.h>
#include <hiredis/hiredis.h>

SS_NAMESPACE_BEGIN_DECL

class CDBRedis
{
public:
    CDBRedis( void );

    enum ERedis
    {
        NormalError     = -101,     // REDIS常规错误说明用的不对;
        NetError        = -102,     // 网络连接错误;
        SpaceNotEnough  = -103,     // 存储空间不够;
    };

    //   连接服务器;
    bool Connect( const char* , sint32 , uint32 , const char* password = NULL );
    //   断开服务器;
    void Close( void );

private:
    /*
    ** 描述: REDIS原始接口 若执行失败尝试一次重新连接;
    ** 参数: 格式化参数,接收可变参数;
    ** 返回: 执行结果一般为RedisReply*;
    */
    void* Command( const char* format , ... );
    void* CommandArgv( const std::vector< NLMISC::CSString >& , const std::vector< NLMISC::CSString >& );
    void* ExecCommand( const char* , sint32 );

public:
    /****************************************<< STRING操作 >>****************************************/
    /*
    ** 描述: 设置一对KEY,VALUE 若已经存在直接覆盖;
    ** 参数: Lifetime 生存时间( 秒 ) 0代表永不删除;
    ** 返回: 成功返回0;
    */
    sint32 SetRedisKey( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisValue , sint32 RedisValueLen , uint32 RedisLifeTime = 0 );
    sint32 SetRedisKey( NLMISC::CSString RedisKey , NLMISC::CSString RedisValue , uint32 RedisLifeTime = 0 );
    sint32 SetRedisKey( NLMISC::CSString RedisKey , uint32 RedisValue , uint32 RedisLifeTime = 0 );
    sint32 SetRedisKey( NLMISC::CSString RedisKey , uint64 RedisValue , uint32 RedisLifeTime = 0 );

    /*
    ** 描述: 在原有的KEY追加,若KEY不存在直接写入 SetRedisKey;
    ** 返回: 修改后VALUE长度;
    */
    sint32 SetRedisAppend( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisValue , sint32 pRedisValueLen );

    /*
    ** 描述: 设置KEY的生存时间;
    ** 参数: Lifetime 单位秒,0代表永不删除;
    ** 返回: 成功返回0;
    */
    sint32 SetRedisKeyLifeTime( const char* pRedisKey , sint32 RedisKeyLen , uint32 RedisLifeTime = 0 );

    /*
    ** 描述: 获取KEY对应的VALUE;
    ** 返回: 返回长度 0标示不存在;
    */
    sint32 GetRedisKey( const char* pRedisKey , sint32 RedisKeyLen , char* pRedisValue , sint32 RedisValueLen );
    sint32 GetRedisKey( NLMISC::CSString RedisKey , char* pRedisValue , sint32 RedisValueLen );
    sint32 GetRedisKey( NLMISC::CSString RedisKey , NLMISC::CSString& RedisValue );

    /*
    ** 描述: 获取KEY对应的VALUE长度;
    ** 返回: 返回长度 0标示不存在;
    */
    sint32 GetRedisLen( const char* pRedisKey , sint32 RedisKeyLen );

    /*
    ** 描述: 获取KEY剩余时间;
    ** 返回: -2 KEY不存在,-1永久,其它返回剩余时间(秒);
    */
    sint32 GetRedisKeyLifeTime( const char* pRedisKey , sint32 RedisKeyLen );

    /*
    ** 描述: 获取KEY类型;
    ** 返回: -2 KEY不存在,-1永久,其它返回剩余时间(秒);
    */
    sint32 GetRedisKeyKind( const char* pRedisKey , sint32 RedisKeyLen ) { return 0; }

    /*
    ** 描述: 删除KEY;
    ** 返回: 删除成功返回1 , 不存在返回0;
    */
    sint32 DeleteRedisKey( const char* pRedisKey , sint32 RedisKeyLen );

    /*
    ** 描述: 检查KEY是否存在;
    ** 返回: KEY存在返回1,不存在返回0;
    */
    sint32 HasRedisKey( const char* pRedisKey , sint32 RedisKeyLen );

    /*
    ** 描述:  操作多个KEY;
    */
    sint32 SetRedisMultiKey( const std::vector<NLMISC::CSString>& RedisKeyValue );
    sint32 GetRedisMultiKey( const std::vector<NLMISC::CSString>& RedisKey , std::vector<NLMISC::CSString>& RedisValue );
    sint32 DelRedisMultiKey( const std::vector<NLMISC::CSString>& RedisKey );


    /****************************************<< HASH操作 >>****************************************/
    sint32 SetRedisHashField( const char* pRedisKey , sint32 RedisLen , const char* pRedisField , sint32 RedisFieldLen , const char* pRedisValue , sint32 RedisValueLen );
    sint32 GetRedisHashField( const char* pRedisKey , sint32 RedisLen , const char* pRedisField , sint32 RedisFieldLen , char* pRedisValue , sint32 RedisValueLen );
    sint32 DelRedisHashField( const char* pRedisKey , sint32 RedisLen , const char* pRedisField , sint32 RedisFieldLen );

    /*
    ** 描述: HASH操作辅助功能;
    */
    sint32 HasRedisHashKey( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisField , sint32 RedisFieldLen );
    sint32 GetRedisHaskAll( const char* pRedisKey , sint32 RedisKeyLen , std::vector< NLMISC::CSString >& );
    sint32 GetRedisHashFieldCount( const char* pRedisKey , sint32 RedisKeyLen );

    sint32 SetMultiHashField( const char* pRedisKey , sint32 RedisKeyLen , const std::vector< NLMISC::CSString >& );
    sint32 GetMultiHashField( const char* pRedisKey , sint32 RedisKeyLen , const std::vector< NLMISC::CSString >& , std::vector< NLMISC::CSString >& );
    sint32 DelMultiHashField( const char* pRedisKey , sint32 RedisKeyLen , const std::vector< NLMISC::CSString >& );


    /****************************************<< LIST操作 >>****************************************/

    /*
    ** 描述: 列表头部添加 左边;
    */
    sint32 LPushRedisList( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisValue , sint32 RedisValueLen );
    sint32 LPoPRedisList ( const char* pRedisKey , sint32 RedisKeyLen , char* pRedisValue , sint32 RedisValueLen );
    sint32 LPoPRedisList ( const char* pRedisKey , sint32 RedisKeyLen , NLMISC::CSString& );

    /*
    ** 描述: 列表尾部添加 右边;
    */
    sint32 RPushRedisList( const char* pRedisKey , sint32 RedisKeyLen , const char* pRedisValue , sint32 RedisValueLen );
    sint32 RPoPRedisList ( const char* pRedisKey , sint32 RedisKeyLen , char* pRedisValue , sint32 RedisValueLen );
    sint32 RPoPRedisList ( const char* pRedisKey , sint32 RedisKeyLen , NLMISC::CSString& );

    /*
    ** 描述: 对列表进行修剪 保留Start End 区间数据;
    ** 下标为 0  标示列表第一个元素 1 标示列表第二个元素;
    ** 下标为 -1 标示列表最后一个元素 -2 标示列表倒数第二个元素;
    */
    sint32 DelRedisListRange( const char* pRedisKey , sint32 RedisKeyLen , sint32 RedisStart , sint32 RedisEnd );

    sint32 GetRedisIndexList( const char* pRedisKey , sint32 RedisKeyLen , sint32 Index , char* pRedisValue , sint32 RedisValueLen );
    sint32 GetRedisListLen  ( const char* pRedisKey , sint32 RedisKeyLen );
    sint32 GetRedisRangeList( const char* pRedisKey , sint32 RedisKeyLen , sint32 Start , sint32 End , std::vector<NLMISC::CSString>& );
    sint32 SetRedisList     ( const char* pRedisKey , sint32 RedisKeyLen , sint32 Index , const char* pRedisValue , sint32 RedisValueLen );

    SS_PROPERTY( redisContext*      , RedisContext  , private );
    SS_PROPERTY( NLMISC::CSString   , Host          , private );
    SS_PROPERTY( sint32             , Port          , private );
    SS_PROPERTY( uint32             , TimeOut       , private );
};

SS_NAMESPACE_END_DECL

#endif // SS_DBREDIS_H_
