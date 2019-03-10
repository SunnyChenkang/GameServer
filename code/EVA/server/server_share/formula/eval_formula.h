#ifndef SS_EVAL_FORMULA_H_
#define SS_EVAL_FORMULA_H_

#include <server_share/common/common.h>

SS_NAMESPACE_BEGIN_DECL

class CEvalFormula : public NLMISC::CSingleton< CEvalFormula >
{
public:
    CEvalFormula( void );
   ~CEvalFormula( void );

    double Formula( NLMISC::CSString );
    double Formula( NLMISC::CSString , double );
    double Formula( NLMISC::CSString , double , double );
    double Formula( NLMISC::CSString , double , double , double );
    double Formula( NLMISC::CSString , double , double , double , double );
    double Formula( NLMISC::CSString , double , double , double , double , double );

    SS_PROPERTY( NLMISC::CEvalNumExpr , EvalNumExpr , private );

    enum
    {
        BUFFER_MAX_LENGTH = 256,
    };
};

SS_NAMESPACE_END_DECL

#define EvalFormula SS::CEvalFormula::instance()

#endif // SS_EVAL_FORMULA_H_;