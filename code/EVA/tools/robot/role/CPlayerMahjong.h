#ifndef CPlayerMahjong_h__
#define CPlayerMahjong_h__
#include <game_share/game_def.h>
#include <server_share/database/record_player.h>
#include <nel/misc/random.h>
#include <game_share/proto_msg/msg_mahjong.pb.h>

struct MahJongCard
{
	MahJongCard( uint rhs )
	{
		card  = rhs;
		color = rhs & MASK_COLOR;
		value = rhs & MASK_VALUE;
	}
	~MahJongCard()
	{
	}

	uint color;
	uint value;
	uint card;
	uint wik;
};
typedef std::vector<MahJongCard> TMahjongHandCardList;

class CPlayerMahjong
{
public:
	CPlayerMahjong( void );
	virtual ~CPlayerMahjong( void );

	void OnSaveHandCard( MsgMahJongRoom& msgMahjongRoonInfo );

	MahJongCard* GetRandonHandCard();

	void RemoveHandCard( uint Card );
private:
	TMahjongHandCardList m_MahjongHandCardList;
	// Ëæ»ú;
	NLMISC::CRandom m_Random;
};

#endif //