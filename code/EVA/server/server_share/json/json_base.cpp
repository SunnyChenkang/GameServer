#include "json_base.h"

SS_NAMESPACE_BEGIN_DECL

NLMISC::CSString CJsonBase::ToJson( void )
{
    StringBuffer s;
    Writer< StringBuffer > writer( s );
    this->WriterJson( writer );
    return s.GetString();
}

void CJsonBase::FromJson( CJsonBase* pJsonBase , const NLMISC::CSString& JsonData )
{
    try {
    Document DocJson;
    DocJson.Parse( JsonData.data() );
    if ( DocJson.IsArray() )
    {
        GenericValue< UTF8< char > >::Array JsonArray( DocJson.GetArray() );
        pJsonBase->ParseJsonArray( JsonArray );
    }
    else
    {
        const Value& val = DocJson;
        pJsonBase->ParseJson( val );
    } }
    catch ( ... )
    {
        nlinfo( " parse json faile !!! " );
    }
}

void CJsonBase::LoadJson( NLMISC::CSString FileName )
{
    ClearJson();

    NLMISC::CSString FilePath = NLMISC::CPath::lookup( FileName );
    if ( FilePath.empty() ) return;

    NLMISC::CIFile   JsonFile;
    NLMISC::CSString JsonDesc;
    NLMISC::CSString JsonLine;

    if ( !JsonFile.open( FilePath ) )
    {
        nlinfo( " open file failes~ [%s]" , FilePath.c_str() );
        return;
    }
    while ( !JsonFile.eof() )
    {
        char StrBuffer[1024] = { '\0' };
        JsonFile.getline( StrBuffer , sizeof( StrBuffer ) );
        JsonLine = StrBuffer;
        JsonDesc.append( JsonLine + '\n');
    }
    JsonFile.close();
    FromJson( this , JsonDesc );
}

void CJsonBase::ToWriterJson( Writer<StringBuffer>& writer , sint32& val )
{
    writer.Int( val );
}

void CJsonBase::ToWriterJson( Writer< StringBuffer >& writer , sint64& val )
{
    writer.Int64( val );
}

void CJsonBase::ToWriterJson( Writer< StringBuffer >& writer , uint32& val )
{
    writer.Uint( val );
}

void CJsonBase::ToWriterJson( Writer< StringBuffer >& writer , uint64& val )
{
    writer.Uint64( val );
}

void CJsonBase::ToWriterJson( Writer< StringBuffer >& writer , double& val )
{
    writer.Double( val );
}

void CJsonBase::ToWriterJson( Writer< StringBuffer >& writer , bool& val )
{
    writer.Bool( val );
}

void CJsonBase::ToWriterJson( Writer< StringBuffer >& writer , NLMISC::CSString& val )
{
    writer.String( val.data() );
}

void CJsonBase::ToWriterJson( Writer< StringBuffer >& writer , char* val )
{
    writer.String( val , strlen( val ) );
}


void CJsonBase::ToParseJson( const Value& value , sint32& t )
{
    t = value.GetInt();
}

void CJsonBase::ToParseJson( const Value& value , sint64& t )
{
    t = value.GetInt64();
}

void CJsonBase::ToParseJson( const Value& value , uint32& t )
{
    t = value.GetUint();
}

void CJsonBase::ToParseJson( const Value& value , uint64& t )
{
    t = value.GetUint64();
}

void CJsonBase::ToParseJson( const Value& value , double& t )
{
    t = value.GetDouble();
}

void CJsonBase::ToParseJson( const Value& value , bool& t )
{
    t = value.GetBool();
}

void CJsonBase::ToParseJson( const Value& value , NLMISC::CSString& t )
{
    t = value.GetString();
}

void CJsonBase::ToParseJson( const Value& value , char t[] )
{
    sint32 size = SS_ARRAYSIZE( t );
    const char* s = value.GetString();
    int len = strlen( s );
    strncpy( t , s , (std::min( size , len )) );
}


SS_NAMESPACE_END_DECL
