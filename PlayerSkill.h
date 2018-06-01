#pragma once
#include "cocos2d.h"
#include <list>
USING_NS_CC;

class Enemy;
class ZombiUnit;
class PlayerSkill 
{
	static PlayerSkill *						m_this;
	Sprite *												m_Skill1;
	Sprite *												m_Skill2;
	Sprite *												m_Skill3;

	Sprite *												m_CulSkill;
	int														m_CulSkillCount;
	Vector<Animate *>							m_SkillAction;
	Vector<Sprite *>							m_vecSkill;
	SpriteFrame *									m_SkillFrame[3];

	Layer *												m_StandardLayer;

	bool													m_Move;
	int														m_Speed;
	int														m_Damage;
public:
	PlayerSkill();
	static PlayerSkill*		 getInstance()
	{
		if (m_this == NULL)
		{
			m_this = new PlayerSkill();
		}

		return m_this;
	}

	void Init(Layer * standard);
	void Update(float eTme , std::list<ZombiUnit *> ZombiEnemy, Enemy* enemy);
	void AttackCheck1(std::list<ZombiUnit *> ZombiEnemy, Enemy* enemy);
	void AttackCheck2(std::list<ZombiUnit *> ZombiEnemy, Enemy* enemy);
	void AttackCheck3(std::list<ZombiUnit *> ZombiEnemy, Enemy* enemy);

	void doSkillChange(int skill, int Speed, int Damage, Point Position, int count = 1);
	void skillCreate();

	bool SkillCheck();
	void CallfuncRemove(Sprite * sprite);
	void Destory();
	~PlayerSkill();
};

