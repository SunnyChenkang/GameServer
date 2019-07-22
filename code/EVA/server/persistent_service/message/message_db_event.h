#ifndef PSE_MESSAGE_DB_EVENT_H_
#define PSE_MESSAGE_DB_EVENT_H_

#include <persistent_service/persistent_service/persistent_service_def.h>

PSE_NAMESPACE_BEGIN_DECL

// 更新角色数据;
void CallBack_Player( NLNET::CMessage&, const std::string&, NLNET::TServiceId );
// 更新道具数据;
void CallBack_Item( NLNET::CMessage&, const std::string&, NLNET::TServiceId  );
// 更新统计数据;
void CallBack_Statistics( NLNET::CMessage& , const std::string& , NLNET::TServiceId );
// 更新任务数据;
void CallBack_Mission( NLNET::CMessage& , const std::string& , NLNET::TServiceId );

// 注册消息;
static NLNET::TUnifiedCallbackItem PSE_DB_CallBackItems[] =
{
    { "MSG_DB_PLAYER"       ,         CallBack_Player         },
    { "MSG_DB_ITEM"         ,         CallBack_Item           },
    { "MSG_DB_STATISTICS"   ,         CallBack_Statistics     },
    { "MSG_DB_MISSION"      ,         CallBack_Mission        },
};

PSE_NAMESPACE_END_DECL

#endif //PSE_MESSAGE_DB_EVENT_H_