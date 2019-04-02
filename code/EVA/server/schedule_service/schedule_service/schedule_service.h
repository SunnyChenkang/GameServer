#ifndef SSE_SERVICE_H_
#define SSE_SERVICE_H_

#include "schedule_service_def.h"

class CScheduleService : public NLNET::IService
{
public:
    CScheduleService( void ) { };
    virtual ~CScheduleService( void ) { }

    void init   ( void );
    bool update ( void );
    void release( void );
};

#endif // SSE_SERVICE_H_;