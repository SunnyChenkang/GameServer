#include "CPlayerItem.h"
#include <game_share/define_attrib.pb.h>
#include <game_share/static_table/static_table_mgr.h>

CPlayerItem::CPlayerItem( void )
{
    m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
    m_ItemData.clear();
}

CPlayerItem::~CPlayerItem( void )
{
}

void CPlayerItem::OnSavePlayerItem( MsgItemCont& data )
{

    for ( int i = 0 ; i < data.msg_item_size(); ++i )
    {
        const MsgItem& msg_item = data.msg_item( i );

        DB_RECORD::CRecordItem ItemEnity;
        ItemEnity.RecordItemData.item_id        = msg_item.item_id();
        ItemEnity.RecordItemData.template_id    = msg_item.template_id();
        ItemEnity.RecordItemData.num            = msg_item.num();
        ItemEnity.RecordItemData.con_type       = msg_item.con_type();

        for ( int j = 0 ; j < msg_item.itemparam_size(); ++j )
        {
            const MsgItemParam& msg_item_param = msg_item.itemparam( j );

            DB_RECORD::CRecordItemParam ItemParam;
            ItemParam.type  = msg_item_param.type();
            ItemParam.value = msg_item_param.value();
            ItemEnity.RecordItemParam.push_back( ItemParam );
        }

        m_ItemData.insert( std::make_pair( msg_item.item_id() , ItemEnity ) );
    }
}

DB_RECORD::CRecordItem* CPlayerItem::GetItem(  DEF::TEMPLATE_ID id )
{
    for ( DB_RECORD::TRecordItem::iterator it = m_ItemData.begin() ; it != m_ItemData.end(); ++it )
    {
        if ( id == it->second.RecordItemData.template_id )
        {
            return &( it->second );
        }
    }

    return NULL;
}

DB_RECORD::CRecordItem* CPlayerItem::GetRandomItem( void )
{
    DB_RECORD::TRecordItem::iterator it = m_ItemData.begin();

    // 距离;
    int dist = std::distance( it , m_ItemData.end() );
    if ( dist <= 0 )
        return NULL;

    std::advance( it , m_Random.rand( dist - 1 ) );

    return &( it->second );
}

DB_RECORD::CRecordItem* CPlayerItem::GetSellItem( void )
{
    if ( m_ItemData.empty() )
        return NULL;

    for ( DB_RECORD::TRecordItem::iterator it = m_ItemData.begin(); it != m_ItemData.end() ; ++it )
    {
        if ( it->second.RecordItemData.is_delete() )
        {
            continue;
        }

        if ( it->second.RecordItemData.num <= 0 )
        {
            it->second.RecordItemData.set_delete();
            continue;
        }

        return &( it->second );
    }

    return NULL;
}

void CPlayerItem::OnUpdateUseItem( MsgUseItemUpdate& data )
{
    std::vector< MsgItem > list_item;

    for ( int index = 0 ; index < data.item_info_size(); ++index ){
        list_item.push_back( data.item_info( index ) );
    }

    OnUpdateItem( list_item );
}

void CPlayerItem::OnUpdateSellItem( MsgSellItemUpdate& data )
{
    std::vector< MsgItem > list_item;

    for ( int index = 0 ; index < data.item_info_size(); ++index ) {
        list_item.push_back( data.item_info( index ) );
    }

    OnUpdateItem( list_item );
}

void CPlayerItem::OnUpdateBuyItem( MsgStoreBuyItemInfo& data )
{
    std::vector< MsgItem > list_item;

    for ( int index = 0 ; index < data.msg_item_size(); ++index ) {
        list_item.push_back( data.msg_item( index ) );
    }

    OnUpdateItem( list_item );
}

void CPlayerItem::OnUpdateMailItem( MsgGainReward& data )
{
    std::vector< MsgItem > list_item;

    for ( int index = 0 ; index < data.msg_item_size(); ++index ) {
        list_item.push_back( data.msg_item( index ) );
    }

    OnUpdateItem( list_item );
}

void CPlayerItem::OnUpdateMissionRewardItem( MsgMissionReward& data )
{
    std::vector< MsgItem > list_item;

    for ( int index = 0 ; index < data.msg_item_size(); ++index ) {
        list_item.push_back( data.msg_item( index ) );
    }

    OnUpdateItem( list_item );
}


void CPlayerItem::OnDeleteItem( DEF::TEMPLATE_ID id )
{
    for ( DB_RECORD::TRecordItem::iterator it = m_ItemData.begin() ; it != m_ItemData.end(); )
    {
        if ( id == it->second.RecordItemData.template_id )
        {
            m_ItemData.erase( it++ );
            continue;
        }
        else
        {
            it++;
        }
    }
}

void CPlayerItem::OnDeleteItem( DEF::ITEM_ID id )
{
    DB_RECORD::TRecordItem::iterator it = m_ItemData.find( id );

    if ( it != m_ItemData.end() )
    {
        m_ItemData.erase( it );
    }
}

void CPlayerItem::OnUpdateItem( std::vector< MsgItem >& data )
{
    for ( int index = 0 ; index < data.size(); ++index )
    {
        const MsgItem& msg_item = data[ index ];

        DB_RECORD::TRecordItem::iterator it = m_ItemData.find( msg_item.item_id() );

        // 堆叠数为0;
        if ( msg_item.num() == 0 )
        {
            m_ItemData.erase( msg_item.item_id() );
        }
        else
        {
            if ( it == m_ItemData.end() )
            {
                // 新道具;
                DB_RECORD::CRecordItem ItemEntity;
                ItemEntity.RecordItemData.item_id       = msg_item.item_id();
                ItemEntity.RecordItemData.template_id   = msg_item.template_id();
                ItemEntity.RecordItemData.num           = msg_item.num();
                ItemEntity.RecordItemData.con_type      = msg_item.con_type();
                m_ItemData.insert( std::make_pair( msg_item.item_id() , ItemEntity ) );
                // 属性表;
            }
            else
            {
                // 仅更新堆叠数;
                it->second.RecordItemData.num = msg_item.num();
            }
        }
    }
}

//
//DB_RECORD::CRecordItem* CPlayerItem::GetConsumeItem( void )
//{
//    for ( DB_RECORD::TRecordItem::iterator it = m_ItemData.begin(); it != m_ItemData.end(); ++it )
//    {
//        StaticData::RecordBase* pUseItemData = StaticTableMgr.GetUseItemData( it->second.RecordItemData.template_id );
//        if ( NULL == pUseItemData )
//            continue;
//
//        if ( it->second.RecordItemData.is_delete() )
//        {
//            continue;
//        }
//
//        if ( it->second.RecordItemData.num <= 0 )
//        {
//            it->second.RecordItemData.set_delete();
//            continue;
//        }
//
//        return &(it->second);
//    }
//
//    return NULL;
//}
//
//DB_RECORD::CRecordItem* CPlayerItem::GetUseExpItem( void )
//{
//    for ( DB_RECORD::TRecordItem::iterator it = m_ItemData.begin(); it != m_ItemData.end(); ++it )
//    {
//        StaticData::RecordBase* pUseItemData = StaticTableMgr.GetUseItemData( it->second.RecordItemData.template_id );
//        if ( NULL == pUseItemData )
//            continue;
//
//        if ( pUseItemData->getAttribInt( ATTRIB_TYPE::ITEM_USE_TYPE_INT , 0 ) != 2 )
//        {
//            continue;
//        }
//
//        if ( it->second.RecordItemData.is_delete() )
//        {
//            continue;
//        }
//
//        if ( it->second.RecordItemData.num <= 0 )
//        {
//            it->second.RecordItemData.set_delete();
//            continue;
//        }
//
//        return &(it->second);
//    }
//
//    return NULL;
//}
//
//void CPlayerItem::OnUpdatCheckinItem( MsgReward& data )
//{
//    std::vector< MsgItem > list_item;
//
//    for ( int index = 0 ; index < data.items_size(); ++index ) {
//        list_item.push_back( data.items( index ) );
//    }
//
//    OnUpdateItem( list_item );
//}
//
//void CPlayerItem::OnUpdateRandomShopItem( MsgBuyItemResult& data )
//{
//    std::vector< MsgItem > list_item;
//
//    for( int index = 0 ; index < data.item_info_size() ; ++index ){
//        list_item.push_back( data.item_info( index ) );
//    }
//
//    OnUpdateItem( list_item );
//}
//
//void CPlayerItem::OnUpdateRandomCardItem( MsgCardAward& data )
//{
//    std::vector< MsgItem > list_item;
//
//    for ( int index = 0 ; index < data.item_info_size(); ++index ) {
//        list_item.push_back( data.item_info( index ) );
//    }
//
//    OnUpdateItem( list_item );
//}
//
//void CPlayerItem::OnUpdateItemPvE( MsgPvELeaveRes& data )
//{
//    std::vector< MsgItem > list_item;
//
//    for ( int index = 0 ; index < data.item_size(); ++index ) {
//        list_item.push_back( data.item( index ) );
//    }
//
//    OnUpdateItem( list_item );
//}
//
//void CPlayerItem::OnUpdateItemPvP(  MsgPvPLeaveRes& data )
//{
//    std::vector< MsgItem > list_item;
//
//    for ( int index = 0 ; index < data.item_size(); ++index ) {
//        list_item.push_back( data.item( index ) );
//    }
//
//    OnUpdateItem( list_item );
//}
//
//void CPlayerItem::OnUpdateDupDropItem( MsgBattleEndRes& data )
//{
//    if( data.items_size() <= 0 )
//        return;
//
//    std::vector< MsgItem > list_item;
//
//    for ( int index = 0 ; index < data.items_size() ; ++ index ) {
//        OnDeleteItem( data.items( index ).template_id() );
//        list_item.push_back( data.items( index ) );
//    }
//
//    OnUpdateItem( list_item );
//}
//
//void CPlayerItem::OnUpdateHeroUpLevelItem( MsgUpdateHero& data )
//{
//    if ( data.item_info_size() <= 0 )
//        return;
//
//    std::vector< MsgItem > list_item;
//
//    for ( int index = 0 ; index < data.item_info_size(); ++index ){
//        OnDeleteItem( data.item_info( index ).template_id() );
//        list_item.push_back( data.item_info( index ) );
//    }
//
//    OnUpdateItem( list_item );
//}
//
//void CPlayerItem::OnUpdateHeroExpUp( MsgUseExpUpdate& data )
//{
//    if( data.item_info_size() <= 0 )
//        return;
//
//    std::vector< MsgItem > list_item;
//
//    for ( int index = 0; index < data.item_info_size(); ++index ) {
//        OnDeleteItem( data.item_info( index ).template_id() );
//        list_item.push_back( data.item_info( index ) );
//    }
//
//    OnUpdateItem( list_item );
//}
//
//void CPlayerItem::OnUpdateHeroEquip( MsgUpdateMeta& data )
//{
//    if ( data.item_info_size() <= 0 )
//        return;
//
//    std::vector< MsgItem > list_item;
//
//    for ( int index = 0 ; index < data.item_info_size(); ++index ) {
//        OnDeleteItem( data.item_info( index ).template_id() );
//        list_item.push_back( data.item_info( index ) );
//    }
//
//    OnUpdateItem( list_item );
//}
//
//void CPlayerItem::OnUpdateHeroSkillLevel( MsgHeroSkillUpRes& data )
//{
//    if ( data.item_info_size() <= 0 )
//        return;
//
//    std::vector< MsgItem > list_item;
//
//    for ( int index = 0 ; index < data.item_info_size(); ++index ) {
//        OnDeleteItem( data.item_info( index ).template_id() );
//        list_item.push_back( data.item_info( index ) );
//    }
//
//    OnUpdateItem( list_item );
//}
