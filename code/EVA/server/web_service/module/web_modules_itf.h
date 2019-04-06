#ifndef WSE_WEBMODULES_ITF_H_
#define WSE_WEBMODULES_ITF_H_

#include <web_service/web_service/web_service_def.h>
#include <memory>

WSE_NAMESPACE_BEGIN_DECL

class CWebModulesItf
{
protected:

    // the callback server adaptor;
    std::auto_ptr< ICallbackServerAdaptor > _CallBackService;

    void GetCallBackArray( NLNET::TCallbackItem *&ArrayPtr , uint32& ArraySize )
    {
        static NLNET::TCallbackItem CallBackArray[] = 
        {
            { "WEB_TESTR" , CWebModulesItf::CallBackWebTest },
        };

        ArrayPtr    = CallBackArray;
        ArraySize   = SS_ARRAYSIZE( CallBackArray );
    }

    // web connection;
    static void CallBackWebConnection( NLNET::TSockId from , void* args )
    {
        H_AUTO( CWebModulesItf_Connection );
        CWebModulesItf* pWebItf = reinterpret_cast< CWebModulesItf* >( args );
    }

    // web disconnection;
    static void CallBackWebDisConnection( NLNET::TSockId from , void* args )
    {
        H_AUTO( CWebModulesItf_DisConnection );
        CWebModulesItf* pWebItf = reinterpret_cast< CWebModulesItf* >( args );
    }

public:
    CWebModulesItf( ICallbackServerAdaptor* pServiceAdaptor = NULL )
    {
        if ( pServiceAdaptor == NULL ) {
            _CallBackService = std::auto_ptr< ICallbackServerAdaptor >( new CNelCallbackServerAdaptor( this ) );
        }
        else {
            _CallBackService = std::auto_ptr< ICallbackServerAdaptor >( pServiceAdaptor );
        }
    }

    void WebModulesInit( uint32 Port )
    {
        H_AUTO( CWebModulesItf_WebModulesInit );

        NLNET::TCallbackItem* CallBackItem;
        uint32 CallBackSize;
        GetCallBackArray( CallBackItem , CallBackSize );
        _CallBackService->setConnectionCallback( CallBackWebConnection , this );
        _CallBackService->setDisconnectionCallback( CallBackWebDisConnection , this );
        _CallBackService->addCallbackArray( CallBackItem , CallBackSize );
        _CallBackService->init( Port );
    }

    void WebModulesUpdate( void )
    {
        H_AUTO( CWebModulesItf_WebModulesUpdate );

        try {
            _CallBackService->update();
        }
        catch( ... ) {
            nlwarning( "CWebModules: Exception launch in callback service update" );
        }
    }

    static void CallBackWebTest( NLNET::CMessage& message , NLNET::TSockId from , NLNET::CCallbackNetBase &netbase )
    {
        H_AUTO( CWebModuesIft_CallBackWebTest );

        #ifdef NL_DEBUG
        nldebug( "CWebModulesItf::CallBackWebTest Received from class %s " , typeid(netbase).name() );
        #endif

        ICallbackServerAdaptor* pServiceAdaptor = static_cast< ICallbackServerAdaptor* >( netbase.getUserData() );
        CWebModulesItf* pCallBack = ( CWebModulesItf* )pServiceAdaptor->getContainerClass();

        std::string test1;
        uint32      test2;
        nlRead( message , serial , test1 );
        nlRead( message , serial , test2 );

        // µ÷ÓÃfunc;
        pCallBack->CallBackWebTest();
    }

    virtual void CallBackWebTest( void ) = 0;
};

WSE_NAMESPACE_END_DECL

#endif//WSE_WEBMODULES_ITF_H_