#ifndef GSE_MISSION_MANAGER_H_
#define GSE_MISSION_MANAGER_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CMissionManager : public NLMISC::CSingleton< CMissionManager >
{
public:
    ///   更新任务;
    void UpdateMission( ROLE_ID , MISSION_ID );
    void UpdateMission( ROLE_ID , MISSION_ID , uint32 );

private:
    ///  检查任务是否无效;
    bool IsInValidMission( MISSION_ID );
    ///  检查任务是否完成;
    bool IsDoneMission ( ROLE_ID , MISSION_ID );
    ///  重置任务;
    void ResetMissionInfo( ROLE_ID , MISSION_ID );
    ///  获取任务信息;
    CRecordMission* GetMissionInfo( ROLE_ID , MISSION_ID , bool IsAdd = false );
};

#define MissionManager CMissionManager::getInstance();

GSE_NAMESPACE_END_DECL

#endif//GSE_MISSION_MANAGER_H_