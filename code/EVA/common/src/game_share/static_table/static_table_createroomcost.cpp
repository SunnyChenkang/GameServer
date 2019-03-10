#include "static_table_createroomcost.h"
#include <nel/misc/file.h>
#include <nel/misc/i_xml.h>

using namespace NLMISC;

CreateRoomCostConfig::CreateRoomCostConfig( void )
{

}

CreateRoomCostConfig::~CreateRoomCostConfig( void )
{

}

void CreateRoomCostConfig::ResetData( void )
{
    m_CreatePrivateConsumeItem.clear();
}

CreatePrivateConsumeItem* CreateRoomCostConfig::GetCreateConsumeItem( uint ID )
{
    std::map<uint,CreatePrivateConsumeItem>::iterator it = m_CreatePrivateConsumeItem.find( ID );
    if ( it == m_CreatePrivateConsumeItem.end() ) { return NULL; }
    return &it->second;
}

bool CreateRoomCostConfig::LoadConfig( void )
{
    try
    {
        ResetData();
    }
    catch ( ... ) {
    }
    std::string path = NLMISC::CPath::lookup("GameConsumePrototype.xml");
    CIFile file;
    CIXml xml;

    if ( !file.open( path ) ) {
        return false;
    }
    if ( !xml.init( file ) ) {
        return false;
    }
    xmlNodePtr rootPtr = xml.getRootNode();
    if ( NULL == rootPtr ) {
        return false;
    }

    // 创建私房消耗;
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "create_room" );
        if ( NULL != pRoomData )
        {
            for ( ; NULL != pRoomData; pRoomData = xml.getNextChildNode( pRoomData , "create_room" ) )
            {
                CreatePrivateConsumeItem ConsumeItem;
                ConsumeItem.ID              = CIXml::getIntProperty( pRoomData , "id" , 0 );
                ConsumeItem.GameCount       = CIXml::getIntProperty( pRoomData , "game_count", 0 );
                ConsumeItem.ConsumeItemNum  = CIXml::getIntProperty( pRoomData , "consume_item_num" , 0 );
                ConsumeItem.GoldItemID      = CIXml::getIntProperty( pRoomData , "item_id" , 0 );
                ConsumeItem.SilverItemID    = 0;
                ConsumeItem.RatioValue      = 100;
                ConsumeItem.AllIntegral     = 1;
                ConsumeItem.OwnerIntegral   = 1;
                m_CreatePrivateConsumeItem[ConsumeItem.ID] = ConsumeItem;
            }
        }
    }
    return true;
}
