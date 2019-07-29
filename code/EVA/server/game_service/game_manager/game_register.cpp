#include "game_register.h"

GSE_NAMESPACE_BEGIN_DECL

void CGameRegister::LoadGameInfo( void )
{
    CConfigFile::CVar* pGameConfig = IService::getInstance()->ConfigFile.getVarPtr( "GameList" );
    if ( nullptr == pGameConfig ) {
        return;
    }
    m_GameList.clear();
    NLMISC::CSString  ServiceName  = IService::getInstance()->ConfigFile.getVar( "AESAliasName").asString();
    for ( auto It = pGameConfig->StrValues.begin(); It != pGameConfig->StrValues.end(); ++It )
    {
        CRecordGameInfo GameInfo;
        NLNET::TParsedCommandLine ParsedCommand;
        const TParsedCommandLine* pParseline1 = ParsedCommand.getParam( "GameName"  );
        const TParsedCommandLine* pParseline2 = ParsedCommand.getParam( "GameCount" );
        GameInfo.SetGameName( pParseline1->toString() );
        GameInfo.SetGameMaxCount( CSString( pParseline2->toString()).atoui() );
        GameInfo.SetServiceName( ServiceName );
        m_GameList.push_back( GameInfo );
    }
}

void CGameRegister::UpdateGameInfo( CSString GameName , sint32 IsAdd )
{
    for ( auto& It = m_GameList.begin(); It != m_GameList.end(); ++It )
    {
        if ( !(*It).GetGameName().compare( GameName ) ) {
            continue;
        }
        sint32 GameCurrCount = (*It).GetGameCurrCount();
        (*It).SetGameCurrCount( GameCurrCount + IsAdd);
        break;
    }
}

GSE_NAMESPACE_END_DECL