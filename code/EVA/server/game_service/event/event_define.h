#ifndef GSE_EVENT_DEF_H_
#define GSE_EVENT_DEF_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CEventDefine : public NLMISC::CSingleton< CEventDefine >
{
public:
    sigslot::signal1< CRecordPlayer& >                                          EventUserLoad;      // 用户数据加载;
    sigslot::signal1< PB_UserLogin& >                                           EventUserLogin;     // 用户登录;
    sigslot::signal1< ROLE_ID >                                                 EventUserOffline;   // 用户下线;
    sigslot::signal1< CPlayer& >                                                EventChangeScenes;  // 切换场景;
    sigslot::signal2< ROLE_ID , ROOM_ID >                                       EventJoinRoom;      // 加入房间;
    sigslot::signal2< ROLE_ID , ROOM_ID >                                       EventLeaveRoom;     // 离开房间;
    sigslot::signal2< ROOM_ID , std::vector<ROLE_ID>& >                         EventDeleteRoom;    // 删除房间;
    sigslot::signal1< ROOM_ID >                                                 EventGameStart;     // 游戏开始;
    sigslot::signal1< ROOM_ID >                                                 EventGameOwer;      // 游戏结束;
    sigslot::signal5< ROLE_ID , ITEM_ID , uint32 , uint32 , PB_DotItem >        EventAddItem;       // 添加道具;
    sigslot::signal5< ROLE_ID , ITEM_ID , uint32 , uint32 , PB_DotItem >        EventSubItem;       // 扣减道具;
};

#define EventDefine CEventDefine::instance()

GSE_NAMESPACE_END_DECL

#endif //GSE_EVENT_DEF_H_