#ifndef SERVER_SHARED_RECORDMISSION_H_
#define SERVER_SHARED_RECORDMISSION_H_

#include "record_base.h"

SS_NAMESPACE_BEGIN_DECL

class CRecordMission : public CRecordBase
{
public:
    CRecordMission( void );
    virtual ~CRecordMission( void );

    SS_PROPERTY( ROLE_ID    , RoleID                , private );        // 角色ID;
    SS_PROPERTY( MISSION_ID , MissionID             , private );        // 任务ID;
    SS_PROPERTY( uint8      , MissionState          , private );        // 任务状态;
    SS_PROPERTY( uint32     , MissionTarGet         , private );        // 任务目标;
    SS_PROPERTY( uint32     , MissionReceiveTime    , private );        // 领取时间;

    // serial stream;
    void serial( NLMISC::IStream& s )
    {
        s.serial( m_DBState );
        s.serial( m_RoleID );
        s.serial( m_MissionID );
        s.serial( m_MissionState );
        s.serial( m_MissionTarGet );
        s.serial( m_MissionReceiveTime );
    }

    // save
    void SaveDB( void )
    {
        CRecordMission& RecordMission( *this );
        NLNET::CMessage SendMessage("MSG_DB_MISSION");
        SendMessage.serial( RecordMission );
        SS_NETWORK->send( "PSE" , SendMessage );
    }
};

SS_NAMESPACE_END_DECL

#endif //SERVER_SHARED_RECORDMISSION_H_