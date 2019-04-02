#ifndef PSE_LOGINUSER_H_
#define PSE_LOGINUSER_H_

#include <persistent_service/persistent_service/persistent_service_def.h>

PSE_NAMESPACE_BEGIN_DECL

class CLoginUser : public NLMISC::CSingleton< CLoginUser >
{
public:
    CLoginUser( void ){ };
   ~CLoginUser( void ){ };

    //   ÓÃ»§µÇÂ¼;
    void UserLoginCallBack( PB_UserLogin& );
};

#define LoginUser CLoginUser::instance()

PSE_NAMESPACE_END_DECL

#endif //PSE_LOGINUSER_H_