
#ifndef GAME_SHARE_STATIC_TABLE_VERI_H
#define GAME_SHARE_STATIC_TABLE_VERI_H

#include <game_share/game_def.h>

struct QyNormalkeyData
{
	uint32 unIndex;
    std::string strOwnKey;
    std::string strUpKey;
	QyNormalkeyData()
	{
		unIndex=0;
		strOwnKey="";
		strUpKey="";
	}
};

struct QyUpkeyData
{
	uint32 unIndex;
	NLMISC::CSString strOwnKey;
	NLMISC::CSString strUpKey;
	uint32 totalRelation;  //  总分与各个分的关系(1是或0是并)  
	uint32 totalScore; //  大师分的条件
	uint32 scoreRelation; //  各个分的关系(1是或0是并)
	uint32 goldScore; //  金分
	uint32 silverScore; //  银分
	uint32 redScore; //  红分
	uint32 blueScore; //  蓝分
	uint32 rankCondition;

	QyUpkeyData()
	{
		unIndex=0;
		strOwnKey="0";
		strUpKey="0";
		totalRelation=1; //  默认或的关系
		totalScore=0;
		scoreRelation=1;
		goldScore=0;
		silverScore=0;
		redScore=0;
		blueScore=0;
		rankCondition=100;
	}
};

class CQualifyKeyConfig : public NLMISC::CSingleton<CQualifyKeyConfig>
{
public:
	CQualifyKeyConfig( void );
	~CQualifyKeyConfig( void );
	//   重置数据;
	void ResetData( void );
	//   加载表;
	bool LoadConfig( void );
	//  获取普通棋院码
	QyNormalkeyData* GetQyNormalKey( uint32 );
	//  获取复赛棋院码
	QyUpkeyData*         GetQyUpKeyDataByIndex( uint32 );
	QyUpkeyData*          GetQyUpKeyDataByKey(NLMISC::CSString& strKey);
	uint32  GetQyRankCondition(NLMISC::CSString& strContent);
	bool CheckQyScoreCondition(NLMISC::CSString& strKey,uint32 unGoldeScore,uint32 unSilverScore,uint32 unRedScore,uint32 unBlueScore);
	typedef   std::map<uint32, QyNormalkeyData >    TNormalMapData;
	typedef   std::map<uint32, QyUpkeyData >           TUpMapData;

private:
	TNormalMapData             m_QyNomalKey;
	TUpMapData                    m_QyUpKey;
};

#define QualifyKeyConfig CQualifyKeyConfig::instance()

#endif