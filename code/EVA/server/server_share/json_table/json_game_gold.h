#ifndef SS_JSON_GAME_GOLD_H_
#define SS_JSON_GAME_GOLD_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

class CGameGoldCell : public CJsonBase
{
    SS_PROPERTY( GAME_ID          , GameID          , private );    /// 游戏自增ID;
    SS_PROPERTY( NLMISC::CSString , GameName        , private );    /// 游戏名字;
    SS_PROPERTY( NLMISC::CSString , GameIconUrl     , private );    /// 游戏图标地址;
    SS_PROPERTY( uint32           , BaseGold        , private );    /// 游戏金币;
    SS_PROPERTY( uint32           , EnterMinGold    , private );    /// 游戏进入金币限制;
    SS_PROPERTY( uint32           , RobotID         , private );    /// 游戏机器人ID;
    PARSE_VALUE_BEGIN

    JsonParseBegin   ( JsonValue );
    JsonParseToInt   ( m_GameID );
    JsonParseToString( m_GameName );
    JsonParseToString( m_GameIconUrl );
    JsonParseToInt   ( m_BaseGold );
    JsonParseToInt   ( m_EnterMinGold );
    JsonParseToInt   ( m_RobotID );
    JsonParseEnd();

    PARSE_VALUE_END
};

class CGameGold : public CJsonBase
{
    PARSE_VALUE_BEGIN
    JsonParseBegin( JsonValue );
    CGameGoldCell* pGameCell = new CGameGoldCell();
    pGameCell->ParseJson( JsonValue );
    m_JsonUint32Array.insert( std::make_pair( pGameCell->GetGameID() , pGameCell ));
    JsonParseEnd( );
    PARSE_VALUE_END
};

SS_NAMESPACE_END_DECL

#endif//SS_JSON_GAME_GOLD_H_