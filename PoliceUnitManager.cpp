#include "PoliceUnitManager.h"
#include "Player.h"
#include "PopLayer.h"
#include "PoliceUnit.h"
#include "PoliceUnit1.h"
#include "PoliceUnit4.h"
#include "PoliceUnit2.h"
#include "PoliceUnit3.h"


PoliceUnitManager *PoliceUnitManager::m_this = nullptr;

PoliceUnitManager::PoliceUnitManager()
{
}


void PoliceUnitManager::Init(Player * player)
{
	m_Player = player;
	m_vecPolice1.reserve(100);
	m_vecPolice2.reserve(100);
	m_vecPolice3.reserve(100);
	m_vecPolice4.reserve(100);

	for (int i = 0; i < 100; i++)
	{
		PoliceUnit * police = PoliceUnit1::createPolice1();
		police->Init(m_Player);
		police->retain();
		m_vecPolice1.pushBack(police);
	}

	for (int i = 0; i < 100; i++)
	{
		PoliceUnit * police = PoliceUnit2::createPolice2();
		police->Init(m_Player);
		police->retain();
		m_vecPolice2.pushBack(police);
	}

	for (int i = 0; i < 100; i++)
	{
		PoliceUnit * police = PoliceUnit3::createPolice3();
		police->Init(m_Player);
		police->retain();
		m_vecPolice3.pushBack(police);
	}

	for (int i = 0; i < 100; i++)
	{
		PoliceUnit * police = PoliceUnit4::createPolice4();
		police->Init(m_Player);
		police->retain();
		m_vecPolice4.pushBack(police);
	}
}

PoliceUnit * PoliceUnitManager::getPoliceUnit(POLICETYPE PoliceType)
{
	switch (PoliceType)
	{
	case POLICE1:
	{
		PoliceUnit * unit = NULL;
		for (auto iter = m_vecPolice1.begin(); iter < m_vecPolice1.end(); iter++)
		{
			if ((*iter)->PoliceUnitLife())
			{
				unit = (*iter);
				break;
			}
		}

		if (unit == NULL)
		{
			int culcapaciti = m_vecPolice1.capacity();
			int capaciti = culcapaciti /2;
			m_vecPolice1.reserve(m_vecPolice1.capacity() + m_vecPolice1.capacity() / 2);
			for (int i = 0; i < capaciti; i++)
			{
				PoliceUnit * police = PoliceUnit1::createPolice1();
				police->retain();
				police->Init(m_Player);
				m_vecPolice1.pushBack(police);
			}
			unit = m_vecPolice1.at(culcapaciti);
		}
		m_listCulUnit.push_back(unit);
		return unit;
	}
		break;
	case POLICE2:
	{
		PoliceUnit * unit = NULL;
		for (auto iter = m_vecPolice2.begin(); iter < m_vecPolice2.end(); iter++)
		{
			if ((*iter)->PoliceUnitLife())
			{
				unit = (*iter);
				break;
			}
		}

		if (unit == NULL)
		{
			int culcapaciti = m_vecPolice2.capacity();
			int capaciti = culcapaciti / 2;
			m_vecPolice2.reserve(m_vecPolice2.capacity() + m_vecPolice2.capacity() / 2);
			for (int i = 0; i < capaciti; i++)
			{
				PoliceUnit * police = PoliceUnit2::createPolice2();
				police->retain();
				police->Init(m_Player);
				m_vecPolice2.pushBack(police);
			}
			unit = m_vecPolice2.at(culcapaciti);
		}

		m_listCulUnit.push_back(unit);
		return unit;
	}
		break;
	case POLICE3:
	{
		PoliceUnit * unit = NULL;
		for (auto iter = m_vecPolice3.begin(); iter < m_vecPolice3.end(); iter++)
		{
			if ((*iter)->PoliceUnitLife())
			{
				unit = (*iter);
				break;
			}
		}

		if (unit == NULL)
		{
			int culcapaciti = m_vecPolice3.capacity();
			int capaciti = culcapaciti / 2;
			m_vecPolice3.reserve(m_vecPolice3.capacity() + m_vecPolice3.capacity() / 2);
			for (int i = 0; i < capaciti; i++)
			{
				PoliceUnit * police = PoliceUnit3::createPolice3();
				police->retain();
				police->Init(m_Player);
				m_vecPolice3.pushBack(police);
			}
			unit = m_vecPolice3.at(culcapaciti);
		}

		m_listCulUnit.push_back(unit);
		return unit;
	}
		break;
	case POLICE4:
	{
		PoliceUnit * unit = NULL;
		for (auto iter = m_vecPolice4.begin(); iter < m_vecPolice4.end(); iter++)
		{
			if ((*iter)->PoliceUnitLife())
			{
				unit = (*iter);
				break;
			}
		}

		if (unit == NULL)
		{
			int culcapaciti = m_vecPolice4.capacity();
			int capaciti = culcapaciti / 2;
			m_vecPolice4.reserve(m_vecPolice4.capacity() + m_vecPolice4.capacity() / 2);
			for (int i = 0; i < capaciti; i++)
			{
				PoliceUnit * police = PoliceUnit4::createPolice4();
				police->retain();
				police->Init(m_Player);
				m_vecPolice4.pushBack(police);
			}
			unit = m_vecPolice4.at(culcapaciti);
		}

		m_listCulUnit.push_back(unit);
		return unit;
	}
		break;
	default:
		break;
	}
}

std::list<PoliceUnit*> PoliceUnitManager::getCulVecUnit()
{
	m_listCulUnit.sort(stLISUnitsort());
	return m_listCulUnit;
}

void PoliceUnitManager::erasePoliceUnit(PoliceUnit * unit)
{
	m_listCulUnit.remove(unit);
}


void PoliceUnitManager::DrawNodeClear()
{
	for (auto iter = m_vecPolice1.begin(); iter < m_vecPolice1.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}

	for (auto iter = m_vecPolice2.begin(); iter < m_vecPolice2.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}

	for (auto iter = m_vecPolice3.begin(); iter < m_vecPolice3.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}

	for (auto iter = m_vecPolice4.begin(); iter < m_vecPolice4.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}
}

void PoliceUnitManager::Destory()
{
	for (auto iter = m_vecPolice1.begin(); iter < m_vecPolice1.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	for (auto iter = m_vecPolice2.begin(); iter < m_vecPolice2.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	for (auto iter = m_vecPolice3.begin(); iter < m_vecPolice3.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	for (auto iter = m_vecPolice4.begin(); iter < m_vecPolice4.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	SAFE_DELETE(m_this);
}

PoliceUnitManager::~PoliceUnitManager()
{
}
