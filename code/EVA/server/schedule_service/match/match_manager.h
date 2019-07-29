#ifndef SSE_MATCH_MANAGER_H_
#define SSE_MATCH_MANAGER_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

class CMatchManager : public CSingleton< CMatchManager >
{
public:
    CMatchManager( void );
   ~CMatchManager( void );

    ///  ÃÌº”∆•≈‰∂”¡–;
    bool PushMatchList( ROLE_ID );
};

#define MatchManager CMatchManager::getInstance()

SSE_NAMESPACE_END_DECL

#endif//SSE_MATCH_MANAGER_H_