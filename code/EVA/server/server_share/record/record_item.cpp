#include "record_item.h"

SS_NAMESPACE_BEGIN_DECL

CRecordItem::CRecordItem( void ) : m_RoleID( 0 )
                                 , m_ItemID( 0 )
                                 , m_ItemCount( 0 )
                                 , m_LastTime( NLMISC::CTime::getSecondsSince1970() )
{
    
}

CRecordItem::~CRecordItem( void )
{
    
}

SS_NAMESPACE_END_DECL


