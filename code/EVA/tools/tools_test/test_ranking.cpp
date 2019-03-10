#include "test_misc.h"
#include <game_share/ranking_slot.h>
#include <game_share/ranking_change_near.h>
#include <nel/misc/random.h>
#include <nel/misc/time_nl.h>

using namespace std;
using namespace NLMISC;

CRankingChangeNear   Ranking;

void test_erase_ranking()
{
    cout<<"---------------  test_erase_ranking ----------------"<<endl;
    Ranking.SetScore(123,900);
    Ranking.SetScore(1234,800);
    Ranking.SetScore(124,700);
    Ranking.SetScore(133,100);
    Ranking.SetScore(223,200);
    Ranking.SetScore(333,300);
    Ranking.SetScore(453,400);
    Ranking.SetScore(763,500);
    
    CRankingChangeNear::TRankingPlayerInfo rank_info;
    rank_info = Ranking.GetRankingInfo();
    CRankingChangeNear::TRankingPlayerInfo::iterator iter = rank_info.begin();
    while (iter != rank_info.end())
    {
        cout<<"id:"<<iter->nID<<" score:"<<iter->nScore<<endl;
        ++iter;
    }
    cout<<"---------------  iter_new ----------------"<<endl;
    Ranking.Erase(1234);
    rank_info = Ranking.GetRankingInfo();
    CRankingChangeNear::TRankingPlayerInfo::iterator iter_new = rank_info.begin();
    while (iter_new != rank_info.end())
    {
        cout<<"id:"<<iter_new->nID<<" score:"<<iter_new->nScore<<endl;
        ++iter_new;
    }
    cout<<"---------------  iter_newnew ----------------"<<endl;
    Ranking.Erase(123);
    Ranking.Erase(124);
    Ranking.Erase(133);
    Ranking.Erase(223);
    Ranking.Erase(333);
    Ranking.Erase(453);
    rank_info = Ranking.GetRankingInfo();
    CRankingChangeNear::TRankingPlayerInfo::iterator iter_newnew = rank_info.begin();
    while (iter_newnew != rank_info.end())
    {
        cout<<"id:"<<iter_newnew->nID<<" score:"<<iter_newnew->nScore<<endl;
        ++iter_newnew;
    }
    cout<<"---------------  delete ----------------"<<endl;
    Ranking.Erase(763);
    Ranking.Erase(123);
    rank_info = Ranking.GetRankingInfo();
    CRankingChangeNear::TRankingPlayerInfo::iterator iter_delete = rank_info.begin();
    while (iter_delete != rank_info.end())
    {
        cout<<"id:"<<iter_delete->nID<<" score:"<<iter_delete->nScore<<endl;
        ++iter_delete;
    }
    system("pause");
}

void test_ranking()
{
    cout<<"---------------  test_ranking ----------------"<<endl;

    const uint16 SCORE_RANDOM_ADD = 100;

    NLMISC::CRandom   random;
 
    std::vector<uint>   m_vctScore;
    m_vctScore.resize(1000001);

    for ( uint i=1000000; i>0; --i )
    {
        m_vctScore[i] = (i/100) + random.rand(SCORE_RANDOM_ADD);;
    }

    uint32 start_time = CTime::getLocalTime();

    for ( uint i=1000000; i>0; --i )
    {
        Ranking.SetScore( i, m_vctScore[i] );
    }

    cout<<"cost time:"<<CTime::getLocalTime()-start_time<<endl;


    for ( uint i=1000000; i>0; --i )
    {
        m_vctScore[i] = m_vctScore[i]+random.rand(SCORE_RANDOM_ADD);
    }

    start_time = CTime::getLocalTime();

    for ( uint i=1000000; i>0; --i )
    {
        Ranking.SetScore( i, m_vctScore[i] );
    }

    cout<<"cost time:"<<CTime::getLocalTime()-start_time<<endl;

    system("pause");
}


CRankingSlot   rnk_min;

void test_ranking_min()
{
    cout<<"---------------  test_ranking_min ----------------"<<endl;

    rnk_min.InitRanking(0,50);
    const uint16 SCORE_RANDOM_ADD = 32767;

    NLMISC::CRandom   random;

    std::vector<uint>   m_vctScore;
    m_vctScore.resize(1000001);

    for ( uint i=1000000; i>0; --i )
    {
        m_vctScore[i] = random.rand(SCORE_RANDOM_ADD);
    }

    uint32 start_time = CTime::getLocalTime();

    for ( uint i=1000000; i>0; --i )
    {
        rnk_min.SetScore( i, m_vctScore[i] );
    }

    cout<<"cost time:"<<CTime::getLocalTime()-start_time<<endl;


    for ( uint i=1000000; i>0; --i )
    {
        m_vctScore[i] = random.rand(SCORE_RANDOM_ADD);
    }

    start_time = CTime::getLocalTime();

    for ( uint i=1000000; i>0; --i )
    {
        rnk_min.SetScore( i, m_vctScore[i] );
    }

    cout<<"cost time:"<<CTime::getLocalTime()-start_time<<endl;

    start_time = CTime::getLocalTime();

    for ( uint i=0; i<1; ++i )
        rnk_min.UpdateRanking();

    cout<<"cost time:"<<CTime::getLocalTime()-start_time<<endl;

    system("pause");
}


