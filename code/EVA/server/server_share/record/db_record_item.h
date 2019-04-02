#ifndef SERVER_SHARED_RECORDITEM_H_
#define SERVER_SHARED_RECORDITEM_H_

#include "db_record_base.h"

SS_NAMESPACE_BEGIN_DECL

class CRecordItem : public CRecordBase
{
public:
    CRecordItem( void );
    virtual ~CRecordItem( void );

    // serial stream;
    void serial( NLMISC::IStream& s )
    {
        s.serial( m_DBState );
        s.serial( m_RoleID );
        s.serial( m_ItemID );
        s.serial( m_ItemCount );
        s.serial( m_LastTime );
    }

    // serial database;
    void SaveToDataBase( void )
    {
        CRecordItem& RecordItem( *this );
        NLNET::CMessage SendMessage("MSG_DB_ITEM");
        SendMessage.serial( RecordItem );
        SS_NETWORK->send( "PSE" , SendMessage );
    }

    // operator += ;
    CRecordItem& operator += ( const CRecordItem& rhs )
    {
        this->m_ItemCount += rhs.m_ItemCount;
        return *this;
    }

    SS_PROPERTY( ROLE_ID , RoleID       , private );
    SS_PROPERTY( ITEM_ID , ItemID       , private );
    SS_PROPERTY( uint32  , ItemCount    , private );
    SS_PROPERTY( uint32  , LastTime     , private );
};

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_RECORDITEM_H_