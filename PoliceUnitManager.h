#pragma once
#include "cocos2d.h"
#include "GameManager.h"
#include <list>
#include "PoliceUnit.h"

USING_NS_CC;

struct stLISUnitsort
{
	bool operator() (const PoliceUnit *pObject1, const PoliceUnit *pObject2) const
	{
		if (pObject1->getUnitPosition() < pObject2->getUnitPosition())
			return FALSE;

		return TRUE;
	}
};

enum POLICETYPE
{
	POLICE1,
	POLICE2,
	POLICE3,
	POLICE4,
};

class Player;

class PoliceUnitManager 
{
	PoliceUnitManager();
	static PoliceUnitManager *						m_this;
	Player *																m_Player;
	Vector<PoliceUnit *>										m_vecPolice1;
	Vector<PoliceUnit *>										m_vecPolice2;
	Vector<PoliceUnit *>										m_vecPolice3;
	Vector<PoliceUnit *>										m_vecPolice4;

	std::list<PoliceUnit *>									m_listCulUnit;
public:
	static PoliceUnitManager*		 getInstance()
	{
		if (m_this == NULL)
		{
			m_this = new PoliceUnitManager();
		}

		return m_this;
	}

	void Init(Player * player);

	PoliceUnit * getPoliceUnit(POLICETYPE PoliceType);
	std::list<PoliceUnit *> getCulVecUnit();
	void erasePoliceUnit(PoliceUnit * unit);


	void DrawNodeClear();
	void Destory();
	~PoliceUnitManager();
};

