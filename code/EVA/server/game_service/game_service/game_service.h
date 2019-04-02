#ifndef GSE_SERVICE_H_
#define GSE_SERVICE_H_

#include "game_service_def.h"

class CGameService : public NLNET::IService
{
public:
    CGameService( void ) { };
    virtual ~CGameService( void ) { };

     void init      ( void );
     bool update    ( void );
     void release   ( void );
};


#endif //GSE_SERVICE_H_

