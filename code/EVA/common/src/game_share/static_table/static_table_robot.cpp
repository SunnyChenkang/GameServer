#include "static_table_robot.h"
#include <game_share/tools.h>

using namespace std;

string RobotConfig::GetRandomName()
{
    std::string  rnd_name = m_BaseName;
    rnd_name.append( NLMISC::toString( GetRandom() ) );

    //sint16 sur_idx  = surnames.size()-1;
    //sint16 name_idx = names.size()-1;

    //rnd_name.append( surnames.at( GetRandom(sur_idx) ) );
    //rnd_name.append( names.at( GetRandom(name_idx) ) );

    return rnd_name;
}

RobotDefine* RobotConfig::GetRobotDefine( std::string name )
{
    RobotDefine* pRobotDefine = NULL;
    TRobotDefines::iterator iter = m_RobotDefines.find( name );

    if ( iter != m_RobotDefines.end() )
    {
        pRobotDefine = &(iter->second);
    }

    return pRobotDefine;
}

uint32 RobotDefine::GetEnterTime()
{
    return enter_time + GetRandom(variation);
}

DEF::MONEY RobotDefine::GetBaseMoney()
{
    return base_money + GetRandom();
}
