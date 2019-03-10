#ifndef CCommonLine_h__
#define CCommonLine_h__

#include <nel/misc/sstring.h>
#include <nel/misc/random.h>
#include <queue>


class CCommonLine
{
private:
    struct LoginData
    {
        std::string  username;
    };

public:
    CCommonLine( void );
   ~CCommonLine( void );

    // 解析命令行;
    void AnalysisCommonLine( const NLMISC::CVectorSString& );

    // 登陆客户端;
    void AutoLoginClient( std::string name );

    void Update();

    // 服务器地址;
    std::string& GetServerHost( void ) {
        return m_Host;
    }

    // 服务器端口;
    short GetServerPort( void ) {
        return m_Port;
    }

    // 获取URL地址;
    std::string& GetLoginUrl( void ){
        return m_Url;
    }

    static CCommonLine* GetInstance( void )
    {
        static CCommonLine _inst;
        return &( _inst );
    }

    void PushLoginAccount( std::string strUserName );
         
public:
    uint32                 m_RobotUID;
    NLMISC::CRandom        m_Random;

private:
    std::string m_Host;
    std::string m_Url;
    short       m_Port;

    typedef std::queue<LoginData> TLoginData;
    TLoginData  m_LoginData;

private:
    CCommonLine( const CCommonLine& rhs );
    CCommonLine & operator = ( const CCommonLine& rhs );
};

#define CommonLine CCommonLine::GetInstance()

#endif // CCommonLine_h__