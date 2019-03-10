#ifndef SERVER_SHARED_I18N_H_
#define SERVER_SHARED_I18N_H_

#include <server_share/common/common.h>

SS_NAMESPACE_BEGIN_DECL

#define CI18N_BUFFER_SIZE 512

class CI18n : public NLMISC::CSingleton< CI18n >
{
public:
    CI18n( void );
   ~CI18n( void ) { }

public:
   const char*       GetString( const char* );
   NLMISC::CSString  Format( const char* , ... );

   SS_PROPERTY( NLMISC::CSString , Content  , private );
   SS_PROPERTY( NLMISC::CSString , Format   , private );
};

#define I18N CI18n::instance()

#define I18N_P0( format ) I18N.GetString( format )
#define I18N_P1( format , param0 ) I18N.Format( I18N.GetString( format ) , param0 )
#define I18N_P2( format , param0 , param1 ) I18N.Format( I18N.GetString( format ) , param0 , param1 )
#define I18N_P3( format , param0 , param1 , param2 ) I18N.Format( I18N.GetString( format ) , param0 , param1 , param2 )
#define I18N_P4( format , param0 , param1 , param2 , param3 ) I18N.Format( I18N.GetString( format ) , param0 , param1 , param2 ,.param3 )
#define I18N_P5( format , param0 , param1 , param2 , param3 , param4 ) I18N.Format( I18N.GetString( format ) , param0 , param1 , param2 , param3 , param4 )
#define I18N_P6( format , param0 , param1 , param2 , param3 , param4 , param5 ) I18N.Format( I18N.GetString( format ) , param0 , param1 , param2 , param3 , param4 , param5 )
#define I18N_P7( format , param0 , param1 , param2 , param3 , param4 , param5 , param6 ) I18N.Format( I18N.GetString( format ) , param0 , param1 , param2 , param3 , param4 , param5 , param6 )

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_I18N_H_;