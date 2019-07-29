#ifndef SS_JSON_LOAD_H_
#define SS_JSON_LOAD_H_

#include <server_share/common/common.h>
#include "json_message_config.h"
#include "json_game_config.h"
#include "json_game_consume_config.h"
#include "json_item_config.h"
#include "json_mission_config.h"
#include "json_statistics_config.h"
#include "json_create_role_config.h"
#include "json_game_gold.h"
#include "json_game_robot.h"

SS_NAMESPACE_BEGIN_DECL

class CJsonLoad : public NLMISC::CSingleton< CJsonLoad >
{
public:
    CJsonLoad( void ){ };
   ~CJsonLoad( void ){ };

    SS_PROPERTY( CMessageConfig     , MessageConfig     , public );
    SS_PROPERTY( CGameConfig        , GameConfig        , public );
    SS_PROPERTY( CGameConsumeConfig , GameConsumeConfig , public );
    SS_PROPERTY( CItemConfig        , ItemConfig        , public );
    SS_PROPERTY( CMissionConfig     , MissionConfig     , public );
    SS_PROPERTY( CStatisticsConfig  , StatisticsConfig  , public );
    SS_PROPERTY( CCreateRoleConfig  , CreateRoleConfig  , public );
    SS_PROPERTY( CGameGold          , GameGoldConfig    , public );
    SS_PROPERTY( CGameRobot         , GameRobotConfig   , public );

    ///  º”‘ÿ»´≤ø≈‰÷√;
    void JsonLoadTable( void );
};

SS_NAMESPACE_END_DECL

#define JsonMessageConfig       SS::CJsonLoad::instance().m_MessageConfig
#define JsonGameConfig          SS::CJsonLoad::instance().m_GameConfig
#define JsonGameConsumeConfig   SS::CJsonLoad::instance().m_GameConsumeConfig
#define JsonItemConfig          SS::CJsonLoad::instance().m_ItemConfig
#define JsonMissionConfig       SS::CJsonLoad::instance().m_MissionConfig
#define JsonStatisticsConfig    SS::CJsonLoad::instance().m_StatisticsConfig
#define JsonCreateRoleConfig    SS::CJsonLoad::instance().m_CreateRoleConfig
#define JsonGameGold            SS::CJsonLoad::instance().m_GameGoldConfig
#define JsonGameRobot           SS::CJsonLoad::instance().m_GameRobotConfig

#endif // SS_JSON_LOAD_H_