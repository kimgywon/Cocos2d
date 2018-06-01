#include "PlayerSkill.h"
#include "ZombiUnit.h"
#include "Enemy.h"

PlayerSkill * PlayerSkill::m_this = NULL;

PlayerSkill::PlayerSkill()
{
}


void PlayerSkill::Init(Layer * standard)
{
	m_StandardLayer = standard;
	this->skillCreate();
	m_Move = true;
	m_CulSkill = NULL;

	m_Skill1 = Sprite::create("effect/Skill_1.png");
	
	m_Skill1->setAnchorPoint(Vec2(0, 0));
	m_Skill1->setVisible(false);
	m_StandardLayer->addChild(m_Skill1);

	m_Skill2 = Sprite::create("effect/Skill2_1.png");

	m_Skill2->setAnchorPoint(Vec2(0, 0));
	m_Skill2->setVisible(false);
	m_StandardLayer->addChild(m_Skill2);

	m_Skill3 = Sprite::create("effect/fire1.png");

	m_Skill3->setAnchorPoint(Vec2(0, 0));
	m_Skill3->setVisible(false);
	m_Skill3->setScale(2);
	m_StandardLayer->addChild(m_Skill3);
}

void PlayerSkill::Update(float eTme, std::list<ZombiUnit*> ZombiEnemy, Enemy * enemy)
{

	if (m_CulSkill != NULL)
	{
		if (m_Move == true)
		{
			Point pos = m_CulSkill->getPosition();
			pos.x += m_Speed * eTme;
			m_CulSkill->setPosition(pos);
		}

		/*
		if (m_CulSkillCount == 2)
		{
			if (m_vecSkill.size() < 7)
			{
				this->doSkillChange(3, 100, 20, m_CulSkill->getPosition(), m_vecSkill.size());
			}
		}
		*/

		if(m_CulSkillCount == 0)
			this->AttackCheck1(ZombiEnemy, enemy);
		else if(m_CulSkillCount == 1)
			this->AttackCheck2(ZombiEnemy, enemy);
		else if (m_CulSkillCount == 2)
			this->AttackCheck3(ZombiEnemy, enemy);
	}
	
}

void PlayerSkill::AttackCheck1(std::list<ZombiUnit*> ZombiEnemy, Enemy * enemy)
{
	bool m_EnemyHit = false;


	for (auto iter = ZombiEnemy.begin(); iter != ZombiEnemy.end(); iter++)
	{
		if ((*iter)->EnemyAteeckCheck() == false)
			continue;

		Rect rect = m_CulSkill->getBoundingBox();
		if ((*iter)->getEnemyPosition()<enemy->EnemyPosition() || m_EnemyHit)
		{
			if (rect.intersectsRect((*iter)->getBoundingBox()))
			{
				(*iter)->SubEnemyHpBar(m_Damage);
				this->doSkillChange(4, 0, 0, Point(m_CulSkill->getPosition().x + rect.size.width, m_CulSkill->getPosition().y), m_vecSkill.size());
				m_EnemyHit = true;
				break;
			}
		}
		else if (m_EnemyHit == false)
		{
			if (rect.intersectsRect(enemy->getEnemyRect()))
			{
				enemy->SubHp(m_Damage);
				this->doSkillChange(4, 100, 20, Point(m_CulSkill->getPosition().x + m_CulSkill->getBoundingBox().size.width, m_CulSkill->getPosition().y), m_vecSkill.size());
				break;
				break;
			}
			m_EnemyHit = true;
		}
	}

	if (m_EnemyHit == false)
	{
		if (m_CulSkill == NULL)
			return;

		Rect rect = m_CulSkill->getBoundingBox();

		if (rect.intersectsRect(enemy->getEnemyRect()))
		{
			enemy->SubHp(m_Damage);
			this->doSkillChange(4, 100, 20, Point(m_CulSkill->getPosition().x + m_CulSkill->getBoundingBox().size.width, m_CulSkill->getPosition().y), m_vecSkill.size());
		}
	}
}

void PlayerSkill::AttackCheck2(std::list<ZombiUnit*> ZombiEnemy, Enemy * enemy)
{
	if (m_CulSkill->getSpriteFrame() != m_SkillFrame[m_CulSkillCount])
		return;

	bool m_EnemyHit = false;

	for (auto iter = ZombiEnemy.begin(); iter != ZombiEnemy.end(); iter++)
	{
		if ((*iter)->EnemyAteeckCheck() == false)
			continue;

		Rect rect = m_CulSkill->getBoundingBox();

		rect.origin.x -= 30;
			if (rect.intersectsRect((*iter)->getBoundingBox()))
			{
				(*iter)->SubEnemyHpBar(m_Damage);
				Sprite * Exp = Sprite::create();
				RemoveSelf * self = RemoveSelf::create(true);
				Sequence * seq = Sequence::create(m_SkillAction.at(4)->clone(), self, NULL);

				Exp->runAction(seq);
				Exp->setPosition(0, 0);
				Exp->setAnchorPoint(Vec2(0, 0));
				(*iter)->addChild(Exp);

			}
			m_EnemyHit = true;
	}

	if (m_EnemyHit)
	{
		m_CulSkill = NULL;
	}
	else
	{
		if (m_CulSkill == NULL)
			return;

		Rect rect = m_CulSkill->getBoundingBox();

		if (rect.intersectsRect(enemy->getEnemyRect()))
		{
			enemy->SubHp(m_Damage);
		}
	}
}

void PlayerSkill::AttackCheck3(std::list<ZombiUnit*> ZombiEnemy, Enemy * enemy)
{
}

/*
void PlayerSkill::AttackCheck(std::list<ZombiUnit *> ZombiEnemy, Enemy* enemy)
{
	bool m_EnemyHit = false;
	bool ateckbreak = false;

	for (auto iter = ZombiEnemy.begin(); iter != ZombiEnemy.end(); iter++)
	{
		if (ateckbreak)
			return;

		if ((*iter)->EnemyAteeckCheck() == false)
			continue;

		for (auto iter2 = m_vecSkill.begin(); iter2 < m_vecSkill.end(); iter2++)
		{
			if ((*iter)->getSpriteFrame() == m_SkillFrame[m_CulSkillCount])
			{
				Rect rect = (*iter2)->getBoundingBox();

				if ((*iter)->getEnemyPosition() < enemy->EnemyPosition() || m_EnemyHit)
				{
					if (rect.intersectsRect((*iter)->getBoundingBox()))
					{
						m_AtteckPossible = true;  // 유닛이 맞음
						if (m_UnitAtteckBox.width < 100)
							m_ZombiUnit = (*iter);
						break;
					}
				}
				else if (m_EnemyHit == false)
				{
					if (rect.intersectsRect(enemy->getEnemyRect()))
					{
						m_AtteckPossible = true;  //플레이어가 맞음
						m_Enemy = enemy;
						break;
					}
					m_EnemyHit = true;
				}
			}
		}
	}

	if (m_AtteckPossible == false)
	{
		Rect rect = this->getBoundingBox();
		Sprite * size = Sprite::createWithSpriteFrame(m_SpriteFrame[2]);
		rect.size = size->getBoundingBox().size;
		rect.size.width += m_UnitAtteckBox.width;
		rect.origin.y += m_UnitAtteckBox.height;

		if (rect.intersectsRect(enemy->getEnemyRect()))
		{
			m_AtteckPossible = true;  //플레이어가 맞음
			m_Enemy = enemy;
		}
		m_EnemyHit = true;
	}
}
*/

void PlayerSkill::doSkillChange(int skill, int Speed, int Damage, Point Position, int count)
{
	m_Damage = Damage;
	m_Speed = Speed;
	switch (skill)
	{
	case 1:
	{
		m_Move = true;
		m_CulSkill = m_Skill1;
		RepeatForever * rep = RepeatForever::create(m_SkillAction.at(0));
		m_CulSkill->runAction(rep);
		m_CulSkill->setAnchorPoint(Vec2(0, 0));
		m_vecSkill.pushBack(m_CulSkill);
		m_CulSkillCount = 0;
		break;
	}
	case 2:
	{
		m_Move = false;
		m_CulSkill = m_Skill2;
		CallFunc * call = CallFunc::create(CC_CALLBACK_0(PlayerSkill::CallfuncRemove, this, m_CulSkill));
		Sequence * seq = Sequence::create(m_SkillAction.at(1), call, NULL);
		m_CulSkill->runAction(seq);
		m_vecSkill.pushBack(m_CulSkill);
		m_CulSkillCount = 1;
		break;
	}
	case 3:
	{
		if (count == 1)
		{
			m_Move = false;
			m_CulSkill = m_Skill3;
			m_CulSkill->runAction(m_SkillAction.at(2));
			m_vecSkill.pushBack(m_CulSkill);
			m_CulSkillCount = 3;
		}
		else
		{
			Sprite * Skill3 = Sprite::create("effect/fire1.png");
			Rect pos = m_Skill3->getBoundingBox();
			int width = pos.origin.x + (pos.size.width *(count+1));
			Skill3->setAnchorPoint(Vec2(0, 0));
			Skill3->setPosition(width, pos.origin.y);
			m_StandardLayer->addChild(Skill3);

			m_vecSkill.pushBack(Skill3);
		}
		break;
	}
	case 4:
	{
		m_CulSkill->stopAllActions();
		m_Move = false;
		m_CulSkill->setSpriteFrame(Sprite::create("effect/Exp1.png")->getSpriteFrame());
		CallFunc * call = CallFunc::create(CC_CALLBACK_0(PlayerSkill::CallfuncRemove, this, m_CulSkill));
		Sequence * seq = Sequence::create(m_SkillAction.at(3), call, NULL);
		m_CulSkill->runAction(seq);
		m_CulSkill->setPosition(Position);
		m_CulSkill->setAnchorPoint(Vec2(0.5, 0));
		m_CulSkill = NULL;
		break;
	}
	default:
		break;
	}

	if (m_CulSkill != NULL)
	{
		m_CulSkill->setVisible(true);
		m_CulSkill->setPosition(Position);
	}
}

void PlayerSkill::skillCreate()
{
	for (int i = 0; i < 5; i++)
	{
		char str[100];
		float animeSpeed;

		Vector<SpriteFrame *> animeFrame;
		if (i == 0)
		{
			animeSpeed = 0.15f;
			for (int i = 0; i < 4; i++)
			{
				sprintf(str, "effect/Skill_%d.png", i + 1);
				SpriteFrame * fraem = Sprite::create(str)->getSpriteFrame();
				animeFrame.pushBack(fraem);
			}
			m_SkillFrame[i] = animeFrame.at(3);
		}
		else if (i == 1)
		{
			animeSpeed = 0.15f;
			for (int i = 0; i < 4; i++)
			{
				sprintf(str, "effect/Skill2_%d.png", i + 1);
				SpriteFrame * fraem = Sprite::create(str)->getSpriteFrame();
				animeFrame.pushBack(fraem);
			}
			m_SkillFrame[i] = animeFrame.at(3);
		}
		else if (i == 2)
		{
			animeSpeed = 0.15f;
			for (int i = 0; i < 10; i++)
			{
				sprintf(str, "effect/fire%d.png", i + 1);
				SpriteFrame * fraem = Sprite::create(str)->getSpriteFrame();
				animeFrame.pushBack(fraem);
			}
			m_SkillFrame[i] = animeFrame.at(3);
		}
		else if (i == 3)
		{
			animeSpeed = 0.15f;
			for (int i = 0; i < 6; i++)
			{
				sprintf(str, "effect/Exp%d.png", i + 1);
				SpriteFrame * fraem = Sprite::create(str)->getSpriteFrame();
				animeFrame.pushBack(fraem);
			}
		}
		else if (i == 4)
		{
			animeSpeed = 0.15f;
			for (int i = 0; i < 6; i++)
			{
				sprintf(str, "effect/Exp1_%d.png", i );
				SpriteFrame * fraem = Sprite::create(str)->getSpriteFrame();
				animeFrame.pushBack(fraem);
			}
		}

		Animation * animation = Animation::createWithSpriteFrames(animeFrame, animeSpeed);

		Animate * action = Animate::create(animation);

		action->retain();
		m_SkillAction.pushBack(action);
	}
}

bool PlayerSkill::SkillCheck()
{
	if(m_vecSkill.size() >0)
		return false;
	
	return true;
}

void PlayerSkill::CallfuncRemove(Sprite * sprite)
{
	m_vecSkill.eraseObject(sprite);

	if (m_vecSkill.size() < 1)
	{
		m_CulSkill = NULL;
		sprite->setVisible(false);
		m_Move = true;
	}
}

void PlayerSkill::Destory()
{
	for (auto iter = m_SkillAction.begin(); iter < m_SkillAction.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}

	CC_SAFE_DELETE(m_this);
}

PlayerSkill::~PlayerSkill()
{
}
