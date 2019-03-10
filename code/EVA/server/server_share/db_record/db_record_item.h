#ifndef SERVER_SHARED_RECORDITEM_H_
#define SERVER_SHARED_RECORDITEM_H_

#include "db_record_base.h"

SS_NAMESPACE_BEGIN_DECL

class CRecordItem : public CRecordBase
{
public:
    CRecordItem( void );
    virtual ~CRecordItem( void );;

    // serial;
    void serial( NLMISC::IStream& s )
    {
        s.serial( m_RoleID );
        s.serial( m_ItemID );
        s.serial( m_ItemNumber );
    }

    SS_PROPERTY( ROLE_ID , RoleID       , private );
    SS_PROPERTY( ITEM_ID , ItemID       , private );
    SS_PROPERTY( uint32  , ItemNumber   , private );
};

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_RECORDITEM_H_