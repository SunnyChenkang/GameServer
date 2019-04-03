#ifndef SS_JSON_ROOM_CONSUME_CONFIG_H_
#define SS_JSON_ROOM_CONSUME_CONFIG_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

class CJsonRoomConsumeCell : public CJsonBase
{
    SS_PROPERTY( uint32           , ConsumeID   , private );    // 消耗ID;
    SS_PROPERTY( NLMISC::CSString , RoomName    , private );    // 房间名字;
    SS_PROPERTY( ITEM_ID          , ConsumeItem , private );    // 消耗道具ID;
    SS_PROPERTY( uint32           , ConsumeCount, private );    // 消耗数量;
    SS_PROPERTY( uint32           , GameCount   , private );    // 游戏数量;
    SS_PROPERTY( NLMISC::CSString , ConsumeDesc , private );    // 消耗描述;

    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin   ( JsonValue );
        JsonParseToUInt  ( m_ConsumeID );
        JsonParseToString( m_RoomName );
        JsonParseToUInt  ( m_ConsumeItem );
        JsonParseToUInt  ( m_ConsumeCount );
        JsonParseToUInt  ( m_GameCount );
        JsonParseToString( m_ConsumeDesc );
        JsonParseEnd( );
    }
};

class CJsonRoomConsumeConfig : public CJsonBase
{
    void ParseJsonArray( const Value& JsonValue )
    {
        JsonParseArrayBegin( JsonValue );
        CJsonRoomConsumeCell* pCell = new CJsonRoomConsumeCell();
        pCell->ParseJson( Values );
        m_JsonUint32Array.insert(std::make_pair( pCell->GetConsumeID() , pCell ) );
        JsonParseArrayEnd();
    }
};

SS_NAMESPACE_END_DECL

#endif //SS_JSON_ROOM_CONSUME_CONFIG_H_;