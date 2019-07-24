#ifndef SS_JSON_ITEM_CONFIG_H_
#define SS_JSON_ITEM_CONFIG_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

class CJsonItemCell;
typedef std::shared_ptr< CJsonItemCell > CJsonItemCellPtr;

/// 道具属性;
class CJsonItemCell : public CJsonBase
{
    SS_PROPERTY( ITEM_ID            , ItemID    , private );    // 道具ID;
    SS_PROPERTY( uint32             , ItemKind  , private );    // 道具种类;
    SS_PROPERTY( NLMISC::CSString   , ItemName  , private );    // 道具名字;
    SS_PROPERTY( NLMISC::CSString   , ItemIcon  , private );    // 道具图标;

    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin   ( JsonValue );
        JsonParseToUInt  ( m_ItemID );
        JsonParseToString( m_ItemName );
        JsonParseToUInt  ( m_ItemKind  );
        JsonParseToString( m_ItemIcon  );
        JsonParseEnd();
    }
};

class CJsonItemConfig : public CJsonBase
{
    void ParseJsonArray( const GenericValue< UTF8<> >& JsonValue )
    {
        JsonParseArrayBegin( JsonValue );
        CJsonItemCellPtr ItemCellPtr = std::make_shared< CJsonItemCell >();
        ItemCellPtr->ParseJson( Values );
        m_JsonUint32Array.insert(std::make_pair( ItemCellPtr->GetItemID() , ItemCellPtr ) );
        JsonParseArrayEnd();
    }
};

SS_NAMESPACE_END_DECL

#endif//SS_JSON_ITEM_CONFIG_H_