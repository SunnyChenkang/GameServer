#ifndef SERVER_SHARED_RECORDPLAYER_H_
#define SERVER_SHARED_RECORDPLAYER_H_

#include "db_record_base.h"
#include "db_record_player_info.h"
#include "db_record_item.h"
#include "db_record_mission.h"
#include "db_record_statistics.h"

SS_NAMESPACE_BEGIN_DECL

class CRecordPlayer : public CRecordBase
{
public:
    CRecordPlayer( void ) { };
    virtual ~CRecordPlayer( void ) { };

    CRecordPlayerInfo   RecordPlayerInfo;   // 玩家基础信息;
    TRecordItem         RecordItem;         // 玩家道具信息;
    TRecordMission      RecordMission;      // 玩家任务信息;
    TRecordStatisics    RecordStatisics;    // 玩家统计信息;

    void serial( NLMISC::IStream& s )
    {
        s.serial    ( m_DBState );
        s.serial    ( RecordPlayerInfo );
        s.serialCont( RecordItem );
        s.serialCont( RecordMission );
        s.serialCont( RecordStatisics );
    }
};

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_DBRECORDPLAYER_H_