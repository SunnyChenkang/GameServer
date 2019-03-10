#include "CCommonLine.h"
#include "http/http_client.h"
#include "http/http_client_curl.h"
#include <nel/misc/sstring.h>
#include <nel/net/service.h>
#include "msg/send_logic.h"
#include <server_share/server_def.h>
#include "CClient.h"
#include "CClientMgr.h"

using namespace NLNET;
using namespace NLMISC;

NLMISC::CVariable<std::string>	VAR_CONNECT_HOST("robot", "ConnectHost"  , "memo", "");

CCommonLine::CCommonLine( void )
{
    m_Host = "";
    m_Url  = "";
    m_Port = 0;
    m_RobotUID = -1;
    m_Random.srand(NLMISC::CTime::getSecondsSince1970());
}

CCommonLine::~CCommonLine( void )
{

}

void CCommonLine::AnalysisCommonLine( const NLMISC::CVectorSString& CmdLine  )
{
    // 解析HTTP地址;
    m_Url = Config.getVar( "LoginUrl" ).asString ();
    // 解析服务器地址;
    m_Host = Config.getVar( "DefaultHost" ).asString();
    // 解析服务器端口;
    m_Port = Config.getVar( "DefaultPort" ).asInt();

    if( !CurlHttpClient.connect( m_Url )  )
    {
        nlwarning( " connect http faile; " );
        return;
    }

    VAR_CONNECT_HOST = m_Host;

    //uint nMinAcc = 0;
    //uint nMaxAcc = 0;

    //if( CmdLine.size() < 2 )
    //{
    //    std::string LoginAcc = Config.getVar( "DefaultAcc" ).asString();
    //    std::string LoginPwd = Config.getVar( "DefaultPort" ).asString();

    //    NLMISC::CSString SplitString( LoginAcc );
    //    NLMISC::CVectorSString SplitVector;
    //    SplitString.splitBySeparator(',' , SplitVector );
    //    if ( SplitVector.size() < 2 ) {
    //        return;
    //    }
    //    NLMISC::CSString StrMinAcc = SplitVector[ 0 ].leftCrop( 4 );
    //    NLMISC::CSString StrMaxAcc = SplitVector[ 1 ].leftCrop( 4 );

    //    nMinAcc = StrMinAcc.atoui();
    //    nMaxAcc = StrMaxAcc.atoui();
    //}
    //else if ( CmdLine.size() == 3 )
    //{
    //    CSString strParam1 = CmdLine[ 1 ];
    //    CSString strParam2 = CmdLine[ 2 ];

    //    if ( strParam1.empty() ||
    //         strParam2.empty() ) 
    //    {
    //        nlwarning( " common line param is null !!~ " );
    //        return;
    //    }

    //    if ( strParam1.atoi() > strParam2.atoi() ) 
    //    {
    //        nlwarning( " common line param input error ~~~! " );
    //        return;
    //    }

    //    nMinAcc = strParam1.atoi();
    //    nMaxAcc = strParam2.atoi();
    //}

    //LoginData login_data;

    //for ( int i = nMinAcc  ; i <= nMaxAcc ; ++i )
    //{
    //    char buff[128] = {'\0'};
    //    smprintf( buff , sizeof( buff ) , "test%d" , i );

    //    login_data.username = buff;
    //    login_data.password = "123456";
    //    m_LoginData.push( login_data );

    //    //AutoLoginClient( buff , "123456" );
    //}

    nlinfo("User Login Start.");
}

void CCommonLine::AutoLoginClient( std::string name )
{
    std::string Post = "cmd=login";

    Post.append( "&usr=" );
    Post.append( name );
    Post.append( "&deviceid=0" );
    Post.append( "&self_channel=2" );
    Post.append("&app_name=CPB");
    Post.append("&login_type=0");
    Post.append("&login_token=0");
    Post.append("&time=0");
    Post.append("&sig=0");

    nlinfo( " start auth account [%s] " , name.c_str() );

    // send;
    while ( !CurlHttpClient.sendPost( m_Url , Post ) )
    {
        nlwarning( " send http message faile" );
    }

    // recv;
    std::string RecvPack ;
    if ( !CurlHttpClient.receive( RecvPack ) ) 
    {
        nlwarning( " recvive http message faile; " );
        return;
    }

    //CurlHttpClient.disconnect();

    // analysis;
    CSString result( RecvPack );
    CVectorSString Analysis;
    result.splitLines( Analysis );

    if ( Analysis.size()<8 )
    {
        return;
    }

    CSString AuthResult = Analysis[ Analysis.size()-1 ];
//     if ( AuthResult.size() != ( 6 + 16 ) )
//         return;

    CSString opt = AuthResult.substr( 0, 6 );
    CSString val = AuthResult.substr( 6, AuthResult.size()-1 );

    if ( opt != "token:")
        return;

    CClient* pClient = ClientMgr->AllocClient();
    if ( NULL == pClient )
        return;

    pClient->SetClientState( client_state_login );
    pClient->GetSendLogic()->SendLogin( val );
    nlinfo( " send login msg %s " , val.c_str() );
}

void CCommonLine::Update()
{
    uint i=0;

    while ( !m_LoginData.empty() && i<1 )
    {
        AutoLoginClient( m_LoginData.front().username );
        m_LoginData.pop();
        ++i;
    }
}

void CCommonLine::PushLoginAccount( std::string strUserName )
{
    LoginData login_data;

    login_data.username = strUserName;
    m_LoginData.push( login_data );
}

