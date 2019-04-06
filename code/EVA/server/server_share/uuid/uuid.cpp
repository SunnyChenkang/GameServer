#include "uuid.h"

SS_NAMESPACE_BEGIN_DECL

#ifdef NL_OS_WINDOWS
NLMISC::CSString AllocGUID( void )
{
    GUID id;
    CoCreateGuid( &id );

    char one[10]    = { '\0' };
    char two[6]     = { '\0' };
    char three[6]   = { '\0' };
    char four[6]    = { '\0' };
    char five[14]   = { '\0' };

    NLMISC::smprintf( one , SS_ARRAYSIZE( one ) , "%02x%02x%02x%02x"            , (unsigned char)( (id.Data1 >> 24) & 0xFF ) 
                                                                                , (unsigned char)( (id.Data1 >> 16) & 0xFF )
                                                                                , (unsigned char)( (id.Data1 >> 8 ) & 0xFF )
                                                                                , (unsigned char)( (id.Data1 )      & 0xFF ) );

    NLMISC::smprintf( two , SS_ARRAYSIZE( two ) , "%02x%02x"                    , (unsigned char)( (id.Data2 >> 8 ) & 0xFF )
                                                                                , (unsigned char)( (id.Data2 )      & 0xFF ) );

    NLMISC::smprintf( three , SS_ARRAYSIZE( three ) , "%02x%02x"                , (unsigned char)( (id.Data3 >> 8 ) & 0xFF )
                                                                                , (unsigned char)( (id.Data3 )      & 0xFF ) );

    NLMISC::smprintf( four , SS_ARRAYSIZE( four ) , "%02x%02x"                  , (unsigned char)id.Data4[0] 
                                                                                , (unsigned char)id.Data4[1] );

    NLMISC::smprintf( five , SS_ARRAYSIZE( five ) , "%02x%02x%02x%02x%02x%02x"  , (unsigned char)id.Data4[2]
                                                                                , (unsigned char)id.Data4[3]
                                                                                , (unsigned char)id.Data4[4]
                                                                                , (unsigned char)id.Data4[5]
                                                                                , (unsigned char)id.Data4[6]
                                                                                , (unsigned char)id.Data4[7] );

    NLMISC::CSString StrUUID = "";
    StrUUID = StrUUID + one     + "-";
    StrUUID = StrUUID + two     + "-";
    StrUUID = StrUUID + three   + "-";
    StrUUID = StrUUID + four    + "-";
    StrUUID = StrUUID + five;
    return StrUUID;
}
#else
NLMISC::CSString AllocGUID( void )
{
    uuid_t uu;
    uuid_generate( uu );

    char one[10]    = { '\0' };
    char two[6]     = { '\0' };
    char three[6]   = { '\0' };
    char four[6]    = { '\0' };
    char five[14]   = { '\0' };

    NLMISC::smprintf( one  , SS_ARRAYSIZE(one)     , "%02x%02x%02x%02x"        , uu[0]  , uu[1] , uu[2] , uu[3] );
    NLMISC::smprintf( two  , SS_ARRAYSIZE(two)     , "%02x%02x"                , uu[4]  , uu[5] );
    NLMISC::smprintf( three, SS_ARRAYSIZE(three)   , "%02x%02x"                , uu[6]  , uu[7] );
    NLMISC::smprintf( four , SS_ARRAYSIZE(four)    , "%02x%02x"                , uu[8]  , uu[9] );
    NLMISC::smprintf( five , SS_ARRAYSIZE(five)    , "%02x%02x%02x%02x%02x%02x", uu[10] , uu[11] , uu[12] , uu[13] , uu[14] , uu[15] );

    NLMISC::CSString StrUUID = "";
    StrUUID = StrUUID + one     + "-";
    StrUUID = StrUUID + two     + "-";
    StrUUID = StrUUID + three   + "-";
    StrUUID = StrUUID + four    + "-";
    StrUUID = StrUUID + five;
    return StrUUID;
}
#endif


SS_NAMESPACE_END_DECL