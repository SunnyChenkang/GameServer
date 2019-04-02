#ifndef SS_JSON_ROOM_CONFIG_H_
#define SS_JSON_ROOM_CONFIG_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

class CJsonRoomCell : public CJsonBase
{
    SS_PROPERTY( NLMISC::CSString , RoomName        , private );    // 房间名字;
    SS_PROPERTY( uint32           , RoomMax         , private );    // 房间人数;
    SS_PROPERTY( uint32           , RoomMin         , private );    // 房间人数;
    SS_PROPERTY( uint32           , RoomDeleteTime  , private );    // 房间删除时间;
    SS_PROPERTY( NLMISC::CSString , RoomIcon        , private );    // 房间图标;
    SS_PROPERTY( NLMISC::CSString , RoomDesc        , private );    // 房间描述;

    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin   ( JsonValue );
        JsonParseToString( m_RoomName );
        JsonParseToUInt  ( m_RoomMax  );
        JsonParseToUInt  ( m_RoomMin  );
        JsonParseToUInt  ( m_RoomDeleteTime );
        JsonParseToString( m_RoomIcon );
        JsonParseToString( m_RoomDesc );
        JsonParseEnd();
    }
};

class CJsonRoomConfig : public CJsonBase
{
    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin( JsonValue );
        CJsonRoomCell* pCell = new CJsonRoomCell();
        pCell->ParseJson( Values );
        m_JsonStringArray.insert(std::make_pair( pCell->GetRoomName() , pCell ) );
        JsonParseEnd();
    }
};

SS_NAMESPACE_END_DECL

#endif //SS_JSON_ROOM_CONFIG_H_