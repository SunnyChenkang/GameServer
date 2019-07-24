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

SS_NAMESPACE_BEGIN_DECL

class CJsonLoad : public NLMISC::CSingleton< CJsonLoad >
{
public:
    CJsonLoad( void ){ };
   ~CJsonLoad( void ){ };

    //   ����ȫ������;
    void JsonLoadTable( void );

    SS_PROPERTY( CJsonMessageConfig     , MessageConfig     , public );
    SS_PROPERTY( CJsonGameConfig        , GameConfig        , public );
    SS_PROPERTY( CJsonGameConsumeConfig , GameConsumeConfig , public );
    SS_PROPERTY( CJsonItemConfig        , ItemConfig        , public );
    SS_PROPERTY( CJsonMissionConfig     , MissionConfig     , public );
    SS_PROPERTY( CJsonStatisticsConfig  , StatisticsConfig  , public );
    SS_PROPERTY( CCreateRoleConfig      , CreateRoleConfig  , public );
};

SS_NAMESPACE_END_DECL

#define JsonLoad                    SS::CJsonLoad::instance()
#define JsonMessageConfig           JsonLoad.m_MessageConfig
#define JsonGameConfig              JsonLoad.m_GameConfig
#define JsonGameConsumeConfig       JsonLoad.m_GameConsumeConfig
#define JsonItemConfig              JsonLoad.m_ItemConfig
#define JsonMissionConfig           JsonLoad.m_MissionConfig
#define JsonStatisticsConfig        JsonLoad.m_StatisticsConfig
#define JsonCreateRoleConfig        JsonLoad.m_CreateRoleConfig

#endif // SS_JSON_LOAD_H_