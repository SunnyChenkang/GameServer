#include "CPlayerMission.h"
#include <game_share/static_table/static_table_mgr.h>


using namespace ATTRIB_TYPE;
using namespace StaticData;

CPlayerMission::CPlayerMission( void )
{
    m_AcceptMission.clear();
    m_Random.rand( NLMISC::CTime::getSecondsSince1970() );
}

CPlayerMission::~CPlayerMission( void )
{

}

void CPlayerMission::OnSavePlayerMission( MsgMissionList& data )
{
    for (int index = 0; index < data.mission_list().size(); ++index )
    {
        const MsgMissionInfo& msg_mission = data.mission_list(index);

        DB_RECORD::CRecordMission Data;
        Data.mission_id    = msg_mission.mission_id();
        Data.state         = msg_mission.state();
        Data.target       = msg_mission.target();

        m_AcceptMission[ Data.mission_id ] = Data;
    }
}

void CPlayerMission::MissionReward( MsgMissionReward& data )
{
    DB_RECORD::TRecordMission::iterator it = m_AcceptMission.find( data.mission_id() );
    if ( it != m_AcceptMission.end() )
    {
        m_AcceptMission.erase( it );
    }
}
