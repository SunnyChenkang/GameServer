#ifndef SS_DBREDIS_INTERFACE_H_
#define SS_DBREDIS_INTERFACE_H_

#include <server_share/common/common.h>

SS_NAMESPACE_BEGIN_DECL

class CDBRedisInterface : public NLMISC::CSingleton< CDBRedisInterface >
{
    SS_PROPERTY( CDBRedis , DBRedisLogin  , public );
    SS_PROPERTY( CDBRedis , DBRedisPlayer , public );
    SS_PROPERTY( CDBRedis , DBRedisGame   , public );
    SS_PROPERTY( CDBRedis , DBRedisMatch  , public );
};

SS_NAMESPACE_END_DECL

#define DBRedisInterface CDBRedisInterface::getInstance()

#define DBRedisLogin     DBRedisInterface.m_DBRedisLogin        /// 登录相关;
#define DBRedisPlayer    DBRedisInterface.m_DBRedisPlayer       /// 玩家相关;
#define DBRedisGame      DBRedisInterface.m_DBRedisGame         /// 游戏相关;
#define DBRedisMatch     DBRedisInterface.m_DBRedisMatch        /// 比赛相关;
#endif//SS_DBREDIS_INTERFACE_H_