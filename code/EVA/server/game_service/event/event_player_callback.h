#ifndef GSE_EVENT_PLAYER_CALLBACK_H_
#define GSE_EVENT_PLAYER_CALLBACK_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CEventPlayerCallBack : public sigslot::has_slots<> , public NLMISC::CSingleton< CEventPlayerCallBack>
{
public:
    void InitEventCallBack( void );

private:
    void CallBackUserLoad( CRecordPlayer& );        //   用户数据加载;
    void CallBackUserLogin( PB_UserLogin& );        //   用户登录事件;
    void CallBackUserOffline( ROLE_ID );            //   用户离线事件;
    void CallBackChangeScenes( CPlayer& );          //   用户切换场景;
};

#define EventPlayerCallBack CEventPlayerCallBack::getInstance()

GSE_NAMESPACE_END_DECL

#endif// GSE_EVENT_PLAYER_CALLBACK_H_