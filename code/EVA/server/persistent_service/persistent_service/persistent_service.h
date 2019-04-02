#ifndef PSE_SERVICE_H_
#define PSE_SERVICE_H_

#include "persistent_service_def.h"

class CPersistentService : public NLNET::IService
{
public:
    CPersistentService( void ) { };
    virtual ~CPersistentService( void ) { }

    //   init;
    void init   ( void );
    //   update;
    bool update ( void );
    //   release;
    void release( void );
};

#endif // PSE_SERVICE_H_;