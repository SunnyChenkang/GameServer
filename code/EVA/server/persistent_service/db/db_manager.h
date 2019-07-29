#ifndef PSE_DB_MANAGER_H_
#define PSE_DB_MANAGER_H_

#include <persistent_service/persistent_service/persistent_service_def.h>

PSE_NAMESPACE_BEGIN_DECL

class CDBManager : public NLMISC::CSingleton< CDBManager >
{
public:

    ///  更新角色基础信息;
    void RefreshDBPlayer ( CRecordPlayerInfo& );

    ///  更新道具信息;
    void RefreshDBItem   ( TRecordItem& );
    void RefreshDBItem   ( CRecordItem& );

    ///  更新任务信息;
    void RefreshDBMission( TRecordMission& );
    void RefreshDBMission( CRecordMission& );

    ///  更新统计信息;
    void RefreshDBStatistics( TRecordStatisics& );
    void RefreshDBStatistics( CRecordStatistics& );

    ///  关闭服务器;
    void CloseService( void );
};

#define DBManager CDBManager::instance()

PSE_NAMESPACE_END_DECL

#endif// PSE_DBMANAGER_H_