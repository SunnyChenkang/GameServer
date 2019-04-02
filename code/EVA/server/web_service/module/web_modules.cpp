#include <web_service/web_service/web_service_def.h>
#include <nel/net/module_builder_parts.h>
#include <nel/net/module.h>
#include "web_modules_itf.h"

using namespace WSE;
using namespace NLNET;
using namespace NLMISC;

class CWebModules : public CEmptyModuleServiceBehav< CEmptyModuleCommBehav<CEmptySocketBehav< CModuleBase > > >
                  , CWebModulesItf
                  , IModuleTrackerCb

{
public:
    bool initModule( const TParsedCommandLine& Commandline )
    {
        CModuleBase::initModule( Commandline );
        // read web port;
        const TParsedCommandLine* pCommandLine = Commandline.getParam("webPort");
        nlassert( pCommandLine != NULL );
        uint16 WebPort = 0;
        fromString( pCommandLine->ParamValue , WebPort );
        CWebModulesItf::WebModulesInit( WebPort );
        return true;
    }

    void onModuleUpdate( void )
    {
        CWebModulesItf::WebModulesUpdate();
    }

    virtual void onTrackedModuleUp( IModuleProxy* pModuleProxy )
    {
        nldebug( " WebModule %s UP" , pModuleProxy->getModuleName().c_str() );
    }
    virtual void onTrackedModuleDown( IModuleProxy* pModuleProxy )
    {
        nldebug( "WebModule %s DOWN " , pModuleProxy->getModuleName().c_str() );
    }

    virtual void CallBackWebTest( )
    {
        
    }
};

NLNET_REGISTER_MODULE_FACTORY( CWebModules, "WebModules" );
