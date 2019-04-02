#ifndef GSE_EVENT_STATISTICS_CALLBACK_H_
#define GSE_EVENT_STATISTICS_CALLBACK_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CEventStatisticsCallBack : public sigslot::has_slots<> , public NLMISC::CSingleton< CEventStatisticsCallBack >
{
public:
    void InitEventCallBack( void );
private:
    
};

#define EventStatisticsCallBack CEventStatisticsCallBack::getInstance()

GSE_NAMESPACE_END_DECL

#endif//GSE_EVENT_STATISTICS_CALLBACK_H_