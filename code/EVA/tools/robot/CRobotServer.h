#ifndef CRobotServer_h__
#define CRobotServer_h__

#include "nel/misc/types_nl.h"
#include "nel/net/service.h"

class CRobotServer : public NLNET::IService
{
public:
    CRobotServer( void );
   ~CRobotServer( void );

    void init();

    bool update();

    void release();

};

#endif // CRobotServer_h__