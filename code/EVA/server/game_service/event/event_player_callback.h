#ifndef GSE_EVENT_PLAYER_CALLBACK_H_
#define GSE_EVENT_PLAYER_CALLBACK_H_

#include <game_service/game_service/game_service_def.h>
#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>

GSE_NAMESPACE_BEGIN_DECL

class CEventPlayerCallBack : public sigslot::has_slots<> , public NLMISC::CSingleton< CEventPlayerCallBack>
{
public:
    void InitEventCallBack( void );

private:
    void CallBackPlayerLoadFinish( CRecordPlayer& );    /// 玩家数据加载完成;
    void CallBackPlyaerLoginFinish( PB_UserLogin& );    /// 玩家登陆完成;
    void CallBackPlayerOffline( ROLE_ID );              /// 玩家离线事件;
    void CallBackChangeScenes( CPlayerPtr );            /// 玩家切换场景;
};

#define EventPlayerCallBack CEventPlayerCallBack::getInstance()

GSE_NAMESPACE_END_DECL

#endif// GSE_EVENT_PLAYER_CALLBACK_H_