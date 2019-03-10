#ifndef SS_JSON_FES_MESSAGE_H_
#define SS_JSON_FES_MESSAGE_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

class CJsonFesMessageCell : public CJsonBase
{
public:
    CJsonFesMessageCell( void ) { };
    virtual ~CJsonFesMessageCell( void ){ };

    SS_PROPERTY( NLMISC::CSString               , Name          , private );
    SS_PROPERTY( NLMISC::CSString               , Desc          , private );
    SS_PROPERTY( CJsonArray<NLMISC::CSString>   , Format        , private );
    SS_PROPERTY( CJsonArray<NLMISC::CSString>   , SendToService , private );

    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin   ( JsonValue );
        JsonParseToString( m_Name );
        JsonParseToString( m_Desc );
        JsonParseToClass ( m_Format );
        JsonParseToClass ( m_SendToService );
        JsonParseEnd     ( );
    }
};

class CJsonFesMessage : public CJsonBase
{
public:
    CJsonFesMessage( void ) { };
    virtual ~CJsonFesMessage( void ) { };

    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin( JsonValue );
        CJsonFesMessageCell* pCell = new CJsonFesMessageCell();
        pCell->ParseJson( it->value );
        m_JsonStringTable.insert(std::make_pair( pCell->GetName() , pCell ) );
        JsonParseEnd( );
    }
};

SS_NAMESPACE_END_DECL

#endif // SS_JSON_FES_MESSAGE_H_;