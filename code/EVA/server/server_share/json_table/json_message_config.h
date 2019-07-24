#ifndef SS_JSON_MESSAGE_CONFIG_H_
#define SS_JSON_MESSAGE_CONFIG_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

class CJsonMessageCell;
typedef std::shared_ptr< CJsonMessageCell > CJsonMessageCellPtr;

class CJsonMessageCell : public CJsonBase
{
    SS_PROPERTY( NLMISC::CSString               , Name          , private );    /// 消息名字;
    SS_PROPERTY( NLMISC::CSString               , Desc          , private );    /// 消息描述;
    SS_PROPERTY( CJsonArray<NLMISC::CSString>   , Format        , public  );    /// 消息字段;
    SS_PROPERTY( CJsonArray<NLMISC::CSString>   , SendToService , public  );    /// 转发进程;

    PARSE_VALUE_BEGIN

    JsonParseBegin   ( JsonValue );
    JsonParseToString( m_Name );
    JsonParseToString( m_Desc );
    JsonParseToClass ( m_Format );
    JsonParseToClass ( m_SendToService );
    JsonParseEnd();

    PARSE_VALUE_END
};

class CJsonMessageConfig : public CJsonBase
{
    PARSE_VALUE_BEGIN

    JsonParseBegin( JsonValue );
    CJsonMessageCellPtr MessageCellPtr = std::make_shared< CJsonMessageCell >();
    MessageCellPtr->ParseJson( Values );
    m_JsonStringArray.insert(std::make_pair( MessageCellPtr->GetName() , MessageCellPtr ) );
    JsonParseEnd();

    PARSE_VALUE_END
};

SS_NAMESPACE_END_DECL

#endif // SS_JSON_FES_MESSAGE_H_;