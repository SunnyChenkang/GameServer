#ifndef GSE_EVENT_ROOM_CALLBACK_H_
#define GSE_EVENT_ROOM_CALLBACK_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CEventRoomCallBack : public sigslot::has_slots<> , public NLMISC::CSingleton< CEventRoomCallBack >
{
public:
    void InitEventCallBack( void );

private:
    //   用户登录;
    void CallBackPlyaerLoginFinish( PB_UserLogin& );
    //   用户离线;
    void CallBackPlayerOffline( ROLE_ID );
    //   加入房间;
    void CallBackJoinRoom ( ROLE_ID , ROOM_ID );
    //   离开房间;
    void CallBackLeaveRoom( ROLE_ID , ROOM_ID );
    //   删除房间;
    void CallBackDeleteRoom( ROOM_ID , std::vector<ROLE_ID>& );
    //   游戏开始;
    void CallBackGameStart( ROOM_ID );
    //   游戏结束;
    void CallBackGameOwer ( ROOM_ID );
};

#define EventRoomCallBack CEventRoomCallBack::getInstance()

GSE_NAMESPACE_END_DECL


#endif//GSE_EVENT_ROOM_CALLBACK_H_