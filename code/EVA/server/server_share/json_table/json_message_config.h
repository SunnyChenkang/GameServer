#ifndef SS_JSON_MESSAGE_CONFIG_H_
#define SS_JSON_MESSAGE_CONFIG_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

class CJsonMessageCell : public CJsonBase
{
    SS_PROPERTY( NLMISC::CSString               , Name          , private );
    SS_PROPERTY( NLMISC::CSString               , Desc          , private );
    SS_PROPERTY( CJsonArray<NLMISC::CSString>   , Format        , public  );
    SS_PROPERTY( CJsonArray<NLMISC::CSString>   , SendToService , public  );

    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin   ( JsonValue );
        JsonParseToString( m_Name );
        JsonParseToString( m_Desc );
        JsonParseToClass ( m_Format );
        JsonParseToClass ( m_SendToService );
        JsonParseEnd();
    }
};

class CJsonMessageConfig : public CJsonBase
{
    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin( JsonValue );
        CJsonMessageCell* pCell = new CJsonMessageCell();
        pCell->ParseJson( Values );
        m_JsonStringArray.insert(std::make_pair( pCell->GetName() , pCell ) );
        JsonParseEnd();
    }
};

SS_NAMESPACE_END_DECL

#endif // SS_JSON_FES_MESSAGE_H_;