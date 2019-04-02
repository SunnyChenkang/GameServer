#ifndef WSE_SERVICE_H_
#define WSE_SERVICE_H_

#include "web_service_def.h"

class CWebService : public NLNET::IService
{
public:
    CWebService( void ) { };
    virtual ~CWebService( void ) { };

    //   init;
    void init   ( void );
    //   update;
    bool update ( void );
    //   release;
    void release( void );
};

#endif // WSE_SERVICE_H_;