#include "frontend_def.h"

FES_NAMESPACE_BEGIN_DECL

NL_BEGIN_STRING_CONVERSION_TABLE( EFormatKind )
NL_STRING_CONVERSION_TABLE_ENTRY( ROLEID )
NL_END_STRING_CONVERSION_TABLE  ( EFormatKind, FormatConversion , INVALID )

EFormatKind ToForMatEnum(const string& Param)
{
    return FormatConversion.fromString( Param );
}

const std::string& ToForMatString( EFormatKind Format )
{
    return FormatConversion.toString( Format );
}

FES_NAMESPACE_END_DECL

 