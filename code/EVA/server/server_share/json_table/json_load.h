#ifndef SS_JSON_LOAD_H_
#define SS_JSON_LOAD_H_

#include <server_share/common/common.h>
#include "json_fes_message.h"

SS_NAMESPACE_BEGIN_DECL

class CJsonLoad : public NLMISC::CSingleton< CJsonLoad >
{
public:
    CJsonLoad( void ){ };
   ~CJsonLoad( void ){ };

    //   º”‘ÿ»´≤ø≈‰÷√;
    void JsonLoadTable( void );

    SS_PROPERTY( CJsonFesMessage , FesMessage , public );
};

SS_NAMESPACE_END_DECL

#define JsonLoad SS::CJsonLoad::instance()
#define JsonFesMessage JsonLoad.m_FesMessage


#endif // SS_JSON_LOAD_H_