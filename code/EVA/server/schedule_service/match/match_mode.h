#ifndef SSE_MATCH_MODE_H_
#define SSE_MATCH_MODE_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

enum TMatchMode
{
    Match_None   = 0,
    Match_Normal = 1,
    Match_Robot  = 2,
    Unknown,
    Match_Bits   = Unknown,
};

TMatchMode ToEnum( const CSString& str );
const CSString ToString( TMatchMode );

SSE_NAMESPACE_END_DECL

#endif//SSE_MATCH_MODE_H_