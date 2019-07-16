#ifndef SSE_USER_LOGIN_H_
#define SSE_USER_LOGIN_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

class CLoginUser : public NLMISC::CSingleton< CLoginUser >
{
public:
    CLoginUser( void ){ }
   ~CLoginUser( void ){ }

    //   用户登录;
    void CallBackUserLogin( NLNET::CMessage& );
    //   用户登录成功;
    void CallBackUserLoginSucceed( NLNET::CMessage& );

private:
    //   用户内存登录;
    bool UserLoginMemory( PB_UserLogin& );
    //   用户数据库登录;
    bool UserLoginDBCache( PB_UserLogin& );
};

#define LoginUser CLoginUser::instance()

SSE_NAMESPACE_END_DECL

#endif //SSE_USER_LOGIN_H_;