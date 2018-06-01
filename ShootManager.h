#pragma once
#include "cocos2d.h"
#include <list>
#include "Shoot.h"

USING_NS_CC;

struct stLISTsort
{
	bool operator() (const Shoot *pObject1, const Shoot *pObject2) const
	{
		if (pObject1->getPosition() < pObject2->getPosition())
			return FALSE;

		return TRUE;
	}
};

struct stLISTZombiBulletsort
{
	bool operator() (const Shoot *pObject1, const Shoot *pObject2) const
	{
		if (pObject1->getPosition() < pObject2->getPosition())
			return TRUE;

		return FALSE;
	}
};

enum POLICEBULLET
{
	POLICE3BULLET,
	POLICE4BULLET,
	ZOMBI2BULLET,
	ZOMBI4BULLET,
};


class ShootManager
{
	Vector<Shoot *>									m_vecPolice3Bullet;
	Vector<Shoot *>									m_vecPolice4Bullet;
	Vector<Shoot *>									m_vecZombi2Bullet;
	Vector<Shoot *>									m_vecZombi4Bullet;

	static ShootManager *					m_this;
	std::list<Shoot *>								m_listCulPoliceBullet;
	std::list<Shoot *>								m_listCulZombiBullet;
public:
	ShootManager();
	static ShootManager*		 getInstance()
	{
		if (m_this == NULL)
		{
			m_this = new ShootManager();
		}

		return m_this;
	}

	void Init();

	Shoot *	getPoliceBullet(POLICEBULLET Type);
	void erasePoliceBullet(Shoot * shoot);
	void eraseZombiBullet(Shoot * shoot);
	std::list<Shoot *> getlistPoliceBullet();
	std::list<Shoot *> getlistZombiBullet();
	void Destory();

	void DrawNodeClear();
	~ShootManager();
};

