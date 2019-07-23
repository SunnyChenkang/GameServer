#ifndef SSE_USER_LOGIN_H_
#define SSE_USER_LOGIN_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

class CLoginUser : public NLMISC::CSingleton< CLoginUser >
{
public:
    CLoginUser( void ){ }
   ~CLoginUser( void ){ }

    ///  用户登录;
    void CallBackPlayerLogin( NLNET::CMessage& );
    ///  用户登录成功;
    void CallBackPlayerLoginFinish( NLNET::CMessage& );
    ///  玩家切换场景;
    void CallBackChangeScenes( NLNET::CMessage& );
};

#define LoginUser CLoginUser::instance()

SSE_NAMESPACE_END_DECL

#endif //SSE_USER_LOGIN_H_;