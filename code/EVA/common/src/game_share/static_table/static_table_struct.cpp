#include "static_tabel_struct.h"
#include <game_share/tools.h>

ChallengeTime* ChallengeConfig::GetChallengeTime( uint32 get_time )
{
    ChallengeTime* pChallengeTime = NULL;
    uint32 _seconds = get_time % DAY_SECONDS;

    for ( uint i=0; i<m_ChallengeTime.size(); ++i )
    {
        if ( _seconds >= m_ChallengeTime[i].open  &&
             _seconds <= m_ChallengeTime[i].close )
        {
            pChallengeTime = &m_ChallengeTime[i];
            break;
        }
    }
    
    return pChallengeTime;
}

ChallengeTime* ChallengeConfig::GetTimeConfig( uint32 cfg_id )
{
    ChallengeTime* pChallengeTime = NULL;

    for ( int idx = 0 ; idx < m_ChallengeTime.size(); idx++ )
    {
        if ( m_ChallengeTime[ idx ].id == cfg_id )
        {
            pChallengeTime = &m_ChallengeTime[idx];
            break;
        }
    }
    return pChallengeTime;
}

ChallengeTime* ChallengeConfig::GetChallengeNotClearing( uint32 get_time )
{
    ChallengeTime* pChallengeTime = NULL;
    uint32 _seconds = get_time % DAY_SECONDS;

    for ( uint i=0; i<m_ChallengeTime.size(); ++i )
    {
        if ( _seconds >= m_ChallengeTime[i].open  &&
             _seconds <= m_ChallengeTime[i].clear_rnk )
        {
            pChallengeTime = &m_ChallengeTime[i];
            break;
        }
    }

    return pChallengeTime;
}

ChallengeReward* ChallengeConfig::GetChallengeReward( DEF::RANKING rnk )
{
    ChallengeReward* pReward = NULL;

    for ( uint i=0; i<m_ChallengeReward.size(); ++i )
    {
        if ( rnk >= m_ChallengeReward[i].ranking_left  &&
             rnk <= m_ChallengeReward[i].ranking_right )
        {
            pReward = &m_ChallengeReward[i];
            break;
        }
    }

    return pReward;
}

ChallengeBuyBack* ChallengeConfig::GetBuyBack( uint32 buy_num )
{
    ChallengeBuyBack* pBuyBack = NULL;

    for ( uint i=0; i<m_BuyBack.size(); ++i )
    {
        pBuyBack = &m_BuyBack[i];

        if ( buy_num == pBuyBack->buy_num )
        {
            break;
        }
    }

    return pBuyBack;
}


