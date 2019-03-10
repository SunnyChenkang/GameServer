#include "static_table_qualify_key.h"
#include <nel/misc/file.h>
#include <nel/misc/i_xml.h>

using namespace NLMISC;

CQualifyKeyConfig::CQualifyKeyConfig( void )
{

}

CQualifyKeyConfig::~CQualifyKeyConfig( void )
{

}

void CQualifyKeyConfig::ResetData( void )
{
	m_QyNomalKey.clear();
	m_QyUpKey.clear();
}

QyNormalkeyData* CQualifyKeyConfig::GetQyNormalKey(uint32 unIndex  )
{
	TNormalMapData::iterator NomalIter = m_QyNomalKey.find( unIndex );
	if ( NomalIter == m_QyNomalKey.end() ) 
    {
        return NULL;
    }
	return &(NomalIter->second);
}

QyUpkeyData* CQualifyKeyConfig::GetQyUpKeyDataByIndex(uint32 unIndex  )
{
	TUpMapData::iterator UpIter = m_QyUpKey.find( unIndex );
	if ( UpIter == m_QyUpKey.end() ) 
	{
		return NULL;
	}
	return &(UpIter->second);
}

QyUpkeyData* CQualifyKeyConfig::GetQyUpKeyDataByKey(NLMISC::CSString& strKey)
{
	TUpMapData::iterator UpIter = m_QyUpKey.begin();
	for (;UpIter!=m_QyUpKey.end();++UpIter)
	{
		if (UpIter->second.strOwnKey==strKey)
		{
			return &(UpIter->second);
		}
	}
	return NULL;
}

bool CQualifyKeyConfig::CheckQyScoreCondition(NLMISC::CSString& strKey,uint32 unGoldeScore,uint32 unSilverScore,uint32 unRedScore,uint32 unBlueScore)
{
	QyUpkeyData* pUpData=GetQyUpKeyDataByKey(strKey);
	if (pUpData)
	{
		uint32 unTotalScore=unGoldeScore+unSilverScore+unRedScore+unBlueScore;
		if (pUpData->totalRelation==1) //  总分或的关系
		{
			if (unTotalScore>=pUpData->totalScore)
			{
				return true;
			}
			if (pUpData->scoreRelation==1) //  各个积分的关系
			{
				if (unGoldeScore>=pUpData->goldScore)
				{
					return true;
				}
				if (unSilverScore>=pUpData->silverScore)
				{
					return true;
				}
				if (unRedScore>=pUpData->redScore)
				{
					return true;
				}
				if (unBlueScore>=pUpData->blueScore)
				{
					return true;
				}
			}
			else
			{
				if (unGoldeScore>=pUpData->goldScore)
				{
					if (unSilverScore>=pUpData->silverScore)
					{
						if (unRedScore>=pUpData->redScore)
						{
							if (unBlueScore>=pUpData->blueScore)
							{
								return true;
							}
						}
					}
				}
			}
		}
		else
		{
			if (unTotalScore>=pUpData->totalScore)
			{
				if (pUpData->scoreRelation==1) //  各个积分的关系
				{
					if (unGoldeScore>=pUpData->goldScore)
					{
						return true;
					}
					if (unSilverScore>=pUpData->silverScore)
					{
						return true;
					}
					if (unRedScore>=pUpData->redScore)
					{
						return true;
					}
					if (unBlueScore>=pUpData->blueScore)
					{
						return true;
					}
				}
				else
				{
					if (unGoldeScore>=pUpData->goldScore)
					{
						if (unSilverScore>=pUpData->silverScore)
						{
							if (unRedScore>=pUpData->redScore)
							{
								if (unBlueScore>=pUpData->blueScore)
								{
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}



bool CQualifyKeyConfig::LoadConfig( void )
{
	try
	{
		ResetData();
	}
	catch ( ... ) {
	}
	std::string path = NLMISC::CPath::lookup("QualifyQykey.xml");
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
		xmlNodePtr pRootKey = xml.getFirstChildNode( rootPtr , "normal_key" );
		if ( NULL != pRootKey )
		{
			xmlNodePtr pKey = xml.getFirstChildNode( pRootKey , "key" );
			for ( ; NULL != pKey; pKey = xml.getNextChildNode( pKey , "key" ) )
			{
				QyNormalkeyData KeyData;
				KeyData.unIndex=CIXml::getIntProperty( pKey , "Index" , 0 );
				KeyData.strOwnKey=CIXml::getStringProperty( pKey , "own_key" , "0" );
				KeyData.strUpKey=CIXml::getStringProperty( pKey , "up_key" , "0" );
				TNormalMapData::iterator mapKeyIter= m_QyNomalKey.find(KeyData.unIndex);
				if (mapKeyIter==m_QyNomalKey.end())
				{
				m_QyNomalKey.insert(std::make_pair(KeyData.unIndex,KeyData));
				}
			}
		}
		xmlNodePtr pUpKey = xml.getFirstChildNode( pRootKey , "up_key" );
		if ( NULL != pUpKey )
		{
			xmlNodePtr pKey = xml.getFirstChildNode( pUpKey , "key" );
			for ( ; NULL != pKey; pKey = xml.getNextChildNode( pKey , "key" ) )
			{
				QyUpkeyData upKeyData;
				upKeyData.unIndex=CIXml::getIntProperty( pKey , "Index" , 0 );
				upKeyData.strOwnKey=CIXml::getStringProperty( pKey , "own_key" , "0" );
				upKeyData.strUpKey=CIXml::getStringProperty( pKey , "up_key" , "0" );
				upKeyData.totalRelation=CIXml::getIntProperty( pKey , "total_relation" , 1 );
				upKeyData.scoreRelation=CIXml::getIntProperty( pKey , "score_relation" , 1 );
				upKeyData.totalScore=CIXml::getIntProperty(pKey, "total_condition" , 0);
				upKeyData.goldScore=CIXml::getIntProperty(pKey, "gold_condition" , 0);
				upKeyData.silverScore=CIXml::getIntProperty(pKey, "silver_condition" , 0);
				upKeyData.redScore=CIXml::getIntProperty(pKey, "red_condition" , 0);
				upKeyData.blueScore=CIXml::getIntProperty(pKey, "blue_condition" , 0);
				upKeyData.rankCondition=CIXml::getIntProperty(pKey,"rank_condition",10);
				TUpMapData::iterator mapKeyIter= m_QyUpKey.find(upKeyData.unIndex);
				if (mapKeyIter==m_QyUpKey.end())
				{
					m_QyUpKey.insert(std::make_pair(upKeyData.unIndex,upKeyData));
				}
			}
		}
	}
	return true;
}

uint32 CQualifyKeyConfig::GetQyRankCondition(NLMISC::CSString& strContent)
{
	TUpMapData::iterator UpIter=m_QyUpKey.begin();
	for (;UpIter!=m_QyUpKey.end();++UpIter)
	{
		CSString strOwn(UpIter->second.strOwnKey);
		if (strOwn==strContent)
		{
			return UpIter->second.rankCondition;
		}
	}
	return 0;
}
