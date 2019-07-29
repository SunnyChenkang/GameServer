#ifndef SS_JSON_GAME_ROBOT_H_
#define SS_JSON_GAME_ROBOT_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

class CGameRobotCell : public CJsonBase
{
    SS_PROPERTY( uint32 , RobotID       , private );
    SS_PROPERTY( uint32 , RobotAI       , private );
    SS_PROPERTY( uint32 , EnterMinTime  , private );
    SS_PROPERTY( uint32 , EnterMaxTime  , private );
    SS_PROPERTY( uint32 , LeaveMinTime  , private );
    SS_PROPERTY( uint32 , LeaveMaxTime  , private );
    SS_PROPERTY( uint32 , QuicMinCount  , private );    // 0永远不退出;
    SS_PROPERTY( uint32 , QuicMaxCount  , private );    // 0永远不退出;

    PARSE_VALUE_BEGIN

    JsonParseBegin ( JsonValue );
    JsonParseToUInt( m_RobotID );
    JsonParseToUInt( m_RobotAI );
    JsonParseToUInt( m_EnterMinTime );
    JsonParseToUInt( m_EnterMinTime );
    JsonParseToUInt( m_LeaveMinTime );
    JsonParseToUInt( m_LeaveMaxTime );
    JsonParseToUInt( m_QuicMinCount );
    JsonParseToUInt( m_QuicMaxCount );
    JsonParseEnd();

    PARSE_VALUE_END
};

class CGameRobot : public CJsonBase
{
    PARSE_VALUE_BEGIN

    JsonParseBegin( JsonValue );
    CGameRobotCell* pGameRobotCell = new CGameRobotCell();
    pGameRobotCell->ParseJson( JsonValue );
    m_JsonUint32Array.insert( std::make_pair( pGameRobotCell->GetRobotID() , pGameRobotCell ));
    JsonParseEnd();

    PARSE_VALUE_END
};

SS_NAMESPACE_END_DECL

#endif//SS_JSON_GAME_ROBOT_H_