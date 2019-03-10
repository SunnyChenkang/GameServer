#ifndef SSE_SERVICE_H_
#define SSE_SERVICE_H_

#include "schedule_def.h"

class CScheduleService : public NLNET::IService
{
public:
    CScheduleService( void ) { };
    virtual ~CScheduleService( void ) { }

    //   init;
    void init   ( void );
    //   update;
    bool update ( void );
    //   release;
    void release( void );
};

#endif // SSE_SERVICE_H_;