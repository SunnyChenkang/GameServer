#include "record_mission.h"

SS_NAMESPACE_BEGIN_DECL

CRecordMission::CRecordMission( void ) : m_RoleID( 0 )
                                       , m_MissionID( 0 )
                                       , m_MissionState( MISSION_STATE_ACCEPT )
                                       , m_MissionTarGet( 0 )
                                       , m_MissionReceiveTime( NLMISC::CTime::getSecondsSince1970() )
{
    
}

CRecordMission::~CRecordMission( void )
{
    
}

SS_NAMESPACE_END_DECL