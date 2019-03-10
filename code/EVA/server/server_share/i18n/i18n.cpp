#include "i18n.h"
#include "nel/misc/i18n.h"

SS::CI18n::CI18n( void ) : m_Content( "" )
                         , m_Format ( "" )
{

}

const char* SS::CI18n::GetString( const char* Label )
{
    m_Content = NLMISC::CI18N::get( Label ).toUtf8();
    return m_Content.c_str();
}

NLMISC::CSString SS::CI18n::Format( const char* format , ... )
{
    m_Format.clear();
    NLMISC_CONVERT_VARGS( m_Format , format , NLMISC::MaxCStringSize );
    return m_Format;
}
