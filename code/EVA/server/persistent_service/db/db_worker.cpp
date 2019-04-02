#include "db_worker.h"

PSE_NAMESPACE_BEGIN_DECL

bool InitLoadPlayer( CDBExecute* pWorker )
{
    pWorker->AddStmt( SQL_STMT_IS_EXIST_PLAYER           , "CALL t_is_exist_player(?)" );
    pWorker->AddStmt( SQL_STMT_LOAD_PLAYERINFO           , "CALL t_load_player(?)" );
    pWorker->AddStmt( SQL_STMT_LOAD_ITEM                 , "CALL t_load_item(?)" );
    pWorker->AddStmt( SQL_STMT_LOAD_STATISTICS           , "CALL t_load_statistics(?)" );
    pWorker->AddStmt( SQL_STMT_LOAD_MISSION              , "CALL t_load_mission(?)" );
    return true;
}

bool InitPlayerInfoWoker( CDBExecute* pWorker )
{
    pWorker->AddStmt( SQL_STMT_INSERT_PLAYERINFO         , "CALL t_insert_player(?,?,?,?,?,?,?,?)" );
    pWorker->AddStmt( SQL_STMT_DELETE_PLAYERINFO         , "CALL t_delete_player(?)" );
    pWorker->AddStmt( SQL_STMT_UPDATE_PLAYERINFO         , "CALL t_update_player(?,?,?,?,?,?,?)" );
    return true;
}

bool InitItemWorker( CDBExecute* pWorker )
{
    pWorker->AddStmt( SQL_STMT_INSERT_ITEM               , "CALL t_insert_item(?,?,?,?)" );
    pWorker->AddStmt( SQL_STMT_DELETE_ITEM               , "CALL t_delete_item(?)" );
    pWorker->AddStmt( SQL_STMT_UPDATE_ITEM               , "CALL t_update_item(?,?,?,?)" );
    return true;
}

bool InitStatisticsWorker( CDBExecute* pWorker )
{
    pWorker->AddStmt( SQL_STMT_INSERT_STATISTICS         , "CALL t_insert_statistics(?,?,?)" );
    pWorker->AddStmt( SQL_STMT_DELETE_STATISTICS         , "CALL t_update_statistisc(?)" );
    pWorker->AddStmt( SQL_STMT_UPDATE_STATISTICS         , "CALL t_update_statistics(?,?,?)" );
    return true;
}

bool InitMissionWorker( CDBExecute* pWorker )
{
    pWorker->AddStmt( SQL_STMT_INSERT_MISSION            , "CALL t_insert_mission(?,?,?,?,?)" );
    pWorker->AddStmt( SQL_STMT_DELETE_MISSION            , "CALL t_delete_mission(?)" );
    pWorker->AddStmt( SQL_STMT_UPDATE_MISSION            , "CALL t_update_mission(?,?,?,?,?)");
    return true;
}

PSE_NAMESPACE_END_DECL