#ifndef SS_TIME_VALUE_H_
#define SS_TIME_VALUE_H_

#include <server_share/common/common.h>
#include <time.h>

SS_NAMESPACE_BEGIN_DECL

class CTimeValue
{

    SS_PROPERTY( timeval , time , private );

public:
    uint32 const static ONE_SECOND_IN_USECS  = 1000000;                                         // 1秒 = 1000000微妙;
    uint32 const static ONE_MINUTE_IN_SECS   = 60;                                              // 1分 = 60秒;
    uint32 const static ONE_HOURS_IN_MINUTE  = 60;                                              // 1时 = 60分;
    uint32 const static ONE_HOURS_IN_SECS    = ( ONE_MINUTE_IN_SECS * ONE_HOURS_IN_MINUTE );    // 1时 = 60*60秒;
    uint32 const static ONE_DAY_IN_HOURS     = 24;                                              // 1天 = 24时;
    uint32 const static ONE_DAY_IN_SECS      = ( ONE_DAY_IN_HOURS * ONE_HOURS_IN_SECS );        // 1天 = 24*60*60秒;
    uint32 const static ONE_WEEK_IN_DAY      = 7;                                               // 1周 = 7天;
    uint32 const static ONE_WEEK_IN_SECS     = ( ONE_WEEK_IN_DAY * ONE_DAY_IN_SECS );           // 1周 = 7*24*60*60;

    friend bool operator > ( const CTimeValue& rhs1 , const CTimeValue& rhs2 );
    friend bool operator < ( const CTimeValue& rhs1 , const CTimeValue& rhs2 );
    friend bool operator >=( const CTimeValue& rhs1 , const CTimeValue& rhs2 );
    friend bool operator <=( const CTimeValue& rhs1 , const CTimeValue& rhs2 );
    friend bool operator ==( const CTimeValue& rhs1 , const CTimeValue& rhs2 );
    friend bool operator !=( const CTimeValue& rhs1 , const CTimeValue& rhs2 );

    friend CTimeValue operator - ( const CTimeValue& rhs1 , const CTimeValue& rhs2 );
    friend CTimeValue operator + ( const CTimeValue& rhs1 , const CTimeValue& rhs2 );

public:
    static const CTimeValue zero;
    static const CTimeValue max;

    CTimeValue( const CTimeValue& );
    explicit CTimeValue( uint32 sec = 0 , uint32 usec = 0 );
    explicit CTimeValue( const struct timeval& t );

    inline uint32 sec ( void ) const  { return this->m_time.tv_sec;  }
    inline void   sec ( uint32 sec )  { this->m_time.tv_sec = sec;   }
    inline uint32 usec( void ) const  { return this->m_time.tv_usec; }
    inline void   usec( uint32 usec ) { this->m_time.tv_usec = usec; }
    inline uint32 msec( void ) const  { return this->m_time.tv_sec * 1000 + this->m_time.tv_usec / 1000; }

    CTimeValue& operator += ( const CTimeValue& rhs );
    CTimeValue& operator -= ( const CTimeValue& rhs );

    // serial;
    void serial( NLMISC::IStream& s )
    {
        uint32 sec  = m_time.tv_sec;
        uint32 usec = m_time.tv_usec;
        s.serial( sec );
        s.serial( usec );
    }

private:
    void normalize( void );
};

inline bool IsSameWeek( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    tm tm1 , tm2;
    time_t t1 = rhs1.sec();
    time_t t2 = rhs2.sec();

    if ( abs( t1 - t2 ) > CTimeValue::ONE_WEEK_IN_SECS ){
         return false;
    }

    if ( rhs1 > rhs2 ) {
        std::swap( t1 , t2 );
    }

    #ifdef NL_OS_UNIX
    ::localtime_r(&t1, &tm1);
    ::localtime_r(&t2, &tm2);
    #else
    ::localtime_s( &tm1 , &t1 );
    ::localtime_s( &tm2 , &t2 );
    #endif

    if ( tm1.tm_wday  < tm2.tm_wday ) { return true; }
    if ( tm1.tm_wday == tm2.tm_wday ) { return tm1.tm_yday == tm2.tm_yday; }

    return false;
}

inline bool IsSameMonth( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    tm tm1 , tm2;
    time_t t1 = rhs1.sec();
    time_t t2 = rhs2.sec();

    #ifdef NL_OS_UNIX
    ::localtime_r(&t1, &tm1);
    ::localtime_r(&t2, &tm2);
    #else
    ::localtime_s( &tm1 , &t1 );
    ::localtime_s( &tm2 , &t2 );
    #endif

    if ( tm1.tm_year != tm2.tm_year ) return false;
    if ( tm1.tm_mon  != tm2.tm_mon  ) return false;

    return true;
}

inline bool IsSameDay( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    tm tm1 , tm2;
    time_t t1 = rhs1.sec();
    time_t t2 = rhs1.sec();

    #ifdef NL_OS_UNIX
    ::localtime_r(&t1, &tm1);
    ::localtime_r(&t2, &tm2);
    #else
    ::localtime_s( &tm1 , &t1 );
    ::localtime_s( &tm2 , &t2 );
    #endif

    if ( tm1.tm_year != tm2.tm_year ) return false;
    if ( tm1.tm_mon  != tm2.tm_mon  ) return false;
    if ( tm1.tm_mday != tm2.tm_mday ) return false;

    return true;
}

inline bool IsSameHour( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    tm tm1 , tm2;
    time_t t1 = rhs1.sec();
    time_t t2 = rhs2.sec();

    #ifdef NL_OS_UNIX
    ::localtime_r(&t1, &tm1);
    ::localtime_r(&t2, &tm2);
    #else
    ::localtime_s( &tm1 , &t1 );
    ::localtime_s( &tm2 , &t2 );
    #endif

    if ( tm1.tm_year != tm2.tm_year ) return false;
    if ( tm1.tm_mon  != tm2.tm_mon  ) return false;
    if ( tm1.tm_mday != tm2.tm_mday ) return false;
    if ( tm1.tm_hour != tm2.tm_hour ) return false;

    return true;
}

inline void GetZeroTime( const CTimeValue& rhs1, CTimeValue& rhs2 )
{
    sint32 ZeroTime = rhs1.sec() + (86400 - (rhs1.sec() + 28800) % 86400 );
    rhs2.sec( ZeroTime );
    rhs2.usec( 0 );
}

// 计算相差天数;
inline sint32 GetTimeSubDays( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    sint32 ZeroTime1 = rhs1.sec() + ( 86400 - (rhs1.sec() + 28800) % 86400 );
    sint32 ZeroTime2 = rhs2.sec() + ( 86400 - (rhs2.sec() + 28800) % 86400 );
    return ( ZeroTime2 - ZeroTime1 )/ 86400;
}

SS_NAMESPACE_END_DECL

#endif//SS_TIME_VALUE_H_