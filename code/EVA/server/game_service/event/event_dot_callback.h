#ifndef GSE_EVENT_DOT_CALLBACK_H_
#define GSE_EVENT_DOT_CALLBACK_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CEventDotCallBack : public sigslot::has_slots<> , public NLMISC::CSingleton< CEventDotCallBack >
{
public:
    void InitEventCallBack( void );

private:
    void CallBackPlyaerLoginFinish  ( PB_UserLogin& );                                      // 用户登录事件;
    void CallBackPlayerOffline      ( ROLE_ID );                                            // 用户离线事件;
    void CallBackAddItem            ( ROLE_ID , ITEM_ID , uint32 , uint32 , PB_DotItem );   // 用户添加道具;
    void CallBackSubItem            ( ROLE_ID , ITEM_ID , uint32 , uint32 , PB_DotItem );   // 用户扣减道具;
};

#define EventDotCallBack CEventDotCallBack::getInstance()

GSE_NAMESPACE_END_DECL

#endif//GSE_EVENT_DOT_CALLBACK_H_