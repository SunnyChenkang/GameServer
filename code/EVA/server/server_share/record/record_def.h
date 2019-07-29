#ifndef SERVER_SHARED_RECORD_DEF_H_
#define SERVER_SHARED_RECORD_DEF_H_

#include <server_share/common/common.h>
#include "record_base.h"

SS_NAMESPACE_BEGIN_DECL

// db handler event;
enum DBEventEnum
{
    DB_EVENT_NULL   = 0x0,
    DB_EVENT_INSERT = 0x1 , // 数据库插入;
    DB_EVENT_UPDATE = 0x2 , // 数据库更新;
    DB_EVENT_DELETE = 0x4 , // 数据库删除;
};

class CRecordItem;
class CRecordMission;
class CRecordStatistics;

// 道具表;
typedef std::map< ITEM_ID , CRecordItem >               TRecordItem;
// 任务表;
typedef std::map< MISSION_ID , CRecordMission >         TRecordMission;
// 统计表;
typedef std::map< STATISTICS_ID , CRecordStatistics >   TRecordStatisics;

SS_NAMESPACE_END_DECL

#endif //SERVER_SHARED_RECORD_DEF_H_;

