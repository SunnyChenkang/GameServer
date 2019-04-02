#include "time_value.h"

SS_NAMESPACE_BEGIN_DECL

CTimeValue::CTimeValue( uint32 sec /* = 0  */, uint32 usec /* = 0 */ )
{
    this->sec ( sec );
    this->usec( usec );
}

CTimeValue::CTimeValue( const struct timeval& t )
{
    this->sec ( t.tv_sec );
    this->usec( t.tv_usec );
}

CTimeValue::CTimeValue( const CTimeValue& rhs )
{
    this->sec ( rhs.sec() );
    this->usec( rhs.usec());
}

bool operator > ( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    if ( rhs1.sec() > rhs2.sec() ) return true;
    if ( rhs1.usec()> rhs2.usec()) return true;
    return false;
}

bool operator < ( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    return rhs2 > rhs1;
}

bool operator >= ( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    if ( rhs1.sec()  > rhs2.sec() ) return true;
    if ( rhs1.sec() == rhs2.sec() && rhs1.usec() >= rhs2.usec() ) return true;
    return false;
}

bool operator <= ( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    return rhs2 >= rhs1;
}

bool operator == ( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    return rhs1.sec() == rhs2.sec() && rhs1.usec() == rhs2.usec();
}

bool operator != ( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    return !( rhs1 == rhs2 );
}

CTimeValue operator - ( const CTimeValue& rhs1, const CTimeValue& rhs2 )
{
    CTimeValue TimeData( rhs1 );
    TimeData -= rhs2;
    return TimeData;
}

CTimeValue operator + ( const CTimeValue& rhs1 , const CTimeValue& rhs2 )
{
    CTimeValue TimeData( rhs1 );
    TimeData += rhs2;
    return TimeData;
}

CTimeValue& CTimeValue::operator -= (  const CTimeValue& rhs )
{
    this->sec ( this->sec() - rhs.sec() );
    this->usec( this->usec()- rhs.usec());
    this->normalize();
    return *this;
}

CTimeValue& CTimeValue::operator += (  const CTimeValue& rhs )
{
    this->sec ( this->sec()  + rhs.sec() );
    this->usec( this->usec() + rhs.usec());
    this->normalize();
    return *this;
}

void CTimeValue::normalize( void )
{
    while ( this->m_time.tv_usec >= 1000000 )
    {
        this->m_time.tv_sec     += 1;
        this->m_time.tv_usec    -= 1000000;
    }
    while ( this->m_time.tv_usec <= -1000000 )
    {
        this->m_time.tv_sec     -= 1;
        this->m_time.tv_usec    += 1000000;
    }
    if ( this->m_time.tv_sec >= 1 && this->m_time.tv_usec < 0 )
    {
         this->m_time.tv_sec -= 1;
         this->m_time.tv_usec+= 1000000;
    }
}

SS_NAMESPACE_END_DECL