#include "static_table_qualifying.h"
#include "../tools.h"
#include <ctime>

using namespace std;
using namespace NLMISC;

CQualifyingConfiger::CQualifyingConfiger( void )
{
    m_PiecwiseTable.clear();
}

CQualifyingConfiger::~CQualifyingConfiger( void )
{

}

void CQualifyingConfiger::LoadQualifyingXml( void )
{
    LoadPiecewiseXml();
}

bool CQualifyingConfiger::IsExist( std::string& RoomType )
{
    return ( m_PiecwiseTable.count( RoomType ) > 0 );
}

PiecewiseData* CQualifyingConfiger::GetPiecewiseData( std::string& RoomName , uint32 DanWeiID )
{
    PiecewiseTable::iterator it = m_PiecwiseTable.find( RoomName );
    if ( it == m_PiecwiseTable.end() ) return NULL;
    for ( int idx = 0; idx < it->second.size(); idx++ )
    {
        if ( it->second[idx].DanWeiID != DanWeiID ) { continue; }
        return &(it->second[idx]);
    }
    return NULL;
}

PiecewiseData* CQualifyingConfiger::GetMinPiecewiseData( std::string& RoomName )
{
    PiecewiseTable::iterator it = m_PiecwiseTable.find( RoomName );
    if ( it == m_PiecwiseTable.end() ) return NULL;
    if ( it->second.empty() ) return NULL;
    return &(it->second[0]);
}

PiecewiseData* CQualifyingConfiger::GetMaxPiecewiseData( std::string& RoomName )
{
    PiecewiseTable::iterator it = m_PiecwiseTable.find( RoomName );
    if ( it == m_PiecwiseTable.end() ) return NULL;
    if ( it->second.empty() ) return NULL;
    return &(it->second[it->second.size()-1]);
}

void CQualifyingConfiger::LoadPiecewiseXml( void )
{
    std::string path = NLMISC::CPath::lookup("PiecewisePrototype.xml");
    CIFile file;
    CIXml xml;

    if ( !file.open( path ) ) { return; }
    if ( !xml.init( file ) )  { return; }

    xmlNodePtr RootPtr = xml.getRootNode();
    if ( NULL == RootPtr ) { return; }

    m_PiecwiseTable.clear();

    xmlNodePtr pPiecewisePtr = xml.getFirstChildNode( RootPtr , "piecewise" );
    for ( ; pPiecewisePtr != NULL; pPiecewisePtr = xml.getNextChildNode( pPiecewisePtr , "piecewise") )
    {
        PiecewiseData Piecewise;
        Piecewise.DanWeiID          = CIXml::getIntProperty( pPiecewisePtr , "id" , 0 );
        Piecewise.RisingStar        = CIXml::getIntProperty( pPiecewisePtr , "rising_star" , 0 );
        Piecewise.RisingStarScore   = CIXml::getIntProperty( pPiecewisePtr , "rising_star_score" , 0 );
        Piecewise.ProtectScore      = CIXml::getIntProperty( pPiecewisePtr , "protect_score" , 0 );
        Piecewise.BaseScore         = CIXml::getIntProperty( pPiecewisePtr , "base_score" , 0 );
        Piecewise.CreditPenalty     = CIXml::getIntProperty( pPiecewisePtr , "credit_penalty" , 0 );
        Piecewise.CreditLimit       = CIXml::getIntProperty( pPiecewisePtr , "credit_limit" , 0 );
        Piecewise.RoomType          = CIXml::getStringProperty( pPiecewisePtr , "match_type"   , "");
        m_PiecwiseTable[Piecewise.RoomType].push_back( Piecewise );
    }
}
