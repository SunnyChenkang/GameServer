#ifndef GAME_SHARD_RANKING_SLOT_H
#define GAME_SHARD_RANKING_SLOT_H

#include <vector>
#include <map>
#include <set>
#include <nel/misc/time_nl.h>
#include "game_def.h"

/** 排名槽管理器
 *	使用PID作为索引，SCORE作为排名依据，获取排名。
 *  按积分槽排名。
 *  分数槽小于1W时效率较高:         UpdateRanking<2ms 。
 *  分数槽小于10W时(Release):      UpdateRanking<10ms 。
 *
 * \author li9chuan
 * \date 2015-1
 */

typedef  std::set<DEF::PID>     TSetPIDs;

struct PIDRanking
{
    DEF::PID        pid;
    DEF::RANKING    rnk;
    PIDRanking() : pid(0), rnk(0) {}
};

struct SlotRankingData
{
    DEF::RANKING    Ranking;
    TSetPIDs        PIDs;

    SlotRankingData():Ranking(0){}
};

class CRankingSlot
{
public:

    typedef  std::vector<DEF::PID>  _TVctPIDs;

    typedef  std::map<DEF::PID, DEF::SCORE>         TMapScore;
    typedef  std::map<DEF::SCORE, SlotRankingData>  TPIDsRanking;

    TPIDsRanking    m_PIDsRanking;

    CRankingSlot():_UpdateSeconds(0),_PreUpdateSecond1970(0),_FastSortMax(0)
    {
        ClearCurrIter();
    }

	/**
	*   初始化排行处理逻辑
	*
	*	\param  update_seconds  调用 UpdateRanking() 的最小间隔时间。
	*	\param  fast_sort_num   SetScore时，在fast_sort_num前的排名会即时更新。
	*/ 
    void InitRanking( uint32 update_seconds, uint32 fast_sort_num )
    {
        _UpdateSeconds  = update_seconds;
        _FastSortMax    = fast_sort_num;
    }

	/**
	*   设置玩家积分
	*
	*	\param  nID
	*	\param  nScore
	*/
	void SetScore( const DEF::PID pid, const DEF::SCORE score )
	{
        DEF::RANKING nRankingNew = 0;
        ClearCurrIter();

        ///  移除玩家旧排名
        TMapScore::iterator itscr = _MapScore.find( pid );

        if ( itscr!=_MapScore.end() )
        {
            DEF::SCORE old_score = itscr->second;

            if ( old_score==score )
            {
                return;
            }

            TPIDsRanking::iterator itrnk = m_PIDsRanking.find( old_score );

            if ( itrnk!=m_PIDsRanking.end() )
            {
                itrnk->second.PIDs.erase(pid);

                if ( itrnk->second.PIDs.empty() )
                {
                    m_PIDsRanking.erase(itrnk);
                }
            }

			itscr->second = score;
        }
        else
        {
            _MapScore.insert( std::make_pair(pid,score) );
        }


        /// 插入玩家新排名
        TPIDsRanking::iterator itrnk = m_PIDsRanking.find( score );

        if ( itrnk!=m_PIDsRanking.end() )
        {
            /// 如果已存在积分排名，插入对应积分槽内。
            itrnk->second.PIDs.insert( pid );
            nRankingNew = itrnk->second.Ranking;
        }
        else
        {
            /// 如果没有输入的积分，新插入一条
            SlotRankingData  Rnk;
            Rnk.PIDs.insert(pid);

            std::pair<TPIDsRanking::iterator,bool> ret =  m_PIDsRanking.insert( std::make_pair( score, Rnk ) );
			
            if ( ret.first != m_PIDsRanking.begin() )
            {
                TPIDsRanking::iterator it_cur = ret.first;
                TPIDsRanking::iterator it_pre = --ret.first;

                nRankingNew = it_pre->second.Ranking + it_pre->second.PIDs.size();
                it_cur->second.Ranking = nRankingNew;
            }
            else
            {
                nRankingNew = 1;
                ret.first->second.Ranking = nRankingNew;
            }
        }

        ///    如果是前几名，那么即时排，不等update

        if ( nRankingNew <= _FastSortMax )
        {
            _TopRnkPIDs.clear();

            uint  rnk_idx = 0;
            TPIDsRanking::reverse_iterator itrnk       = m_PIDsRanking.rbegin();
            TPIDsRanking::reverse_iterator itrnk_end   = m_PIDsRanking.rend();

            if ( itrnk!=itrnk_end )
            {
                itrnk->second.Ranking = 1;

                TSetPIDs::iterator  itpids     = itrnk->second.PIDs.begin();
                TSetPIDs::iterator  itpids_end = itrnk->second.PIDs.end();

                while ( itpids!=itpids_end )
                {
                    _TopRnkPIDs.push_back( *itpids );

                    ++rnk_idx;
                    ++itpids;

                    if ( rnk_idx>_FastSortMax )
                    {
                        return;
                    }
                }

                ++itrnk;
            }

            while ( itrnk!=itrnk_end )
            {
                TPIDsRanking::reverse_iterator it_pre = itrnk;
                --it_pre;
                itrnk->second.Ranking = it_pre->second.Ranking + it_pre->second.PIDs.size();

                TSetPIDs::iterator  itpids     = itrnk->second.PIDs.begin();
                TSetPIDs::iterator  itpids_end = itrnk->second.PIDs.end();

                while ( itpids!=itpids_end )
                {
                    _TopRnkPIDs.push_back( *itpids );

                    ++rnk_idx;
                    ++itpids;

                    if ( rnk_idx>_FastSortMax )
                    {
                        return;
                    }
                }

                ++itrnk;
            }
        }
	}

	/**
	*   获取排名
	*
	*	\param  nID
	*	\return 排名从1开始，0表示没有找到此ID
	*/
	DEF::RANKING GetRanking( const DEF::SCORE score )
	{
        DEF::RANKING  rnk = 0;
        TPIDsRanking::iterator iter = m_PIDsRanking.find(score);

        if ( iter!=m_PIDsRanking.end() )
        {
            m_CurrRnkIter = iter;
            rnk = iter->second.Ranking;
        }

		return rnk;
	}

    DEF::RANKING GetOldRanking( DEF::PID pid )
    {
        TMapScore::iterator itscr = _MapScore.find( pid );

        if ( itscr!=_MapScore.end() )
        {
            TPIDsRanking::iterator itrnk = m_PIDsRanking.find( itscr->second );

            if ( itrnk!=m_PIDsRanking.end() )
            {
                m_CurrRnkIter = itrnk;
                return itrnk->second.Ranking;
            }
        }
        return 0;
    }

    void UpdateRanking( bool force_update=false )
    {
        uint32 curr_seconds = NLMISC::CTime::getSecondsSince1970();

        if ( force_update ||
             curr_seconds - _PreUpdateSecond1970 < _UpdateSeconds )
        {
            return;
        }

        ClearCurrIter();
        _PreUpdateSecond1970 = curr_seconds;
        _ResortRanking();
    }

    DEF::SCORE GetScore( DEF::PID unRoleID )
    {
        std::map<DEF::PID, DEF::SCORE> ::iterator it = _MapScore.find( unRoleID );
        if ( it == _MapScore.end() ) {
            return 0;
        }

        return it->second;
    }

    std::vector<DEF::PID>&  GetTopRanking()
    {
        return _TopRnkPIDs;
    }

    /**
	*   获取排名
	*
	*	\param  nID
	*	\return 排名从1开始，0表示没有找到此ID
	*/
    SlotRankingData* GetSlotRankingData( DEF::SCORE score )
    {
        SlotRankingData* pSlotRankingData = NULL;
        TPIDsRanking::iterator iter = m_PIDsRanking.find(score);

        if ( iter!=m_PIDsRanking.end() )
        {
            pSlotRankingData = &(iter->second);
        }

        return pSlotRankingData;
    }

    /**
	*   其它查找函数调用后，继续获取前一排名。
	*
	*	\return PIDRanking
	*/
    PIDRanking Previous()
    {
        PIDRanking pid_rnk;

        if ( m_CurrRnkIter != m_PIDsRanking.end() )
        {
            ++m_CurrRnkIter;

            if ( m_CurrRnkIter != m_PIDsRanking.end() &&
                 m_CurrRnkIter->second.PIDs.size() > 0 )
            {
                TSetPIDs::iterator iter = m_CurrRnkIter->second.PIDs.begin();
                pid_rnk.pid = *iter;
                pid_rnk.rnk = m_CurrRnkIter->second.Ranking;
            }
        }

        return pid_rnk;
    }

    void ClearCurrIter()
    {
        m_CurrRnkIter = m_PIDsRanking.end();
    }

private:

    void    _ResortRanking()
    {
        TPIDsRanking::reverse_iterator itrnk       = m_PIDsRanking.rbegin();
        TPIDsRanking::reverse_iterator itrnk_end   = m_PIDsRanking.rend();

        if ( itrnk!=itrnk_end )
        {
            itrnk->second.Ranking = 1;
            ++itrnk;
        }

        while ( itrnk!=itrnk_end )
        {
            TPIDsRanking::reverse_iterator it_pre = itrnk;
            --it_pre;
            itrnk->second.Ranking = it_pre->second.Ranking + it_pre->second.PIDs.size();
            ++itrnk;
        }
    }


    _TVctPIDs       _TopRnkPIDs;
    
    TMapScore       _MapScore;

    uint32          _UpdateSeconds;
    uint32          _PreUpdateSecond1970;
    uint32          _FastSortMax;

    TPIDsRanking::iterator   m_CurrRnkIter;
};


#endif // GAME_SHARD_RANKING_SLOT_H

/* End of ranking_solt.h */
