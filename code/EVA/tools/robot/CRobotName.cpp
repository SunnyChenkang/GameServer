#include "CRobotName.h"
#include <nel/misc/debug.h>
#include <game_share/game_def.h>

CRobotName::CRobotName( void )
{
    m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
    m_Name.clear();
    m_Surname.clear();
}

CRobotName::~CRobotName( void )
{
}

void CRobotName::LoadRandomName( void )
{
    FILE* SFile = fopen( "surname.txt" , "r" );
    if ( NULL == SFile ) {
        nldebug( " load name file faile " );
        return;
    }

    char SurnBuff[ 32 ] = {'\0'};

    while ( true )
    {
        if ( !fgets( SurnBuff , sizeof( SurnBuff ) , SFile ) )
            break;

        for ( int index = 0 ; index < sizeof( SurnBuff ) ; ++index )
        {
            if ( SurnBuff[ index ] == 0xA )
            {
                SurnBuff[ index ] = '\0';
                break;
            }
        }

        m_Surname.push_back( std::string( SurnBuff ) );
    }

    fclose( SFile );

    FILE* NFile = fopen( "name.txt" , "r" );
    if ( NULL == NFile ){
        nldebug( " load name file faile " );
        return;
    }

    char NameBuff[ 32 ] = { '\0' };

    while ( true )
    {
        if ( !fgets( NameBuff , sizeof( NameBuff ) , NFile ) )
            break;

        for ( int index = 0 ; index < sizeof( NameBuff ); ++index )
        {
            if ( NameBuff[ index ] == 0xA )
            {
                NameBuff[ index ] = '\0';
                break;
            }
        }

        m_Name.push_back( std::string( NameBuff ) );
    }

    fclose( NFile );
}

std::string CRobotName::GetRandomName( void )
{
    int SurnLen = m_Surname.size();
    int NameLen = m_Name.size();

    if ( 0 == SurnLen || 0 == NameLen )
    {
        return "";
    }

    sint32 SurnRandom = m_Random.rand() % ( SurnLen - 1 );
    sint32 NameRandom = m_Random.rand() % ( NameLen - 1 );

    return ( m_Surname[ SurnRandom ] + m_Name[ NameRandom ] );
}