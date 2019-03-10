#include "json_base.h"

SS_NAMESPACE_BEGIN_DECL

NLMISC::CSString CJsonBase::ToJson( void )
{
    StringBuffer s;
    Writer< StringBuffer > writer( s );
    this->WriterJson( writer );
    return s.GetString();
}

void CJsonBase::FromJson( CJsonBase* json_base , const NLMISC::CSString& json )
{
    Document doc;
    doc.Parse( json.data() );
    const Value& val = doc;
    json_base->ParseJson( val );
}

void CJsonBase::LoadJson( NLMISC::CSString file_name )
{
    std::string file_path = NLMISC::CPath::lookup( file_name );
    if ( file_path.empty() ) return;

    NLMISC::CIFile   json_file;
    NLMISC::CSString json_desc;
    NLMISC::CSString json_line;

    if ( !json_file.open(file_path) )
    {
        nlinfo( " open file failes~ [%s]" , file_path.c_str() );
        return;
    }
    while ( !json_file.eof() )
    {
        char StrBuffer[1024] = { '\0' };
        json_file.getline( StrBuffer , sizeof( StrBuffer ) );
        json_line = StrBuffer;
        json_desc.append( json_line + '\n');
    }
    json_file.close();
    FromJson( this , json_desc );
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
