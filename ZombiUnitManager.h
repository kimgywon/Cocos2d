#pragma once
#include "cocos2d.h"
#include "GameManager.h"
#include <list>
#include "ZombiUnit.h"

USING_NS_CC;

struct stLISZombiUnitsort
{
	bool operator() (const ZombiUnit *pObject1, const ZombiUnit *pObject2) const
	{
		if (pObject1->getEnemyPosition() < pObject2->getEnemyPosition())
			return TRUE;

		return FALSE;
	}
};

enum ZOMBITYPE
{
	ZOMBI1,
	ZOMBI2,
	ZOMBI3,
	ZOMBI4,
	ZOMBIBOSS1,
	ZOMBIBOSS2,
};

class ZombiUnitManager
{
	ZombiUnitManager();
	static ZombiUnitManager *						m_this;

	Vector<ZombiUnit *>										m_vecZombi1;
	Vector<ZombiUnit *>										m_vecZombi2;
	Vector<ZombiUnit *>										m_vecZombi3;
	Vector<ZombiUnit *>										m_vecZombi4;
	ZombiUnit *														m_vecZombiBoss1;
	ZombiUnit *														m_vecZombiBoss2;
	std::list<ZombiUnit *>									m_listCulUnit;

	int																		m_DieZombiCount;
public:
	static ZombiUnitManager*		 getInstance()
	{
		if (m_this == NULL)
		{
			m_this = new ZombiUnitManager();
		}

		return m_this;
	}

	void Init();

	ZombiUnit * getZombiUnit(ZOMBITYPE ZombiType);
	std::list<ZombiUnit *> getCulVecUnit();
	void eraseZombiUnit(ZombiUnit * unit);

	inline int getZombiCount() { return m_DieZombiCount; }
	void DrawNodeClear();
	void Destory();
	~ZombiUnitManager();
};

