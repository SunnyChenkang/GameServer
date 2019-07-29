#include "match_mode.h"

SSE_NAMESPACE_BEGIN_DECL

NL_BEGIN_STRING_CONVERSION_TABLE( TMatchMode   )
NL_STRING_CONVERSION_TABLE_ENTRY( Match_None   )
NL_STRING_CONVERSION_TABLE_ENTRY( Match_Normal )
NL_STRING_CONVERSION_TABLE_ENTRY( Match_Robot  )
NL_END_STRING_CONVERSION_TABLE  ( TMatchMode , MatchModeConversion , Unknown );

/// string to enum;
TMatchMode     ToEnum( const CSString& str )    { return MatchModeConversion.fromString( str );     }
/// enum to string;
const CSString ToString( TMatchMode MatchMode ) { return MatchModeConversion.toString( MatchMode ); }

SSE_NAMESPACE_END_DECL