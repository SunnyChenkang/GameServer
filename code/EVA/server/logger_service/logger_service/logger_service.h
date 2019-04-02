#include "logger_service_def.h"

LSE_NAMESPACE_BEGIN_DECL

class CLoggerService : public NLNET::IService
{
public:
    //   init;
    void init( void );
    //   update;
    bool update( void );
    //   release;
    void release( void );
};

LSE_NAMESPACE_END_DECL