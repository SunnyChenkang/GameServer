#ifndef CPlayerInfo_h__
#define CPlayerInfo_h__
#include <game_share/game_def.h>
#include <server_share/database/record_player.h>
#include "../CRobotHelper.h"

class CPlayerInfo
{
public:
    CPlayerInfo( void );
    virtual ~CPlayerInfo( void );


    // 获取玩家UID;
    DEF::UID    GetRoleUID( void ){ return m_PlayerData.uid ; }
    // 获取玩家ID;
    DEF::PID    GetRoleID( void ){ return m_PlayerData.pid ; }
    // 获取玩家名字;
    std::string GetName( void ){ return m_PlayerData.player_name; }
    // 获取玩家等级;
    uint32 GetLevel( void ){ return m_PlayerData.level; }
    // 获取金钱;
    DEF::MONEY GetMoney( void ) { return m_PlayerData.money ; }

    // 更新等级;
    void SetLevel( uint32 value )    { m_PlayerData.level = value; }
    // 添加金钱;
    void AddMoney( DEF::MONEY value ){ m_PlayerData.money += value ; }
    // 添加RMB;
    void AddRMB( DEF::RMB value ) { m_PlayerData.bind += value; }

    // 保存玩家信息;
    void OnSavePlayerInfo( MsgPlayerInfo& data );


protected:

    // 角色基础信息;
    DB_RECORD::CRecordPlayer m_PlayerData;

};

#endif // CPlayerInfo_h__