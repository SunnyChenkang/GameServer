#include "json_load.h"

void SS::CJsonLoad::JsonLoadTable( void )
{
    JsonMessageConfig.LoadJson("fes_message.json");
    JsonRoomConfig.LoadJson("room_config.json");
    JsonRoomConsumeConfig.LoadJson("room_consume_config.json");
    JsonItemConfig.LoadJson( "item_config.json" );
    JsonMissionConfig.LoadJson( "mission_config.json" );
    JsonStatisticsConfig.LoadJson( "statistics_config.json" );
    JsonCreateRoleConfig.LoadJson( "create_role_config.json");
}
