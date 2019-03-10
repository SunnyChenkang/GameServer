#include "static_table_ddzpool.h"
#include <nel/misc/file.h>
#include <nel/misc/i_xml.h>

using namespace NLMISC;

bool DDZPoolConFig::LoadCardConfig( void )
{
	CIFile file;
	ResetData();
	file.setCacheFileOnOpen( true );
	std::string path = NLMISC::CPath::lookup("DouDiZhuCardPool//ddz.txt");
	if ( !file.open( path ) ) {
		return false;
	}
	char strBuff[1024] = { '\0' };

	// 解析玩家手牌;
	sint32 nIndex = 0;
	while ( !file.eof() )
	{
		if ( 4 == m_HandCardPool.size() ) { break; }
		file.getline( strBuff , sizeof( strBuff ) );
		CSString strSub( strBuff );
		CVectorSString strVec;
		strVec.clear();
		strSub.splitBySeparator('\t' , strVec );
		if ( strVec.empty() ) { continue; }
		std::vector<uint8> CardList;
		for ( int idx = 0; idx < strVec.size(); idx++ )
		{
			uint8 CardValue = SwitchToCardValue( strVec[idx] );
			if ( CardValue <= 0 ) { continue; }
			CardList.push_back( CardValue );
		}
		m_HandCardPool.push_back( CardList );
		nIndex++;
	}

	return true;
}

bool DDZPoolConFig::IsValidConfig( void ) const
{
	if ( 4 != m_HandCardPool.size() )
		return false;
	return true;
}
/*
转换规则：
a 黑桃
b 红桃
c 梅花
d 方块
e1 小王
e2 大王
*/

uint8 DDZPoolConFig::SwitchToCardValue( CSString& str )
{
	uint8 CvRet = 0;
	CSString left = str.left( 1 );
	CSString right = str.right( str.length() - 1 );
	uint8 CardColor = 0;
	uint8 CardValue = 0;

	// 颜色值
	if ( left == "a" )
	{
		CardColor = 3;
	}
	else if ( left == "b" )
	{
		CardColor = 2;
	}
	else if ( left == "c" )
	{
		CardColor = 1;
	}
	else if ( left == "d" )
	{
		CardColor = 0;
	}
	else if ( left == "e" )
	{
		CardColor = 4;
	}

	// 牌值
	CardValue = atoi( right.c_str() );

	CvRet = ( ( CardColor << 4 ) | CardValue );

	return CvRet;
}