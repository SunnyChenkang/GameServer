#ifndef SS_JSON_CREATEROLE_H_
#define SS_JSON_CREATEROLE_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

class CAddItemCell : public CJsonBase
{
    SS_PROPERTY( ITEM_ID            , ItemID    , private );
    SS_PROPERTY( uint32             , ItemCount , private );

    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin ( JsonValue );
        JsonParseToUInt( m_ItemID  );
        JsonParseToUInt( m_ItemCount );
        JsonParseEnd();
    }
};

class CCreateRoleConfig : public CJsonBase
{
    SS_PROPERTY( CJsonArray< CAddItemCell > , AddItem , public  );
    SS_PROPERTY( NLMISC::CSString           , NickName, private );
    SS_PROPERTY( uint32                     , HeadID  , private );

    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin   ( JsonValue );
        JsonParseBegin   ( Values );
        JsonParseToClass ( m_AddItem );
        JsonParseToString( m_NickName);
        JsonParseToUInt  ( m_HeadID  );
        JsonParseEnd();
        JsonParseEnd();
    }
};

SS_NAMESPACE_END_DECL

#endif//SS_JSON_CREATEROLE_H_