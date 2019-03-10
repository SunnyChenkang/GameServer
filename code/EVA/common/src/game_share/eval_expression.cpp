#include "eval_expression.h"
#include <nel/misc/string_common.h>
#include <static_table/static_table_mgr.h>

using namespace NLMISC;

CEvalExpr* CEvalExpr::Instance = NULL;

double CEvalExpr::Eval( NLMISC::CSString expression )
{
    double result = 0;

    try
    {
        CSString formula = StaticTableMgr.GetFormula(expression);
        m_EvalExpr.evalExpression(formula.c_str(), result, NULL);
    }
    catch (FormulaNotFound e)
    {
    }

    return result;
}

double CEvalExpr::Eval( NLMISC::CSString expression, double param )
{
    double result = 0;

    try
    {
        CSString formula = StaticTableMgr.GetFormula(expression);
        result = Formula(formula, param);
    }
    catch (FormulaNotFound e)
    {
    }

    return result;
}

double CEvalExpr::Eval( NLMISC::CSString expression, double param0, double param1 )
{
    double result = 0;

    try
    {
        smprintf( m_StrParam, ParamMaxLength, "%lf", param0 );
        CSString formula = StaticTableMgr.GetFormula(expression);
        m_Expr = formula.replace("$a", m_StrParam);

        smprintf( m_StrParam, ParamMaxLength, "%lf", param1 );
        m_Expr = m_Expr.replace("$b", m_StrParam);

        m_EvalExpr.evalExpression(m_Expr.c_str(), result, NULL);
    }
    catch (FormulaNotFound e)
    {
    }

    return result;
}

double CEvalExpr::Eval( NLMISC::CSString expression, double param0, double param1, double param2 )
{
    double result = 0;

    try
    {
        smprintf( m_StrParam, ParamMaxLength, "%lf", param0 );
        CSString formula = StaticTableMgr.GetFormula(expression);
        m_Expr = formula.replace("$a", m_StrParam);

        smprintf( m_StrParam, ParamMaxLength, "%lf", param1 );
        m_Expr = m_Expr.replace("$b", m_StrParam);

        smprintf( m_StrParam, ParamMaxLength, "%lf", param2 );
        m_Expr = m_Expr.replace("$c", m_StrParam);

        m_EvalExpr.evalExpression(m_Expr.c_str(), result, NULL);
    }
    catch (FormulaNotFound e)
    {
    }

    return result;
}

double CEvalExpr::Eval( NLMISC::CSString expression, double param0, double param1 , double param2 , double param3 , double param4 , double param5 , double param6 )
{
    double result = 0.f;

    try
    {
        smprintf( m_StrParam , ParamMaxLength , "%1f" , param0 );
        CSString formula = StaticTableMgr.GetFormula(expression);
        m_Expr = formula.replace( "$a" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param1 );
        m_Expr = m_Expr.replace( "$b" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param2 );
        m_Expr = m_Expr.replace( "$c" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param3 );
        m_Expr = m_Expr.replace( "$d" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param4 );
        m_Expr = m_Expr.replace( "$e" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param5 );
        m_Expr = m_Expr.replace( "$f" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param6);
        m_Expr = m_Expr.replace( "$g" , m_StrParam );

        m_EvalExpr.evalExpression(m_Expr.c_str(), result, NULL);
    }
    catch (FormulaNotFound e)
    {
    }

    return result;
}

double CEvalExpr::Eval( NLMISC::CSString expression, double param0, double param1 , double param2 , double param3 , double param4 , double param5 , double param6 , double param7 , double param8 )
{
    double result = 0.f;

    try
    {
        smprintf( m_StrParam , ParamMaxLength , "%1f" , param0 );
        CSString formula = StaticTableMgr.GetFormula(expression);
        m_Expr = formula.replace( "$a" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param1 );
        m_Expr = m_Expr.replace( "$b" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param2 );
        m_Expr = m_Expr.replace( "$c" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param3 );
        m_Expr = m_Expr.replace( "$d" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param4 );
        m_Expr = m_Expr.replace( "$e" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param5 );
        m_Expr = m_Expr.replace( "$f" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param6);
        m_Expr = m_Expr.replace( "$g" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param7);
        m_Expr = m_Expr.replace( "$h" , m_StrParam );

        smprintf( m_StrParam , ParamMaxLength , "%1f" , param8);
        m_Expr = m_Expr.replace( "$i" , m_StrParam );

        m_EvalExpr.evalExpression(m_Expr.c_str(), result, NULL);
    }
    catch (FormulaNotFound e)
    {
    }

    return result;
}

double CEvalExpr::Formula( NLMISC::CSString formula, double param )
{
    double result = 0;

    smprintf( m_StrParam, ParamMaxLength, "%lf", param );
    m_Expr = formula.replace("$a", m_StrParam);
    m_EvalExpr.evalExpression(m_Expr.c_str(), result, NULL);

    return result;
}


