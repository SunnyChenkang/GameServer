#ifndef SS_DBREDIS_INTERFACE_H_
#define SS_DBREDIS_INTERFACE_H_

#include <server_share/common/common.h>

SS_NAMESPACE_BEGIN_DECL

class CDBRedisInterface : public NLMISC::CSingleton< CDBRedisInterface >
{
    SS_PROPERTY_QUOTE( CDBRedis , DBRedisLogin        , private );
    SS_PROPERTY_QUOTE( CDBRedis , DBRedisPlayer       , private );
    SS_PROPERTY_QUOTE( CDBRedis , DBRedisGame         , private );
    SS_PROPERTY_QUOTE( CDBRedis , DBRedisMatch        , private );
    SS_PROPERTY_QUOTE( CDBRedis , DBRedisGameRecord   , private );
};

#define DBRedisLogin      CDBRedisInterface::getInstance().GetDBRedisLogin()        /// 登录相关;
#define DBRedisPlayer     CDBRedisInterface::getInstance().GetDBRedisPlayer()       /// 玩家相关;
#define DBRedisGame       CDBRedisInterface::getInstance().GetDBRedisGame()         /// 游戏相关;
#define DBRedisMatch      CDBRedisInterface::getInstance().GetDBRedisMatch()        /// 比赛相关;
#define DBRedisGameRecord CDBRedisInterface::getInstance().GetDBRedisGameRecord()   /// 游戏回放;

SS_NAMESPACE_END_DECL

#endif//SS_DBREDIS_INTERFACE_H_