#ifndef GSE_MISSION_MANAGER_H_
#define GSE_MISSION_MANAGER_H_

#include <server_share/common/common.h>

GSE_NAMESPACE_BEGIN_DECL

class CMissionManager : public NLMISC::CSingleton< CMissionManager >
{
public:
    //   更新任务;
    void UpdateMission( ROLE_ID , MISSION_ID );
    void UpdateMission( ROLE_ID , MISSION_ID , uint32 );

    //   领取任务;
    void RewardMission( ROLE_ID , MISSION_ID ){ };

private:
    //   检查任务是否无效;
    bool IsInValidMission( MISSION_ID );
    //   检查任务是否完成;
    bool IsDoneMission ( MISSION_ID );
    //   重置任务;
    void ResetMission( ROLE_ID , MISSION_ID );
};

#define MissionManager CMissionManager::getInstance();

GSE_NAMESPACE_END_DECL

#endif//GSE_MISSION_MANAGER_H_