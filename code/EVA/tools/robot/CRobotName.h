#ifndef CRandomName_h__
#define CRandomName_h__
#include <string>
#include <vector>
#include <nel/misc/random.h>

class CRobotName
{
public:
    CRobotName( void );
   ~CRobotName( void );

    // 加载名字文件;
    void LoadRandomName( void );

    // 随机名字;
    std::string GetRandomName( void );

    static CRobotName* GetInstance( void )
    {
        static CRobotName _inst;
        return ( &_inst );
    }

private:
    NLMISC::CRandom            m_Random;
    std::vector< std::string > m_Surname;
    std::vector< std::string > m_Name;

    CRobotName( const CRobotName& rhs );
    CRobotName & operator = ( const CRobotName& rhs );
};

#define RobotName CRobotName::GetInstance()

#endif // CRandomName_h__