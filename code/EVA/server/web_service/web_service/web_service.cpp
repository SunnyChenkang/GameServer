#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "web_service.h"

#ifdef NL_OS_WINDOWS
#include <Windows.h>
#endif

using namespace NLMISC;
using namespace NLNET;
using namespace WSE;

// admin modules;
extern void admin_modules_forceLink();
void foo()
{
    admin_modules_forceLink();
}

void CWebService::init()
{
    
}

bool CWebService::update( void )
{
    return true;
}

void CWebService::release( void )
{
    
}

NLNET_SERVICE_MAIN( CWebService, "WSE", "web_service", 0 , "", "")