#ifndef SERVER_SHARED_RECORDPLAYER_H_
#define SERVER_SHARED_RECORDPLAYER_H_

#include "record_base.h"
#include "record_player_info.h"
#include "record_item.h"
#include "record_mission.h"
#include "record_statistics.h"

SS_NAMESPACE_BEGIN_DECL

class CRecordPlayer : public CRecordBase
{
public:
    CRecordPlayer( void ) { };
    virtual ~CRecordPlayer( void ) { };

    /// 玩家基础信息;
    SS_PROPERTY_QUOTE( CRecordPlayerInfo , RecordBasePlayer , private );
    /// 玩家道具信息;
    SS_PROPERTY_QUOTE( TRecordItem       , RecordItem       , private );
    /// 玩家任务信息;
    SS_PROPERTY_QUOTE( TRecordMission    , RecordMission    , private );
    /// 玩家统计信息;
    SS_PROPERTY_QUOTE( TRecordStatisics  , RecordStatisics  , private );

    /// serial;
    void serial( NLMISC::IStream& s )
    {
        s.serial    ( m_DBState );
        s.serial    ( m_RecordBasePlayer );
        s.serialCont( m_RecordItem );
        s.serialCont( m_RecordMission );
        s.serialCont( m_RecordStatisics );
    }
};


SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_DBRECORDPLAYER_H_