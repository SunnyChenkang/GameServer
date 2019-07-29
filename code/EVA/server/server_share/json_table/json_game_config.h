#ifndef SS_JSON_GAME_CONFIG_H_
#define SS_JSON_GAME_CONFIG_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

/// 游戏属性参数;
class CJsonGameCell : public CJsonBase
{
    SS_PROPERTY( NLMISC::CSString , GameName        , private );    // 游戏名字;
    SS_PROPERTY( uint32           , GameMax         , private );    // 游戏人数;
    SS_PROPERTY( uint32           , GameMin         , private );    // 游戏人数;
    SS_PROPERTY( uint32           , GameDeleteTime  , private );    // 游戏删除时间;
    SS_PROPERTY( NLMISC::CSString , GameIcon        , private );    // 游戏图标;
    SS_PROPERTY( NLMISC::CSString , GameDesc        , private );    // 游戏描述;


    PARSE_VALUE_BEGIN

    JsonParseBegin   ( JsonValue );
    JsonParseToString( m_GameName );
    JsonParseToUInt  ( m_GameMax  );
    JsonParseToUInt  ( m_GameMin  );
    JsonParseToUInt  ( m_GameDeleteTime );
    JsonParseToString( m_GameIcon );
    JsonParseToString( m_GameDesc );
    JsonParseEnd();

    PARSE_VALUE_END
};


class CJsonGameConfig : public CJsonBase
{
    PARSE_VALUE_BEGIN

    JsonParseBegin( JsonValue );
    CJsonGameCell* pGameCell = new CJsonGameCell();
    pGameCell->ParseJson( Values );
    m_JsonStringArray.insert(std::make_pair( pGameCell->GetGameName() , pGameCell ) );
    JsonParseEnd();

    PARSE_VALUE_END
};

SS_NAMESPACE_END_DECL

#endif //SS_JSON_GAME_CONFIG_H_