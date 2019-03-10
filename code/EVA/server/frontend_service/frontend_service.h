#ifndef FRONTEND_SERVICE_SERVICE_H_
#define FRONTEND_SERVICE_SERVICE_H_

#include "frontend_def.h"

using namespace SS;

class CFrontEndService : public NLNET::IService
{
public:
    CFrontEndService(){ };
    virtual ~CFrontEndService( void ) { }

    //   init;
    void init   ( void );
    //   update;
    bool update ( void );
    //   releaes;
    void release( void );

private:
    std::vector< NLMISC::CSString > m_WaitServiceAccess;

};

#endif // FRONTEND_SERVICE_SERVICE_H_
