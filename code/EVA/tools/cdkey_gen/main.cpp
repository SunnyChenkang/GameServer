#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

#include "nel/misc/debug.h"
#include "nel/misc/config_file.h"
#include "nel/misc/path.h"
#include "nel/misc/sstring.h"
#include "nel/misc/file.h"
#include "nel/misc/random.h"
#include "nel/misc/time_nl.h"

using namespace std;
using namespace NLMISC;

const char Base64NumberTable[] =
{
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z',
    '2','3','4','5','6','7','8','9'
};

#define  STAGES  sizeof(Base64NumberTable)

sint  GetBase64NumberTableIndex( char data )
{
    sint idx = -1;

    for ( uint i=0; i<STAGES; ++i )
    {
        if ( Base64NumberTable[i] == data )
        {
            idx = i;
            break;
        }
    }

    return idx;
}

std::string Base64NumberCoder( uint64 number )
{
    std::string  base64_num = "A";
    uint mod=0,index=0,uintmp[128];

    while ( number!=0 &&
            index<sizeof(uintmp) )
    {  
        uint mod = number%STAGES;  
        number=number/STAGES;  
        uintmp[index++]=mod;
    }

    if ( index > 0 )
    {
        base64_num.assign(index, '\0');
        for( sint k=index-1; k>=0; --k )
        {
            base64_num[k] = Base64NumberTable[ uintmp[k] ];
        }
    }

    return base64_num;
}

uint64 Base64NumberDecoder( std::string numberstr )
{
    uint64 decode_num = 0;

    for( sint k=numberstr.size()-1; k>=0; --k )
    {
        uint  mod = std::pow( (double)STAGES, k );
        decode_num += mod * GetBase64NumberTableIndex( numberstr[k] );
    }  

    return decode_num;
}

int main (int argc, char *argv[])
{
	createDebug( NULL, false );
	CConfigFile config;
	CPath::addSearchPath(".");

    config.load ( CPath::lookup("cdkey_gen.cfg") );	
    CRandom  randomL,randomR;
    randomL.srand( CTime::getLocalTime() );
    randomR.srand( CTime::getSecondsSince1970() );

    uint gen_num        = config.getVar("gen_num").asInt();
    uint gen_tid        = config.getVar("gen_template_id").asInt();
    uint cdkey_len      = config.getVar("cdkey_length").asInt();
    string  use_db      = config.getVar("use_database").asString();
    string  cdkey_head  = config.getVar("cdkey_head").asString();

    COFile   out_key("./cdkey.txt");
    COFile   out_sql("./cdkey.sql");

    string  cdkey;
    char sql_str[512] = {0};
    char sql_insert[] = "INSERT INTO t_gift_code (f_gift_code,f_template_id) VALUES ('%s','%d');\n";

    {
        sint sql_size = smprintf( sql_str, sizeof(sql_str), "use %s;\n", use_db.c_str() );
        out_sql.serialBuffer( (uint8*)sql_str, sql_size );
    }

    for ( uint row=0; row<gen_num; ++row )
    {
        cdkey.clear();
        cdkey.append( cdkey_head );
        cdkey.append( Base64NumberCoder(gen_tid) );
        uint i=0;

        while ( i<cdkey_len )
        {
            cdkey.append( 1, Base64NumberTable[ randomL.rand(sizeof(Base64NumberTable)-1) ] );
            cdkey.append( 1, Base64NumberTable[ randomR.rand(sizeof(Base64NumberTable)-1) ] );

            i += 2;
        }

        sint sql_size = smprintf( sql_str, sizeof(sql_str), sql_insert, cdkey.c_str(), gen_tid );
        out_sql.serialBuffer( (uint8*)sql_str, sql_size );

        cdkey.append("\n");
        out_key.serialBuffer( (uint8*)cdkey.c_str(), cdkey.size() );
    }

    out_sql.flush();
    out_sql.close();
    out_key.flush();
    out_key.close();

	return EXIT_SUCCESS;
}


