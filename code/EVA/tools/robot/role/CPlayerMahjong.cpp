#include "CPlayerMahjong.h"

CPlayerMahjong::CPlayerMahjong( void )
{
	m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
}

CPlayerMahjong::~CPlayerMahjong( void )
{

}

void CPlayerMahjong::OnSaveHandCard( MsgMahJongRoom& msgMahjongRoonInfo )
{
	for ( int i = 0; i < msgMahjongRoonInfo.hand_card().size(); ++i )
	{
		MahJongCard Data( msgMahjongRoonInfo.hand_card(i) );
		m_MahjongHandCardList.push_back( Data );
	}
}

MahJongCard* CPlayerMahjong::GetRandonHandCard()
{
	if( !m_MahjongHandCardList.empty() )
	{
		TMahjongHandCardList::iterator it = m_MahjongHandCardList.begin();
		if( it == m_MahjongHandCardList.end() )
			return NULL;

		int dist = std::distance( m_MahjongHandCardList.begin() , m_MahjongHandCardList.end() );
		std::advance( it , m_Random.rand( dist - 1 ) );

		return &(*it);
	}
	return NULL;
}

void CPlayerMahjong::RemoveHandCard( uint Card )
{
	TMahjongHandCardList::iterator it = m_MahjongHandCardList.begin();
	for ( ; it != m_MahjongHandCardList.end(); ++it )
	{
		if ( it->card != Card ) { continue; }
		m_MahjongHandCardList.erase(it);

		break;
	}
}
