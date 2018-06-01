#pragma once
#include <stdio.h>
#include "MapBean.h"
#include "UnitBean.h"
#include "UpgradeBean.h"
#include "PlayerBean.h"
#include "PlayerUpgradeInfo.h"
#include "ZombiBean.h"
#include "ZombiZenBean.h"
#include <vector>

class beanManager
{
	beanManager();
	static beanManager*										m_this;
	std::vector<MapBean *>									m_vecMapBean;
	std::vector<UnitBean *>									m_vecUnitBean;
//	std::vector<UpgradeBean *>							m_vecUpgradeBean;
	std::vector<	std::vector<UpgradeBean *>>	m_vecUpgradeBean;
	PlayerBean *														m_playerBean;
	std::vector<PlayerUpgradeInfo *>				m_vecPlayerUpgradeBean;
	std::vector<ZombiBean *>								m_vecZombiBean;
	std::vector<	std::vector<ZombiZenBean *>>	m_vecZombiZenBean;
public:
	static beanManager*		 getInstance()
	{
		if (m_this == NULL)
			m_this = new beanManager();

		return m_this;
	}

	void	 Init();

	void LoadMapBean();
	void SaveMapBean();
	inline 	std::vector<MapBean *> getMapBean() { return m_vecMapBean; }

	void LoadUnitBean();
	void SaveUnitBean();
	inline 	std::vector<UnitBean *>	 getUnitBean() { return m_vecUnitBean; }

	void LoadUpgradeBean();
	void SaveUpgradeBean();
	inline 		std::vector<UpgradeBean *>		 getUpgradeBean(int index) { return m_vecUpgradeBean.at(index); }

	void LoadPlayerBean();
	void SavePlayerBean();
	inline PlayerBean *	getPlayerBean() { return m_playerBean; }
	
	void LoadPlayerUpgradeBean();
	void SavePlayerUpgradeBean();
	inline 		std::vector<PlayerUpgradeInfo *>	getPlayerUpgraedBean() { return m_vecPlayerUpgradeBean; }

	void LoadZombiBean();
	void SaveZombiBean();
	inline std::vector<ZombiBean *>	 getZombiBean() { return m_vecZombiBean; }
	

	void LoadZombiZenBean();
	void SaveZombiZenBean();
	inline std::vector<ZombiZenBean *>	 getZombiZenBean(int index) { return m_vecZombiZenBean.at(index); }

	void Destory();
	~beanManager();
};

