#ifndef LSE_DEF_H_
#define LSE_DEF_H_

#include <server_share/common/common.h>
#include <server_share/db/mysql/db_mysql.h>
#include <server_share/record/record_dot_data.h>

#include <logger_service/message/message_db_event.h>
#include <logger_service/message/message_service.h>

using namespace SS;
using namespace LSE;
using namespace NLMISC;
using namespace NLNET;

LSE_NAMESPACE_BEGIN_DECL

enum TSQLStmt
{
    SQL_STMT_LOG_LOGIN    = 1,
    SQL_STMT_LOG_ITEM     = 2,
    SQL_STMT_LOG_MISSION  = 3,
};

LSE_NAMESPACE_END_DECL

#endif//LSE_DEF_H_

