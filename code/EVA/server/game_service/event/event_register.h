#ifndef GSE_EVENT_REGISTER_H_
#define GSE_EVENT_REGISTER_H_

#include <server_share/common/common.h>

GSE_NAMESPACE_BEGIN_DECL

class CEventRegister : public NLMISC::CSingleton< CEventRegister >
{
public:
    CEventRegister( void );
   ~CEventRegister( void );
};

#define EventRegister CEventRegister::instance()

GSE_NAMESPACE_END_DECL

#endif // GSE_EVENT_REGISTER_H_