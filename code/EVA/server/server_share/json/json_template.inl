#include "json_base.h"

template< typename T >
void SS::CJsonBase::ToWriterJson( Writer< StringBuffer >& Writer , T& val )
{
    CJsonBase* pJsonBase = &val;
    pJsonBase->WriterJson( Writer );
}

template< typename T >
void SS::CJsonBase::ToParseJson( const Value& val , T& t )
{
    CJsonBase* pJsonBase = &t;
    pJsonBase->ParseJson( val );
}

template< typename T >
T* SS::CJsonBase::GetJsonCell( uint32 id )
{
    JSON_UINT32_KEYTABLE::iterator it = m_JsonUint32Table.find( id );
    if ( it == m_JsonUint32Table.end() ) return NULL;
    return dynamic_cast<T*>( it->second );
}

template< typename T >
T* SS::CJsonBase::GetJsonCell( NLMISC::CSString name )
{
    JSON_STRING_KEYTABLE::iterator it = m_JsonStringTable.find( name );
    if ( it == m_JsonStringTable.end() ) return NULL;
    return dynamic_cast<T*>( it->second );
}

template< typename T >
void SS::CJsonArray<T>::WriterJson(Writer<StringBuffer> & writer)
{
    writer.StartArray();
    typename std::vector< T >::iterator it = m_JsonArray.begin();
    for ( ; it != m_JsonArray.end(); ++it )
    {
        ToWriterJson( writer , *it );
    }
    writer.EndArray();
}

template< typename T >
void SS::CJsonArray<T>::ParseJson(const Value& val)
{
    SizeType len = val.Size();
    for ( size_t idx =  0; idx < len; ++idx )
    {
        const Value& f = val[idx];
        T t;
        ToParseJson( f , t );
        m_JsonArray.push_back( t );
    }
}