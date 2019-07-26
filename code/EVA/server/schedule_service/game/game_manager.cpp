#include "game_manager.h"

SSE_NAMESPACE_BEGIN_DECL

CGameManager::CGameManager( void )
{
    m_GameTable.clear();
    m_HallTable.clear();
}

CGameManager::~CGameManager( void )
{

}

void CGameManager::LoadGameInfo( TServiceId& ServiceID )
{
    this->RemoveGameInfo( ServiceID );
    NLMISC::CConfigFile::CVar* pGameConfig = NLNET::IService::getInstance()->ConfigFile.getVarPtr("");
    if ( nullptr == pGameConfig )
    {
        nlinfo( " load game info fails service id : " , ServiceID.get() );
        return;
    }
    for ( auto It = pGameConfig->StrValues.begin(); It != pGameConfig->StrValues.end(); ++It )
    {
        NLNET::TParsedCommandLine ParsedCommand;
        ParsedCommand.parseParamList( *It );
        const TParsedCommandLine * pParseLine1 = ParsedCommand.getParam("");
        const TParsedCommandLine * pParseLine2 = ParsedCommand.getParam("");
        const TParsedCommandLine * pParseLine3 = ParsedCommand.getParam("");
        CGameInfoPtr GameInfoPtr = std::make_shared< CGameInfo >();
        GameInfoPtr->SetGameName( pParseLine1->toString() );
        GameInfoPtr->SetGameServiceID( NLNET::TServiceId( pParseLine2->toString() ));
        GameInfoPtr->SetGameMaxCount( NLMISC::CSString(pParseLine3->toString()).atoui() );
        m_GameTable.push_back( GameInfoPtr );
    }
}

void CGameManager::LoadHallInfo( void )
{
    m_HallTable.clear();
    NLMISC::CConfigFile::CVar* pHallConfig = NLNET::IService::getInstance()->ConfigFile.getVarPtr( "" );
    if ( nullptr == pHallConfig )
    {
        nlinfo( " load hall info fails ... " );
        return;
    }
    for ( auto It = pHallConfig->StrValues.begin(); It != pHallConfig->StrValues.end(); ++It )
    {
        NLNET::TParsedCommandLine ParsedCommand;
        ParsedCommand.parseParamList( *It );
        const TParsedCommandLine * pParsedLine1 = ParsedCommand.getParam("");
        const TParsedCommandLine * pParsedLine2 = ParsedCommand.getParam("");
        const TParsedCommandLine * pParsedLine3 = ParsedCommand.getParam("");
        CHallInfoPtr HallInfoPtr = std::make_shared< CHallInfo >();
        HallInfoPtr->SetHallName( pParsedLine1->toString() );
        HallInfoPtr->SetHallServiceID( NLNET::TServiceId( pParsedLine2->toString() ) );
        HallInfoPtr->SetRoleMaxCount ( NLMISC::CSString( pParsedLine3->toString() ).atoui() );
        m_HallTable.push_back( HallInfoPtr );
    }
}

void CGameManager::UpdateGameInfo( TServiceId& ServiceID , CSString& GameName , uint32 GameCount)
{
    for ( auto Element : m_GameTable )
    {
        if ( Element->GetGameServiceID() != ServiceID ) continue;
        if ( Element->GetGameName() != GameName )       continue;
        Element->SetGameCurrCount( GameCount );
    }
}

void CGameManager::UpdateHallInfo( TServiceId& ServiceID , CSString& GameName , uint32 RoleCount )
{
    for ( auto Element : m_HallTable )
    {
        if ( Element->GetHallServiceID() != ServiceID ) continue;
        if ( Element->GetHallName() != GameName )       continue;
        Element->SetRoleCurrCount( RoleCount );
    }
}

void CGameManager::RemoveGameInfo( TServiceId& ServiceID )
{
    for ( auto It = m_GameTable.begin(); It != m_GameTable.end() ; )
    {
        if ( (*It)->GetGameServiceID() == ServiceID ) {
            m_GameTable.erase( It++ );
            continue;
        }
        ++It;
    }
}

void CGameManager::RemoveHallInfo( TServiceId& ServiceID )
{
    for ( auto It = m_HallTable.begin(); It != m_HallTable.end(); )
    {
        if ( (*It)->GetHallServiceID() == ServiceID ) {
            m_HallTable.erase( It++ );
            continue;
        }
        ++It;
    }
}

CGameInfoPtr CGameManager::GetGameInfoPtr( CSString GameName )
{
    for ( auto It = m_GameTable.begin(); It != m_GameTable.end(); ++It )
    {
        if ( !(*It)->GetGameName().compare( GameName ) ) { continue; }
        if ( (*It)->IsRoleFull() ) { continue; }
        return (*It);
    }
    return nullptr;
}

CHallInfoPtr CGameManager::GetHallInfoPtr( void )
{
    for ( auto It = m_HallTable.begin(); It != m_HallTable.end(); ++It )
    {
        if ( (*It)->IsHallFull() ) { continue; }
        return (*It);
    }
    return nullptr;
}

SSE_NAMESPACE_END_DECL