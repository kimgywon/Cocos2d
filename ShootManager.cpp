#include "ShootManager.h"
#include "Shoot.h"
#include "GameManager.h"
#include "Police3Bullet.h"
#include "Police4Bullet.h"
#include "Zombi2Bullet.h"
#include "Zombi4Bullet.h"

ShootManager * ShootManager::m_this = NULL;

ShootManager::ShootManager()
{
}

void ShootManager::Init()
{
	m_vecPolice3Bullet.reserve(40);
	m_vecPolice4Bullet.reserve(40);
	m_vecZombi2Bullet.reserve(40);
	m_vecZombi4Bullet.reserve(40);

	for (int i = 0; i < 40; i++)
	{
		Shoot * police = Police3Bullet::createBullet();
		police->Init();
		police->retain();
		m_vecPolice3Bullet.pushBack(police);
	}

	for (int i = 0; i < 40; i++)
	{
		Shoot * police = Police4Bullet::createBullet();
		police->Init();
		police->retain();
		m_vecPolice4Bullet.pushBack(police);
	}

	for (int i = 0; i < 40; i++)
	{
		Shoot * police = Zombi2Bullet::createBullet();
		police->Init();
		police->retain();
		m_vecZombi2Bullet.pushBack(police);
	}

	for (int i = 0; i < 40; i++)
	{
		Shoot * police = Zombi4Bullet::createBullet();
		police->Init();
		police->retain();
		m_vecZombi4Bullet.pushBack(police);
	}
}

Shoot * ShootManager::getPoliceBullet(POLICEBULLET Type)
{
	Shoot * shoot = NULL;

	switch (Type)
	{
	case POLICE3BULLET:
		for (auto iter = m_vecPolice3Bullet.begin(); iter < m_vecPolice3Bullet.end(); iter++)
		{
			if ((*iter)->BulletLife())
			{
				shoot = (*iter);
				break;
			}
		}

		if (shoot == NULL)
		{
			int culcapaciti = m_vecPolice3Bullet.capacity();
			int capaciti = culcapaciti / 2;
			m_vecPolice3Bullet.reserve(culcapaciti + capaciti);
			for (int i = 0; i < capaciti; i++)
			{
				Shoot * police = Police3Bullet::createBullet();
				police->Init();
				police->retain();
				m_vecPolice3Bullet.pushBack(police);
			}
			shoot = m_vecPolice3Bullet.at(culcapaciti);
		}

		m_listCulPoliceBullet.push_back(shoot);
		return shoot;
		break;
	case POLICE4BULLET:
		for (auto iter = m_vecPolice4Bullet.begin(); iter < m_vecPolice4Bullet.end(); iter++)
		{
			if ((*iter)->BulletLife())
			{
				shoot = (*iter);
				break;
			}
		}

		if (shoot == NULL)
		{
			int culcapaciti = m_vecPolice4Bullet.capacity();
			int capaciti = culcapaciti / 2;
			m_vecPolice4Bullet.reserve(culcapaciti + capaciti);
			for (int i = 0; i < capaciti; i++)
			{
				Shoot * police = Police3Bullet::createBullet();
				police->Init();
				police->retain();
				m_vecPolice4Bullet.pushBack(police);
			}
			shoot = m_vecPolice4Bullet.at(culcapaciti);
		}

		m_listCulPoliceBullet.push_back(shoot);
		return shoot;
		break;
	case ZOMBI2BULLET:
		for (auto iter = m_vecZombi2Bullet.begin(); iter < m_vecZombi2Bullet.end(); iter++)
		{
			if ((*iter)->BulletLife())
			{
				shoot = (*iter);
				break;
			}
		}

		if (shoot == NULL)
		{
			int culcapaciti = m_vecZombi2Bullet.capacity();
			int capaciti = culcapaciti / 2;
			m_vecZombi2Bullet.reserve(culcapaciti + capaciti);
			for (int i = 0; i < capaciti; i++)
			{
				Shoot * police = Zombi2Bullet::createBullet();
				police->Init();
				police->retain();
				m_vecZombi2Bullet.pushBack(police);
			}
			shoot = m_vecZombi2Bullet.at(culcapaciti);
		}
		m_listCulZombiBullet.push_back(shoot);

		return shoot;
		break;
	case ZOMBI4BULLET:
		for (auto iter = m_vecZombi4Bullet.begin(); iter < m_vecZombi4Bullet.end(); iter++)
		{
			if ((*iter)->BulletLife())
			{
				shoot = (*iter);
				break;
			}
		}

		if (shoot == NULL)
		{
			int culcapaciti = m_vecZombi4Bullet.capacity();
			int capaciti = culcapaciti / 2;
			m_vecZombi4Bullet.reserve(culcapaciti + capaciti);
			for (int i = 0; i < capaciti; i++)
			{
				Shoot * police = Zombi4Bullet::createBullet();
				police->Init();
				police->retain();
				m_vecZombi4Bullet.pushBack(police);
			}
			shoot = m_vecZombi4Bullet.at(culcapaciti);
		}
		m_listCulZombiBullet.push_back(shoot);

		return shoot;
		break;
	default:
		break;
	}
}

void ShootManager::erasePoliceBullet(Shoot * shoot)
{
	m_listCulPoliceBullet.remove(shoot);
}

void ShootManager::eraseZombiBullet(Shoot * shoot)
{
	m_listCulZombiBullet.remove(shoot);
}

std::list<Shoot*> ShootManager::getlistPoliceBullet()
{
	m_listCulPoliceBullet.sort(stLISTsort());
	return m_listCulPoliceBullet;
}

std::list<Shoot*> ShootManager::getlistZombiBullet()
{
	m_listCulZombiBullet.sort(stLISTZombiBulletsort());
	return m_listCulZombiBullet;
}

void ShootManager::Destory()
{
	for (auto iter = m_vecPolice3Bullet.begin(); iter < m_vecPolice3Bullet.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}


	for (auto iter = m_vecPolice4Bullet.begin(); iter < m_vecPolice4Bullet.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	for (auto iter = m_vecZombi2Bullet.begin(); iter < m_vecZombi2Bullet.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	for (auto iter = m_vecZombi4Bullet.begin(); iter < m_vecZombi4Bullet.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	CC_SAFE_DELETE(m_this);
}

void ShootManager::DrawNodeClear()
{
	for (auto iter = m_vecPolice3Bullet.begin(); iter < m_vecPolice3Bullet.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}


	for (auto iter = m_vecPolice4Bullet.begin(); iter < m_vecPolice4Bullet.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}

	for (auto iter = m_vecZombi2Bullet.begin(); iter < m_vecZombi2Bullet.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}

	for (auto iter = m_vecZombi4Bullet.begin(); iter < m_vecZombi4Bullet.end(); iter++)
	{
		(*iter)->DrawNodeClear();
	}
}

ShootManager::~ShootManager()
{

}
