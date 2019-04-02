#ifndef PSE_DBMANAGER_H_
#define PSE_DBMANAGER_H_

#include <persistent_service/persistent_service/persistent_service_def.h>

PSE_NAMESPACE_BEGIN_DECL

class CDBManager : public NLMISC::CSingleton< CDBManager >
{
public:
    //   创建角色;
    bool CreatePlayer( LoadUserData* );
    //   保存角色;
    void SavePlayerInfo( LoadUserData* );

    //   更新角色基础信息;
    void UpdateDBPlayer ( CRecordPlayerInfo& );
    //   更新角色道具信息;
    void UpdateDBItem   ( TRecordItem& );
    void UpdateDBItem   ( CRecordItem& );
    //   更新角色任务信息;
    void UpdateDBMission( TRecordMission& );
    void UpdateDBMission( CRecordMission& );
    //   更新角色统计信息;
    void UpdateDBStatistics( TRecordStatisics& );
    void UpdateDBStatistics( CRecordStatistics& );

    //   获取玩家实例;
    CRecordPlayer* GetPlayerInfo( ROLE_ID );
    //   全部存储;
    void CloseServiceSaveDBData( void );

    SS_PROPERTY( PLAYER_TABLE , PlayerTable , private );
};

#define DBManager CDBManager::instance()

PSE_NAMESPACE_END_DECL

#endif// PSE_DBMANAGER_H_