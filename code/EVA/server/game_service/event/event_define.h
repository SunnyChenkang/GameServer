#ifndef GSE_EVENT_DEF_H_
#define GSE_EVENT_DEF_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CEventDefine : public NLMISC::CSingleton< CEventDefine >
{
public:
    sigslot::signal1< CRecordPlayer& >                                          PlayerLoadFinish;  /// 角色数据加载完成;
    sigslot::signal1< PB_UserLogin& >                                           PlayerLoginFinish; /// 角色登录完成;
    sigslot::signal1< ROLE_ID >                                                 PlayerOffline;     /// 角色下线;
    sigslot::signal1< CPlayerPtr >                                              ChangeScenes;      /// 切换场景;
    sigslot::signal2< ROLE_ID , ROOM_ID >                                       JoinGame;          /// 加入游戏;
    sigslot::signal2< ROLE_ID , ROOM_ID >                                       LeaveRoom;         /// 离开房间;
    sigslot::signal2< ROOM_ID , std::vector<ROLE_ID>& >                         DeleteRoom;        /// 删除房间;
    sigslot::signal2< ROLE_ID , ROOM_ID >                                       GameStart;         /// 游戏开始;
    sigslot::signal2< ROLE_ID , ROOM_ID >                                       GameOwer;          /// 游戏结束;
    sigslot::signal5< ROLE_ID , ITEM_ID , uint32 , uint32 , PB_DotItem >        AddItem;           /// 添加道具;
    sigslot::signal5< ROLE_ID , ITEM_ID , uint32 , uint32 , PB_DotItem >        SubItem;           /// 扣减道具;
};

#define EventDefine CEventDefine::instance()

GSE_NAMESPACE_END_DECL

#endif //GSE_EVENT_DEF_H_