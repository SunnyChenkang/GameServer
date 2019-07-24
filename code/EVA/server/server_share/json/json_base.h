#ifndef SS_JSON_BASE_H_
#define SS_JSON_BASE_H_

#include <server_share/common/common.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

SS_NAMESPACE_BEGIN_DECL

using namespace rapidjson;

// writer json;
#define JsonWriteBegin( writer ) {  writer.StartObject();
#define JsonWriteEnd()              writer.EndObject(); }
#define JsonWriterString( xxx )     writer.Key( #xxx );writer.String( xxx.data() );
#define JsonWriterChar( xxx )       writer.Key( #xxx );writer.String( xxx , strlen(xxx) );
#define JsonWriterInt( xxx )        writer.Key( #xxx );writer.Int( xxx );
#define JsonWriterInt64( xxx )      writer.Key( #xxx );writer.Int64( xxx );
#define JsonWriterUInt( xxx )       writer.Key( #xxx );writer.UInt( xxx );
#define JsonWriterUInt64( xxx )     writer.Key( #xxx );writer.Uint64( xxx );
#define JsonWriterDouble( xxx )     writer.key( #xxx );writer.Double( xxx );
#define JsonWriterClass( xxx )      writer.key( #xxx );((CJsonBase*)(&xxx))->ToWriter( writer );

// reads json;

#define PARSE_VALUE_BEGIN void ParseJson( const Value& JsonValue ) {
#define PARSE_VALUE_END   }

#define PARSE_VALUE_ARRAY_BEGIN void ParseJsonArray( const Value& JsonValue ) {
#define PARSE_VALUE_ARRAY_END }

#define JsonParseBegin( val ) for ( Value::ConstMemberIterator it = val.MemberBegin(); it != val.MemberEnd(); ++it ) { const Value& Values = it->value;
#define JsonParseEnd() }
#define JsonParseArrayBegin( val ) for ( sint32 idx = 0; idx < val.Size(); idx++ ) { const Value& Values =  val[idx];
#define JsonParseArrayEnd() }

#define JsonParseToString( xxx )    if ( strcmp( it->name.GetString() , #xxx) == 0 ) xxx = it->value.GetString();
#define JsonParseToInt( xxx )       if ( strcmp( it->name.GetString() , #xxx) == 0 ) xxx = it->value.GetInt();
#define JsonParseToInt64( xxx )     if ( strcmp( it->name.GetString() , #xxx) == 0 ) xxx = it->value.GetInt64();
#define JsonParseToUInt( xxx )      if ( strcmp( it->name.GetString() , #xxx) == 0 ) xxx = it->value.GetUint();
#define JsonParseToUInt64( xxx )    if ( strcmp( it->name.GetString() , #xxx) == 0 ) xxx = it->value.GetUint64();
#define JsonParseToDouble( xxx )    if ( strcmp( it->name.GetString() , #xxx) == 0 ) xxx = it->value.GetDouble();
#define JsonParseToClass( xxx )     if ( strcmp( it->name.GetString() , #xxx) == 0 ) ((CJsonBase*)(&xxx))->ParseJson( it->value );
#define JsonParseToChar( xxx )      if ( strcmp( it->name.GetString() , #xxx) == 0 )\
{\
    int size = SS_ARRAYSIZE( xxx );\
    const char* s = it->value.GetString();\
    int len = strlen( s );\
    strncpy( xxx , s , (std::min(size , len)) );\
}\

class CJsonBase;
typedef std::shared_ptr< CJsonBase > CJsonBasePtr;

class CJsonBase
{
public:
    typedef std::map< NLMISC::CSString , CJsonBasePtr > JSON_STRING_KEYTABLE;
    typedef std::map< uint32           , CJsonBasePtr > JSON_UINT32_KEYTABLE;

    CJsonBase( void ){ };
    virtual ~CJsonBase( void ){ };

    // load json file;
    void LoadJson( NLMISC::CSString );

    // get json cell;
    template< typename T >
    T* GetJsonCell( NLMISC::CSString name );
    template< typename T >
    T* GetJsonCell( uint32 id );

    NLMISC::CSString ToJson( void );
    void FromJson( CJsonBase* , const NLMISC::CSString& );

protected:
    // writer template;
    template< typename T >
    static void ToWriterJson( Writer< StringBuffer >& Writer , T& val );

    // writer int32;
    static void ToWriterJson( Writer< StringBuffer >& , sint32& );
    static void ToWriterJson( Writer< StringBuffer >& , uint32& );
    // writer int64;
    static void ToWriterJson( Writer< StringBuffer >& , sint64& );
    static void ToWriterJson( Writer< StringBuffer >& , uint64& );
    // writer double;
    static void ToWriterJson( Writer< StringBuffer >& , double& );
    // writer bool;
    static void ToWriterJson( Writer< StringBuffer >& , bool&   );
    // writer string;
    static void ToWriterJson( Writer< StringBuffer >& , NLMISC::CSString& );
    static void ToWriterJson( Writer< StringBuffer >& , char* );


    // parse template;
    template< typename T >
    static void ToParseJson( const Value& val , T& t );
    // parse int32;
    static void ToParseJson( const Value& , sint32& );
    static void ToParseJson( const Value& , uint32& );
    // parse int64;
    static void ToParseJson( const Value& , sint64& );
    static void ToParseJson( const Value& , uint64& );
    // parse double;
    static void ToParseJson( const Value& , double& );
    // parse bool;
    static void ToParseJson( const Value& , bool&   );
    // parse string;
    static void ToParseJson( const Value& , NLMISC::CSString& );
    static void ToParseJson( const Value& , char t[] );

public:
    // 子类继承需要;
    virtual void WriterJson( Writer<StringBuffer>& ){ };
    virtual void ParseJson ( const Value& ) { nlinfo( "parse json base class..." ); };
    virtual void ParseJsonArray( const GenericValue< UTF8<> >& ) { };

    SS_PROPERTY( JSON_STRING_KEYTABLE , JsonStringArray , protected );
    SS_PROPERTY( JSON_UINT32_KEYTABLE , JsonUint32Array , protected );
};

template< typename T >
class CJsonArray : public CJsonBase
{
public:
    CJsonArray( void ){ };
   ~CJsonArray( void ){ };

    SS_PROPERTY( std::vector< T > , JsonArray , public );

public:
    virtual void WriterJson( Writer<StringBuffer>& Writer );
    virtual void ParseJson( const Value& val );
};

#include "json_template.inl"

SS_NAMESPACE_END_DECL

#endif // SS_JSON_BASE_H_