#include "db_record_player_info.h"

SS_NAMESPACE_BEGIN_DECL

CRecordPlayerInfo::CRecordPlayerInfo( void ) : m_RoleID( 0 )
                                             , m_RoleKind( 0 )
                                             , m_GameTime( 0 )
                                             , m_LastHost( "" )
                                             , m_CreateTime( 0 )
                                             , m_LastLoginTime( 0 )
                                             , m_LastOfflineTime( 0 )
                                             , m_NickName( "" )
                                             , m_HeadID( 0 )
{
    m_RoleState.resetEnumValue( ROLE_STATE_NULL );
}

CRecordPlayerInfo::~CRecordPlayerInfo( void )
{
    
}

SS_NAMESPACE_END_DECL
