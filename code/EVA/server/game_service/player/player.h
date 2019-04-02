#ifndef GES_PLAYER_H_
#define GES_PLAYER_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CPlayer
{
public:
    CPlayer( void ) { };
    CPlayer( CRecordPlayer& );
   ~CPlayer( void );

    // serial;
    void serial( NLMISC::IStream& s )
    {
        s.serial    ( m_FrontendServiceId );
        s.serial    ( m_RecordPlayer.RecordPlayerInfo );
        s.serialCont( m_RecordPlayer.RecordItem );
        s.serialCont( m_RecordPlayer.RecordStatisics );
        s.serialCont( m_RecordPlayer.RecordStatisics );
    }

    // 获取玩家基础数据;
    CRecordPlayerInfo& GetRecordPlayerInfo( void )  { return m_RecordPlayer.RecordPlayerInfo; }
    // 获取玩家道具数据;
    TRecordItem&       GetRecordItemInfo( void )   { return m_RecordPlayer.RecordItem; }
    // 获取玩家统计数据;
    TRecordStatisics&  GetRecordStatisics( void )   { return m_RecordPlayer.RecordStatisics; }
    // 获取玩家任务数据;
    TRecordMission&    GetRecordMission( void )    { return m_RecordPlayer.RecordMission; }

    SS_PROPERTY( NLNET::TServiceId  , FrontendServiceId , private ); // 消息频道;
    SS_PROPERTY( ROOM_ID            , RoomID            , private ); // 房间ID;

private:
    CRecordPlayer m_RecordPlayer;
};

GSE_NAMESPACE_END_DECL

#endif//GES_PLAYER_H_