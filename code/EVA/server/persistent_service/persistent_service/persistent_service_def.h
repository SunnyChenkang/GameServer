#ifndef PSE_DEF_H_
#define PSE_DEF_H_

#include <server_share/common/common.h>

#include <server_share/record/db_record_dot_data.h>
#include <server_share/record/db_record_player.h>

#include <server_share/json_table/json_load.h>
#include <server_share/db/mysql/db_mysql.h>
#include <server_share/db/mysql/db_result.h>

#include <persistent_service/message/message_login.h>
#include <persistent_service/message/message_db_event.h>
#include <persistent_service/message/message_service.h>

PSE_NAMESPACE_BEGIN_DECL

using namespace SS;

typedef std::map< ROLE_ID , CRecordPlayer > PLAYER_TABLE;

// MYSQL STMT;
enum TSQLStmt
{

    SQL_STMT_LOAD_PLAYERINFO            = 1,
    SQL_STMT_LOAD_ITEM                  = 2,
    SQL_STMT_LOAD_MISSION               = 3,
    SQL_STMT_LOAD_STATISTICS            = 4,
    SQL_STMT_IS_EXIST_PLAYER            = 5,

    // d_player.t_playerinfo;
    SQL_STMT_INSERT_PLAYERINFO          = 50,
    SQL_STMT_DELETE_PLAYERINFO          = 51,
    SQL_STMT_UPDATE_PLAYERINFO          = 52,

    // d_player.t_item;
    SQL_STMT_INSERT_ITEM                = 100,
    SQL_STMT_DELETE_ITEM                = 101,
    SQL_STMT_UPDATE_ITEM                = 102,

    // d_player.t_statistics;
    SQL_STMT_INSERT_STATISTICS          = 150,
    SQL_STMT_DELETE_STATISTICS          = 151,
    SQL_STMT_UPDATE_STATISTICS          = 152,

    // d_player.t_mission;
    SQL_STMT_INSERT_MISSION             = 200,
    SQL_STMT_DELETE_MISSION             = 201,
    SQL_STMT_UPDATE_MISSION             = 202,
};

// 加载用户数据;
class LoadUserData : public CRecordBase
{
public:
    virtual ~LoadUserData( void ) { }

    LoadUserData( PB_UserLogin& rhs )
    {
        SetLoadPlayerState( false );
        SetRoleID( rhs.role_id() );
        SetRoleKind( rhs.role_kind() );
        SetFrontendServiceID( NLNET::TServiceId( rhs.frontend_service_id() ) );
        SetGameServiceID( NLNET::TServiceId( rhs.game_service_id() ) );
        SetClientHost( rhs.client_host() );
    }

    SS_PROPERTY( bool              , LoadPlayerState    , public );
    SS_PROPERTY( ROLE_ID           , RoleID             , public );
    SS_PROPERTY( uint32            , RoleKind           , public );
    SS_PROPERTY( NLNET::TServiceId , FrontendServiceID  , public );
    SS_PROPERTY( NLNET::TServiceId , GameServiceID      , public );
    SS_PROPERTY( NLMISC::CSString  , ClientHost         , public );
    SS_PROPERTY( CRecordPlayer     , RecordPlayer       , public );
};

PSE_NAMESPACE_END_DECL

#endif // PSE_DEF_H_