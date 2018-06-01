#include "beanManager.h"
#include "GameManager.h"
#include <string.h> 
beanManager *beanManager::m_this = nullptr;


beanManager::beanManager()
{
}


void beanManager::Init()
{
	this->LoadMapBean();
	this->LoadUnitBean();
	this->LoadUpgradeBean();
	this->LoadPlayerBean();
	this->LoadPlayerUpgradeBean();
	this->LoadZombiBean();
	this->LoadZombiZenBean();
}

void beanManager::LoadMapBean()
{
	int pMapCount = 9;
	char Ctemp[256];
	char str[256];

	FILE * f;
	f = fopen("txt/MapInfo.csv", "r");
	fgets(Ctemp, sizeof(Ctemp), f);  //처음 필요없는 설명 줄뺴기

	int num;
	for (int i = 0; i < pMapCount; i++)
	{
		MapBean * bean = new MapBean();

		fscanf(f, "%d", &num);
		bean->setMapCount(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setMapClear(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setStarCount(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setClearTime(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setMapImplement(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setQuestTime(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setQuestGold1(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setQuestGold2(num);
		fgets(Ctemp, sizeof(Ctemp), f);
		Ctemp[strlen(Ctemp) - 1] = '\0';

		for (int i = 0; i < strlen(Ctemp); i++)
		{
				str[i] = Ctemp[i + 1];
		}
		bean->setTip(str);

		m_vecMapBean.push_back(bean);
	}

	fclose(f);
}

void beanManager::SaveMapBean()
{
	int pMapCount = 9;
	char Ctemp[256];

	FILE * f;
	f = fopen("txt/MapInfo.csv", "w");
	fprintf(f, "%s\n", "위치,클리어,별,시간,구현,보상시간,보상1,보상2,도움말");

	int num;

	for (auto iter = m_vecMapBean.begin(); iter < m_vecMapBean.end(); iter++)
	{
		num = (*iter)->getMapCount();
		fprintf(f, "%d,", num);

		num = (*iter)->getMapClear();
		fprintf(f, "%d,", num);

		num = (*iter)->getStarCount();
		fprintf(f, "%d,", num);

		num = (*iter)->getClearTime();
		fprintf(f, "%d,", num);

		num = (*iter)->getMapImplement();
		fprintf(f, "%d,", num);

		num = (*iter)->getQuestTime();
		fprintf(f, "%d,", num);

		num = (*iter)->getQuestGold1();
		fprintf(f, "%d,", num);

		num = (*iter)->getQuestGold2();
		fprintf(f, "%d,", num);

		strcpy(Ctemp, (*iter)->getTip());
		fprintf(f, "%s", Ctemp);

		fprintf(f, "\n");
		SAFE_DELETE((*iter));
	}

	fclose(f);
}

void beanManager::LoadUnitBean()
{
	int pMapCount = 4;
	char Ctemp[256];

	FILE * f;
	f = fopen("txt/UnitInfo.csv", "r");
	fgets(Ctemp, sizeof(Ctemp), f);  //처음 필요없는 설명 줄뺴기

	int num;
	for (int i = 0; i < pMapCount; i++)
	{
		UnitBean * bean = new UnitBean();

		fscanf(f, "%d", &num);
		bean->setUnitNum(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setUpgradeCount(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setAttackDamage(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setMoveSpeed(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setHelth(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setDefense(num);
		fseek(f, 1L, SEEK_CUR);

		m_vecUnitBean.push_back(bean);
	}

	fclose(f);
}

void beanManager::SaveUnitBean()
{
	int pMapCount = 4;
	char Ctemp[256];

	FILE * f;
	f = fopen("txt/UnitInfo.csv", "w");
	fprintf(f, "%s\n", "유닛번호,강화,공격력,이동속도,체력,방어력");

	int num;

	for (auto iter = m_vecUnitBean.begin(); iter < m_vecUnitBean.end(); iter++)
	{
		num = (*iter)->getUnitNum();
		fprintf(f, "%d,", num);

		num = (*iter)->getUpgradCount();
		fprintf(f, "%d,", num);

		num = (*iter)->getAttackDamage();
		fprintf(f, "%d,", num);

		num = (*iter)->getMoveSpeed();
		fprintf(f, "%d,", num);

		num = (*iter)->getHelth();
		fprintf(f, "%d,", num);

		num = (*iter)->getDefence();
		fprintf(f, "%d", num);

		fprintf(f, "\n");

		SAFE_DELETE((*iter));
	}

	fclose(f);
}

void beanManager::LoadUpgradeBean()
{
	int pMapCount = 20;
	char Ctemp[256];

	for (int j = 0; j < 4; j++)
	{
		FILE * f;
		sprintf(Ctemp, "txt/UpgradRoce%d.csv", j);
		f = fopen(Ctemp, "r");
		fgets(Ctemp, sizeof(Ctemp), f);  //처음 필요없는 설명 줄뺴기
		std::vector<UpgradeBean *>vecUpgradeBean;

		int num;
		for (int i = 0; i < pMapCount; i++)
		{
			UpgradeBean * bean = new UpgradeBean();

			fscanf(f, "%d", &num);
			bean->setUpgradePrice(num);
			fseek(f, 1L, SEEK_CUR);

			fscanf(f, "%d", &num);
			bean->setAttackDamage(num);
			fseek(f, 1L, SEEK_CUR);

			fscanf(f, "%d", &num);
			bean->setMoveSpeed(num);
			fseek(f, 1L, SEEK_CUR);

			fscanf(f, "%d", &num);
			bean->setHelth(num);
			fseek(f, 1L, SEEK_CUR);

			fscanf(f, "%d", &num);
			bean->setDefense(num);
			fseek(f, 1L, SEEK_CUR);

			vecUpgradeBean.push_back(bean);
		}
		m_vecUpgradeBean.push_back(vecUpgradeBean);
		fclose(f);
	}
}

void beanManager::SaveUpgradeBean()
{
	int pMapCount = 20;
	char Ctemp[256];
	int count = 0;
	for (auto iter2 = m_vecUpgradeBean.begin(); iter2 < m_vecUpgradeBean.end(); iter2++, count++)
	{
		FILE * f;
		sprintf(Ctemp, "txt/UpgradRoce%d.csv", count);
		f = fopen(Ctemp, "w");
		fprintf(f, "%s\n", "강화가격,공격,스피드,체력,방어력");

		int num;
		std::vector<UpgradeBean *> vecUpgradeBean = (*iter2);
		for (auto iter = vecUpgradeBean.begin(); iter < vecUpgradeBean.end(); iter++)
		{
			num = (*iter)->getUpgradPrice();
			fprintf(f, "%d,", num);

			num = (*iter)->getAttackDamage();
			fprintf(f, "%d,", num);

			num = (*iter)->getMoveSpeed();
			fprintf(f, "%d,", num);

			num = (*iter)->getHelth();
			fprintf(f, "%d,", num);

			num = (*iter)->getDefence();
			fprintf(f, "%d,", num);

			fprintf(f, "\n");

			SAFE_DELETE((*iter));
		}

		fclose(f);
	}
}

void beanManager::LoadPlayerBean()
{
	char Ctemp[100];

	FILE * f;
	f = fopen("txt/PlayerInfo.csv", "r");
	//fscanf(f, "%s", Ctemp);  //처음 필요없는 설명 줄뺴기
	fgets(Ctemp, sizeof(Ctemp), f);
	int num;

	m_playerBean = new PlayerBean();

	fscanf(f, "%d", &num);
	m_playerBean->setPlayerMoney(num);
	fseek(f, 1L, SEEK_CUR);

	fscanf(f, "%d", &num);
	m_playerBean->setPlayerHp(num);
	fseek(f, 1L, SEEK_CUR);

	fscanf(f, "%d", &num);
	m_playerBean->setPlayerMana(num);
	fseek(f, 1L, SEEK_CUR);

	fscanf(f, "%d", &num);
	m_playerBean->setPlayerEnegy(num);
	fseek(f, 1L, SEEK_CUR);

	fscanf(f, "%d", &num);
	m_playerBean->setPlayerBlessAtteck(num);
	fseek(f, 1L, SEEK_CUR);

	fscanf(f, "%d", &num);
	m_playerBean->setPlayerBlessDefence(num);
	fseek(f, 1L, SEEK_CUR);

	fscanf(f, "%d", &num);
	m_playerBean->setPlayerBlessMoveSpeed(num);
	fseek(f, 1L, SEEK_CUR);

	fscanf(f, "%d", &num);
	m_playerBean->setPlayerMagicSize(num);
	fclose(f);
}

void beanManager::SavePlayerBean()
{
	char Ctemp[256];

	FILE * f;
	f = fopen("txt/PlayerInfo.csv", "w");
	fprintf(f, "%s\n", "소지금,체력,마나,애너지바,버프공격력,버프방어력,버프속도,버프크기");

	int num;

	num = m_playerBean->getPlayerMoney();
	fprintf(f, "%d,", num);

	num = m_playerBean->getPlayerHp();
	fprintf(f, "%d,", num);

	num = m_playerBean->getPlayerMana();
	fprintf(f, "%d,", num);

	num = m_playerBean->getPlayerEnegy();
	fprintf(f, "%d,", num);

	num = m_playerBean->getPlayerBlessAtteck();
	fprintf(f, "%d,", num);

	num = m_playerBean->getPlayerBlessDefence();
	fprintf(f, "%d,", num);

	num = m_playerBean->getPlayerBlessMoveSpeed();
	fprintf(f, "%d,", num);

	num = m_playerBean->getPlayerMagicSize();
	fprintf(f, "%d", num);
	SAFE_DELETE(m_playerBean);


	fclose(f);
}

void beanManager::LoadPlayerUpgradeBean()
{
	int pMapCount = 5;
	char Ctemp[100];

	FILE * f;
	f = fopen("txt/PlayerUpgradeInfo.csv", "r");
	fgets(Ctemp, sizeof(Ctemp), f);

	int num;
	float num2;
	for (int i = 0; i < pMapCount; i++)
	{
		PlayerUpgradeInfo * m_playerBean = new PlayerUpgradeInfo();

		fscanf(f, "%d", &num);
		m_playerBean->setUpgradeCount(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		m_playerBean->setPlayerHp(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		m_playerBean->setPlayerMana(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		m_playerBean->setPlayerEnegy(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		m_playerBean->setPlayerBlessAtteck(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		m_playerBean->setPlayerBlessDefence(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		m_playerBean->setPlayerBlessMoveSpeed(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%f", &num2);
		m_playerBean->setPlayerMagicSize(num2);
		fseek(f, 1L, SEEK_CUR);

		m_vecPlayerUpgradeBean.push_back(m_playerBean);

	}
	fclose(f);
}

void beanManager::SavePlayerUpgradeBean()
{
	char Ctemp[256];

	FILE * f;
	f = fopen("txt/PlayerUpgradeInfo.csv", "w");
	fprintf(f, "%s\n", "강화,체력,마나,에너지,버프공격력,버프방어력,버프스피드,버프크기");

	int num;
	float num2;

	for (auto iter = m_vecPlayerUpgradeBean.begin(); iter < m_vecPlayerUpgradeBean.end(); iter++)
	{
		num =(*iter)->getUpgradeCount();
		fprintf(f, "%d,", num);

		num = (*iter)->getPlayerHp();
		fprintf(f, "%d,", num);

		num = (*iter)->getPlayerMana();
		fprintf(f, "%d,", num);

		num = (*iter)->getPlayerEnegy();
		fprintf(f, "%d,", num);

		num = (*iter)->getPlayerBlessAtteck();
		fprintf(f, "%d,", num);

		num = (*iter)->getPlayerBlessDefence();
		fprintf(f, "%d,", num);

		num = (*iter)->getPlayerBlessMoveSpeed();
		fprintf(f, "%d,", num);

		num2 = (*iter)->getPlayerMagicSize();
		fprintf(f, "%f,", num2);

		fprintf(f, "\n");
		SAFE_DELETE((*iter));
	}

	fclose(f);
}

void beanManager::LoadZombiBean()
{
	int pMapCount = 6;
	char Ctemp[256];

	FILE * f;
	f = fopen("txt/ZombiInfo.csv", "r");
	fgets(Ctemp, sizeof(Ctemp), f);

	int num;
	for (int i = 0; i < pMapCount; i++)
	{
		ZombiBean * bean = new ZombiBean();

		fscanf(f, "%d", &num);
		bean->setUnitNum(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setAttackDamage(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setMoveSpeed(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setHelth(num);
		fseek(f, 1L, SEEK_CUR);

		fscanf(f, "%d", &num);
		bean->setDefense(num);
		fseek(f, 1L, SEEK_CUR);

		m_vecZombiBean.push_back(bean);
	}

	fclose(f);
}

void beanManager::SaveZombiBean()
{
	int pMapCount = 6;
	char Ctemp[256];

	FILE * f;
	f = fopen("txt/ZombiInfo.csv", "w");
	fprintf(f, "%s\n", "유닛번호,공격력,이동속도,체력,방어력");

	int num;

	for (auto iter = m_vecZombiBean.begin(); iter < m_vecZombiBean.end(); iter++)
	{
		num = (*iter)->getUnitNum();
		fprintf(f, "%d,", num);

		num = (*iter)->getAttackDamage();
		fprintf(f, "%d,", num);

		num = (*iter)->getMoveSpeed();
		fprintf(f, "%d,", num);

		num = (*iter)->getHelth();
		fprintf(f, "%d,", num);

		num = (*iter)->getDefence();
		fprintf(f, "%d,", num);

		fprintf(f, "\n");

		SAFE_DELETE((*iter));
	}

	fclose(f);
}

void beanManager::LoadZombiZenBean()
{
	int pMapCount = 60;
	char Ctemp[256];

	for (int j = 0; j < 2; j++)
	{
		FILE * f;
		sprintf(Ctemp, "txt/UnitZen%d.csv", j);
		f = fopen(Ctemp, "r");
		fgets(Ctemp, sizeof(Ctemp), f);  //처음 필요없는 설명 줄뺴기
		std::vector<ZombiZenBean *>vecUpgradeBean;

		int num;
		for (int i = 0; i < pMapCount; i++)
		{
			ZombiZenBean * bean = new ZombiZenBean();

			fscanf(f, "%d", &num);
			bean->setUnit1Zen(num);
			fseek(f, 1L, SEEK_CUR);

			fscanf(f, "%d", &num);
			bean->setUnit2Zen(num);
			fseek(f, 1L, SEEK_CUR);

			fscanf(f, "%d", &num);
			bean->setBossZen(num);
			fseek(f, 1L, SEEK_CUR);

			vecUpgradeBean.push_back(bean);
		}
		m_vecZombiZenBean.push_back(vecUpgradeBean);
		fclose(f);
	}
}

void beanManager::SaveZombiZenBean()
{
	int pMapCount = 20;
	char Ctemp[256];
	int count = 0;
	for (auto iter2 = m_vecZombiZenBean.begin(); iter2 < m_vecZombiZenBean.end(); iter2++, count++)
	{
		FILE * f;
		sprintf(Ctemp, "txt/UpgradRoce%d.csv", count);
		f = fopen(Ctemp, "w");
		fprintf(f, "%s\n", "유닛1,유닛2,보스");

		int num;
		std::vector<ZombiZenBean *>vecUpgradeBean = (*iter2);
		for (auto iter = vecUpgradeBean.begin(); iter < vecUpgradeBean.end(); iter++)
		{
			num = (*iter)->getUnit1Zen();
			fprintf(f, "%d,", num);

			num = (*iter)->getUnit2Zen();
			fprintf(f, "%d,", num);

			num = (*iter)->getBossZen();
			fprintf(f, "%d,", num);


			fprintf(f, "\n");

			SAFE_DELETE((*iter));
		}

		fclose(f);
	}
}

void beanManager::Destory()
{
	this->SaveMapBean();
	this->SaveUnitBean();
	this->SaveUpgradeBean();
	this->SavePlayerBean();
	this->SavePlayerUpgradeBean();
	this->SaveZombiBean();
	this->SaveZombiZenBean();
	SAFE_DELETE(m_this);
}

beanManager::~beanManager()
{

}
 