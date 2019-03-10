#ifndef STATIC_TABLE_ROBOT_H
#define STATIC_TABLE_ROBOT_H

#include <vector>
#include <string>
#include <game_share/game_def.h>

struct RobotRandomName
{
    std::vector<std::string>    surnames;
    std::vector<std::string>    names;

    void        Clear() { surnames.clear();  names.clear(); };
};

struct RobotDefine
{
    uint32      enter_time;
    uint32      variation;
    uint32      max_robot;
    DEF::MONEY  base_money;

    uint32      GetEnterTime();
    DEF::MONEY  GetBaseMoney();

    RobotDefine() : enter_time(10), variation(5), max_robot(0), base_money(0) {}
};

typedef std::map<std::string, RobotDefine>       TRobotDefines;

struct RobotConfig
{
    uint32                                  m_ShardID;
    uint32                                  m_StartPID;
    std::string                             m_BaseName;

    RobotRandomName                         m_RobotRandomName;
    TRobotDefines                           m_RobotDefines;

    RobotDefine*        GetRobotDefine( std::string name );
    std::string         GetRandomName();
    
    void                Clear()
    {
        m_RobotRandomName.Clear();
        m_RobotDefines.clear();
    }

    RobotConfig():m_ShardID(0), m_StartPID(5000)   {}
};

#endif // STATIC_TABLE_ROBOT_H
