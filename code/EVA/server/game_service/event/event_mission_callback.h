#ifndef GSE_EVENT_MISSION_CALLBACK_H_
#define GSE_EVENT_MISSION_CALLBACK_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CEventMissionCallBack : public sigslot::has_slots<> , public NLMISC::CSingleton< CEventMissionCallBack >
{
public:
    void InitEventCallBack( void );
};

#define EventMissionCallBack CEventMissionCallBack::getInstance()

GSE_NAMESPACE_END_DECL

#endif//GSE_EVENT_MISSION_CALLBACK_H_