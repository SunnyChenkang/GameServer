#ifndef FRONTEND_SERVICE_CLIENT_FUNCTOR_H_
#define FRONTEND_SERVICE_CLIENT_FUNCTOR_H_

#include "frontend_def.h"

FES_NAMESPACE_BEGIN_DECL

// 检查连接超时客户端;
class ScanConnectionTimeOutClient
{
    template< typename T > void operator() ( T& rhs )
    {
        
    }
};

FES_NAMESPACE_END_DECL

#endif // FRONTEND_SERVICE_CLIENT_FUNCTOR_H_;