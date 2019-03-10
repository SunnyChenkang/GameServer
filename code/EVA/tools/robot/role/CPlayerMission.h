#ifndef CPlayerMission_h
#define CPlayerMission_h

#include <game_share/game_def.h>
#include <server_share/database/db_logic_chunk.h>
#include <nel/misc/random.h>
#include "../CRobotHelper.h"

class CPlayerMission
{
public:

    CPlayerMission( void );
    virtual ~CPlayerMission( void );

    // 保存任务;
    void OnSavePlayerMission( MsgMissionList& data );

    // 任务领取完奖励;
    void MissionReward( MsgMissionReward& );
private:

protected:
    // 接取任务;
    DB_RECORD::TRecordMission        m_AcceptMission;
    // 随机数;
    NLMISC::CRandom                  m_Random;
};

#endif // CPlayerMail_h__