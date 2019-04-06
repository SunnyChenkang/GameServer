#ifndef SS_UUID_H_
#define SS_UUID_H_

#include <server_share/common/common.h>

#ifdef NL_OS_UNIX
#include <uuid/uuid.h>
#endif

#ifdef NL_OS_WINDOWS
#include <objbase.h>
#endif

SS_NAMESPACE_BEGIN_DECL

NLMISC::CSString AllocGUID( void );

SS_NAMESPACE_END_DECL

#endif//SS_UUID_H_