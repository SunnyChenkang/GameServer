#include "eval_formula.h"

SS_NAMESPACE_BEGIN_DECL

CEvalFormula::CEvalFormula( void )
{
    
}

CEvalFormula::~CEvalFormula( void )
{
    
}

double CEvalFormula::Formula( NLMISC::CSString formula )
{
    double result = 0.f;
    m_EvalNumExpr.evalExpression( formula.c_str() , result , NULL );

    return result;
}

double CEvalFormula::Formula( NLMISC::CSString formula , double param0 )
{
    double result = 0.f;
    char   buffer[ BUFFER_MAX_LENGTH ] = {'\0'};

    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param0 );
    formula = formula.replace( "$a" , buffer );
    m_EvalNumExpr.evalExpression( formula.c_str() , result , NULL );

    return result;
}

double CEvalFormula::Formula( NLMISC::CSString formula , double param0 , double param1 )
{
    double result = 0.f;
    char   buffer[ BUFFER_MAX_LENGTH ] = { '\0' };

    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param0 );
    formula = formula.replace( "$a" , buffer );
    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param1 );
    formula = formula.replace( "$b" , buffer );
    m_EvalNumExpr.evalExpression( formula.c_str() , result , NULL );

    return result;
}

double CEvalFormula::Formula( NLMISC::CSString formula , double param0 , double param1 , double param2 )
{
    double result = 0.f;
    char   buffer[ BUFFER_MAX_LENGTH ] = { '\0' };

    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param0 );
    formula = formula.replace( "$a" , buffer );
    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param1 );
    formula = formula.replace( "$b" , buffer );
    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param2 );
    formula = formula.replace( "$c" , buffer );
    m_EvalNumExpr.evalExpression( formula.c_str() , result , NULL );

    return result;
}

double CEvalFormula::Formula( NLMISC::CSString formula , double param0 , double param1 , double param2 , double param3 )
{
    double result = 0.f;
    char   buffer[ BUFFER_MAX_LENGTH ] = { '\0' };

    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param0 );
    formula = formula.replace( "$a" , buffer );
    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param1 );
    formula = formula.replace( "$b" , buffer );
    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param2 );
    formula = formula.replace( "$c" , buffer );
    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param3 );
    formula = formula.replace( "$d" , buffer );
    m_EvalNumExpr.evalExpression( formula.c_str() , result , NULL );

    return result;
}

double CEvalFormula::Formula( NLMISC::CSString formula , double param0 , double param1 , double param2 , double param3 , double param4 )
{
    double result = 0.f;
    char   buffer[ BUFFER_MAX_LENGTH ] = { '\0' };

    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param0 );
    formula = formula.replace( "$a" , buffer );
    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param1 );
    formula = formula.replace( "$b" , buffer );
    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param2 );
    formula = formula.replace( "$c" , buffer );
    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param3 );
    formula = formula.replace( "$d" , buffer );
    NLMISC::smprintf( buffer , BUFFER_MAX_LENGTH , "%lf" , param4 );
    formula = formula.replace( "%e" , buffer );
    m_EvalNumExpr.evalExpression( formula.c_str() , result , NULL );

    return result;
}

SS_NAMESPACE_END_DECL
