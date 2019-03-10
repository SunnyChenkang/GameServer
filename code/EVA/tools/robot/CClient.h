#ifndef CClient_h__
#define CClient_h__

#include "CConnect.h"
#include "CRobotHelper.h"

#include "role/CPlayerInfo.h"
#include "role/CPlayerMail.h"
#include "role/CPlayerFriend.h"
#include "role/CPlayerAchievement.h"
#include "role/CPlayerMahjong.h"
#include "role/CPlayerItem.h"
#include "role/CPlayerMission.h"
#include "role/CPlayerStatistics.h"

#include <game_share/game_def.h>
#include <server_share/database/db_logic_chunk.h>

class CClient : public CConnect 
              , public CPlayerInfo
              , public CPlayerMailInfo
              , public CPlayerFriendInfo
              , public CPlayerAchievementInfo
              , public CPlayerMahjong
              , public CPlayerItem
              , public CPlayerMission
              , public CPlayerStatistics
{
public:
    CClient( void );
    virtual ~CClient( void );

    // 重置函数;
    void OnReset( void );
    // 更新函数;
    void OnUpdate( void );
    // 创建定时器;
    void OnCreateTimer( const char* lua_usename , const char* lua_funname , int time , bool flag = false );
    // 设置客户端状态;
    void SetClientState( ClientState State ){ m_ClientState = State ;}
    // 验证账号中;
    bool IsAuthAccountState( void ){ return ( m_ClientState == client_state_authaccount ) ; }
    // 登陆中;
    bool IsLoginState( void ){ return ( m_ClientState == client_state_login ) ; }
    // 创建角色;
    bool IsCreateRoleState( void ){ return ( m_ClientState == client_state_createrole ) ; }
    // 加载玩家状态;
    bool IsLoadPlayerState( void ) { return ( m_ClientState == client_state_createrole ) ; }
    // 登陆成功;
    bool IsOnlineState( void ) { return ( m_ClientState == client_state_online ) ; }

    // 检查RCR32长度;
    uint32 GetBufferLenght( google::protobuf::Message* Message );
    // 设置同步状态;
    void SetSyncCleintState( uint32 unSyncValue );
    // 取消同步状态;
    void CleSyncClientState( uint32 unSyncValue );
    // 是否同步完成;
    bool IsSyncSucceed( void );
    
    // 进入房间类型;
    void SetRoomType( std::string value ) { m_strRoomType = value; }
    std::string GetRoomType( ) { return m_strRoomType; }

    void ClearTimer();

    void SetMountLuaType( MountLuaType type ) { m_MountLuaType = type; }
    bool IsInBlackJack() { return m_MountLuaType == MountLua_BlackJack; }
    bool IsInTexasPoker() { return m_MountLuaType == MountLua_TexasPoker; }
    bool IsInSlots() { return m_MountLuaType == MountLua_Slots; }
    bool IsInHall() { return m_MountLuaType == MountLua_Hall; }
    bool IsInMahJong() { return m_MountLuaType == MountLua_MahJong; }
   
    // 获取成就CRC长度;
    DEF::CHECK_SUM GetCRC32Achievement( void );
    // 获取道具CRC长度;
    DEF::CHECK_SUM GetCRC32Item( void );
    // 获取任务CRC长度;
    DEF::CHECK_SUM GetCRC32Mission( void );
private:
    // 挂载脚本;
    MountLuaType             m_MountLuaType;
    // 进入房间类型;
    std::string              m_strRoomType;
    // 绑定计时器队列;
    std::deque< CTimer* >    m_TimerQueue;
    // 客户端状态;
    ClientState              m_ClientState;
    // 异步登陆状态;
    uint32                   m_SyncLoginState;
};

#endif // CClient_h__