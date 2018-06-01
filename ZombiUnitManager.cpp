#include "ZombiUnitManager.h"
#include "ZombiUnit.h"
#include "ZombiUnit1.h"
#include "ZombiUnit2.h"
#include "ZombiUnit3.h"
#include "ZombiUnit4.h"
#include "EnemyBoss1.h"
#include "EnemyBoss2.h"

ZombiUnitManager *ZombiUnitManager::m_this = nullptr;



ZombiUnitManager::ZombiUnitManager()
{
}


void ZombiUnitManager::Init()
{
	m_vecZombi1.reserve(100);
	m_vecZombi2.reserve(100);
	m_vecZombi3.reserve(100);
	m_vecZombi4.reserve(100);

	for (int i = 0; i < 100; i++)
	{
		ZombiUnit * Zombi = ZombiUnit1::createZombi1();
		Zombi->Init();
		Zombi->retain();
		m_vecZombi1.pushBack(Zombi);
	}

	for (int i = 0; i < 100; i++)
	{
		ZombiUnit * Zombi = ZombiUnit2::createZombi2();
		Zombi->Init();
		Zombi->retain();
		m_vecZombi2.pushBack(Zombi);
	}

	for (int i = 0; i < 100; i++)
	{
		ZombiUnit * Zombi = ZombiUnit3::createZombi3();
		Zombi->Init();
		Zombi->retain();
		m_vecZombi3.pushBack(Zombi);
	}

	for (int i = 0; i < 100; i++)
	{
		ZombiUnit * Zombi = ZombiUnit4::createZombi4();
		Zombi->Init();
		Zombi->retain();
		m_vecZombi4.pushBack(Zombi);
	}

	m_vecZombiBoss1 = EnemyBoss1::createBoss1();
	m_vecZombiBoss1->Init();
	m_vecZombiBoss1->retain();


	m_vecZombiBoss2 = EnemyBoss2::createBoss2();
	m_vecZombiBoss2->Init();
	m_vecZombiBoss2->retain();


	m_DieZombiCount = 0;
}



ZombiUnit * ZombiUnitManager::getZombiUnit(ZOMBITYPE ZombiType)
{
	switch (ZombiType)
	{
	case ZOMBI1:
	{
		ZombiUnit * unit = NULL;
		for (auto iter = m_vecZombi1.begin(); iter < m_vecZombi1.end(); iter++)
		{
			if ((*iter)->EnemyUnitLife())
			{
				unit = (*iter);
				break;
			}
		}

		if (unit == NULL)
		{
			int culcapaciti = m_vecZombi1.capacity();
			int capaciti = culcapaciti / 2;
			m_vecZombi1.reserve(m_vecZombi1.capacity() + m_vecZombi1.capacity() / 2);
			for (int i = 0; i < capaciti; i++)
			{
				ZombiUnit * Zombi = ZombiUnit1::createZombi1();
				Zombi->retain();
				Zombi->Init();
				m_vecZombi1.pushBack(Zombi);
			}
			unit = m_vecZombi1.at(culcapaciti);
		}
		m_listCulUnit.push_back(unit);
		return unit;
	}
	break;
	case ZOMBI2:
	{
		ZombiUnit * unit = NULL;
		for (auto iter = m_vecZombi2.begin(); iter < m_vecZombi2.end(); iter++)
		{
			if ((*iter)->EnemyUnitLife())
			{
				unit = (*iter);
				break;
			}
		}

		if (unit == NULL)
		{
			int culcapaciti = m_vecZombi2.capacity();
			int capaciti = culcapaciti / 2;
			m_vecZombi2.reserve(m_vecZombi2.capacity() + m_vecZombi2.capacity() / 2);
			for (int i = 0; i < capaciti; i++)
			{
				ZombiUnit * Zombi = ZombiUnit2::createZombi2();
				Zombi->retain();
				Zombi->Init();
				m_vecZombi2.pushBack(Zombi);
			}
			unit = m_vecZombi2.at(culcapaciti);
		}
		m_listCulUnit.push_back(unit);
		return unit;
	}
	break;
	case ZOMBI3:
	{
		ZombiUnit * unit = NULL;
		for (auto iter = m_vecZombi3.begin(); iter < m_vecZombi3.end(); iter++)
		{
			if ((*iter)->EnemyUnitLife())
			{
				unit = (*iter);
				break;
			}
		}

		if (unit == NULL)
		{
			int culcapaciti = m_vecZombi3.capacity();
			int capaciti = culcapaciti / 2;
			m_vecZombi3.reserve(m_vecZombi3.capacity() + m_vecZombi3.capacity() / 2);
			for (int i = 0; i < capaciti; i++)
			{
				ZombiUnit * Zombi = ZombiUnit3::createZombi3();
				Zombi->retain();
				Zombi->Init();
				m_vecZombi3.pushBack(Zombi);
			}
			unit = m_vecZombi3.at(culcapaciti);
		}
		m_listCulUnit.push_back(unit);
		return unit;
	}
	break;
	case ZOMBI4:
	{
		ZombiUnit * unit = NULL;
		for (auto iter = m_vecZombi4.begin(); iter < m_vecZombi4.end(); iter++)
		{
			if ((*iter)->EnemyUnitLife())
			{
				unit = (*iter);
				break;
			}
		}

		if (unit == NULL)
		{
			int culcapaciti = m_vecZombi4.capacity();
			int capaciti = culcapaciti / 2;
			m_vecZombi4.reserve(m_vecZombi4.capacity() + m_vecZombi4.capacity() / 2);
			for (int i = 0; i < capaciti; i++)
			{
				ZombiUnit * Zombi = ZombiUnit4::createZombi4();
				Zombi->retain();
				Zombi->Init();
				m_vecZombi4.pushBack(Zombi);
			}
			unit = m_vecZombi4.at(culcapaciti);
		}
		m_listCulUnit.push_back(unit);
		return unit;
	}
	break;
	case ZOMBIBOSS1:
	{
		m_listCulUnit.push_back(m_vecZombiBoss1);
		return m_vecZombiBoss1;
		break;
	}
	case ZOMBIBOSS2:
	{
		m_listCulUnit.push_back(m_vecZombiBoss2);
		return m_vecZombiBoss2;
		break;
	}
	default:
		break;
	}
}

std::list<ZombiUnit*> ZombiUnitManager::getCulVecUnit()
{
	m_listCulUnit.sort(stLISZombiUnitsort());
	return m_listCulUnit;
}

void ZombiUnitManager::eraseZombiUnit(ZombiUnit * unit)
{
	m_listCulUnit.remove(unit);
	m_DieZombiCount++;
}

void ZombiUnitManager::DrawNodeClear()
{
	for (auto iter = m_vecZombi1.begin(); iter < m_vecZombi1.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}
	for (auto iter = m_vecZombi2.begin(); iter < m_vecZombi2.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}
	for (auto iter = m_vecZombi3.begin(); iter < m_vecZombi3.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}
	for (auto iter = m_vecZombi4.begin(); iter < m_vecZombi4.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}

	m_vecZombiBoss1->DrawNodeClear();
}

void ZombiUnitManager::Destory()
{
	for (auto iter = m_vecZombi1.begin(); iter < m_vecZombi1.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	for (auto iter = m_vecZombi2.begin(); iter < m_vecZombi2.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	for (auto iter = m_vecZombi3.begin(); iter < m_vecZombi3.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	for (auto iter = m_vecZombi4.begin(); iter < m_vecZombi4.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	CC_SAFE_RELEASE(m_vecZombiBoss1);

	SAFE_DELETE(m_this);
}

ZombiUnitManager::~ZombiUnitManager()
{
}
