#include "Player.h"
#include "GameScene.h"
#include "beanManager.h"

Player::Player()
{
}

Player * Player::createSprite(GameScene * scene)
{
	Player * player = new Player();

	if (player && player->initWithSpriteFrameName("policeBossIdle1.png"))
	{
		player->autorelease();
		player->Init(scene);
		return player;
	}

	CC_SAFE_DELETE(player);

	return nullptr;
}

void Player::Init(GameScene * scene)
{
	this->createUnitAction();
	this->m_GameScne = scene;
	m_CulAction = NULL;
	m_BlinkAction = NULL;

	std::vector<PlayerUpgradeInfo *> Upgradeinfo = beanManager::getInstance()->getPlayerUpgraedBean();

	PlayerBean * bean = beanManager::getInstance()->getPlayerBean();
	m_PlayerInfo.MagicSize = Upgradeinfo.at(bean->getPlayerMagicSize() - 1)->getPlayerMagicSize();
	m_PlayerInfo.playerCulHp = Upgradeinfo.at(bean->getPlayerHp() - 1)->getPlayerHp();
	m_PlayerInfo.PlayerEnegy = Upgradeinfo.at(bean->getPlayerEnegy() - 1)->getPlayerEnegy();
	m_PlayerInfo.playerHp = Upgradeinfo.at(bean->getPlayerHp() - 1)->getPlayerHp();
	m_PlayerInfo.PlayerMana = Upgradeinfo.at(bean->getPlayerMana() - 1)->getPlayerMana();
	m_PlayerInfo.UnitAttackDamage = Upgradeinfo.at(bean->getPlayerBlessAtteck() - 1)->getPlayerBlessAtteck();
	m_PlayerInfo.UnitDefense = Upgradeinfo.at(bean->getPlayerBlessDefence() - 1)->getPlayerBlessDefence();
	m_PlayerInfo.UnitMoveSpeed = Upgradeinfo.at(bean->getPlayerBlessMoveSpeed() - 1)->getPlayerBlessMoveSpeed();

	m_drawNode = DrawNode::create();
	addChild(m_drawNode, 10);

	m_PlayerKey = NONKEY;
	m_PlayerSptae = PLAYERBASE;

	char str[100];
	m_magicSprite = Sprite::create("effect/10.png");
	Animation * anmation = Animation::create();

	anmation->setDelayPerUnit(.15);
	for (int i = 0; i < 5; i++)
	{
		sprintf(str, "effect/%d.png", i + 10);
		anmation->addSpriteFrameWithFile(str);
	}

	Animate * animate = Animate::create(anmation);
	Sequence * seq = Sequence::create(animate, NULL);
	RepeatForever * rep = RepeatForever::create(seq);
	m_magicSprite->runAction(rep);

	m_magicSprite->setScaleX(m_PlayerInfo.MagicSize);

	m_magicSprite->setPosition(Vec2(this->getContentSize().width / 2, 0));

	this->addChild(m_magicSprite, -1);


	m_Wing = Sprite::create("effect/wing.png");

	m_Wing->setPosition(Vec2(this->getContentSize().width / 2, 80));
	this->addChild(m_Wing, -1);
	ScaleBy * action2 = ScaleBy::create(1.0f, 1.1f);
	ScaleBy * action3 = action2->reverse();
	Sequence * seq2 = Sequence::create(action2, action3, NULL);
	RepeatForever * rep2 = RepeatForever::create(seq2);
	m_Wing->runAction(rep2);


	this->setPosition(Vec2(200, 350));
	this->setAnchorPoint(Vec2(0., 0));

	this->PlayerActionChange(PLAYERBASE);
}

void Player::Draw()
{
	m_drawNode->clear();
	Point p = this->getPosition();
	m_drawNode->drawRect(Vec2(0,0), Vec2(this->getContentSize().width , this->getContentSize().height ), Color4F::RED);
}

void Player::createUnitAction()
{
	for (int i = 0; i < 4; i++)
	{
		char str[100];
		float animeSpeed;

		Vector<SpriteFrame *> animeFrame;
		if (i == 0)
		{
			animeSpeed = 0.15f;
			for (int i = 0; i < 8; i++)
			{
				sprintf(str, "policeBossIdle%d.png", i + 1);
				SpriteFrame * fraem = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
				animeFrame.pushBack(fraem);
			}
		}
		else if (i == 1)
		{
			animeSpeed = 0.2f;
			for (int i = 0; i < 8; i++)
			{
				sprintf(str, "policeBossAttack%d.png", i + 1);
				SpriteFrame * fraem = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
				animeFrame.pushBack(fraem);
			}
		}
		else if (i == 2)
		{
			animeSpeed = 0.15f;
			for (int i = 0; i < 8; i++)
			{
				sprintf(str, "policeBossWalk%d.png", i + 1);
				SpriteFrame * fraem = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
				animeFrame.pushBack(fraem);
			}
		}
		else if (i == 3)
		{
			animeSpeed = 0.3f;
			for (int i = 0; i < 9; i++)
			{
				sprintf(str, "policeBossHurt%d.png", i + 1);
				SpriteFrame * fraem = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
				animeFrame.pushBack(fraem);
			}
		}

		Animation * animation = Animation::createWithSpriteFrames(animeFrame, animeSpeed);

		Animate * action = Animate::create(animation);

		if (i != 1 && i !=3)
		{
			RepeatForever * rep = RepeatForever::create(action);
			rep->retain();
			m_vecUnitAction.pushBack(rep);
		}
		else
		{
			action->retain();
			m_vecUnitAction.pushBack(action);
		}
	}


}

void Player::PlayerActionChange(PLAYERSTATE state)
{
	if (m_PlayerSptae == PLAYERDIE)
		return;

	if (m_CulAction != NULL)
		this->stopAction(m_CulAction);

	switch (state)
	{
	case PLAYERBASE:
		m_GameScne->IsPlayerSkill(false);
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("policeBossIdle1.png"));
		this->runAction(m_vecUnitAction.at(0));
		m_CulAction = m_vecUnitAction.at(0);
		break;
	case PLAYERATTECK:
	{
		m_GameScne->IsPlayerSkill(true);
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("policeBossAttack1.png"));
		DelayTime * action = DelayTime::create(0.15 * 10);
		CallFunc * action2;

		if(m_PlayerKey == NONKEY)
			 action2 = CallFunc::create(CC_CALLBACK_0(Player::PlayerActionChange, this, PLAYERBASE));
		else
			action2 = CallFunc::create(CC_CALLBACK_0(Player::PlayerActionChange, this, PLAYERRIGHTMOVE));
	
		Sequence * action3 = Sequence::create((Animate *)m_vecUnitAction.at(1), action2, NULL);
		this->runAction(action3);
		m_CulAction = action3;
//////////////////////////////////////////////////////////////////////////////////
		char str[100];
		float animeSpeed;
		Vector<SpriteFrame *> animeFrame2;

		Sprite * effect = Sprite::create("effect/Bosseffect0.png");
		effect->setAnchorPoint(Vec2(0, 0));

		animeSpeed = 0.1f;
		for (int i = 0; i < 4; i++)
		{
			sprintf(str, "effect/Bosseffect%d.png", i);
			SpriteFrame * fraem = Sprite::create(str)->getSpriteFrame();
			animeFrame2.pushBack(fraem);
		}

		Animation * animation2 = Animation::createWithSpriteFrames(animeFrame2, animeSpeed);

		Animate * anima = Animate::create(animation2);

		Repeat * rep = Repeat::create(anima,3);

		RemoveSelf * self = RemoveSelf::create(true);

		Sequence * seq = Sequence::create(rep, self, NULL);
		effect->runAction(seq);

		this->addChild(effect);
		//////////////////////////////////////////////////////////////////////////////////
		break;
	}
	case PLAYERRIGHTMOVE:
		m_GameScne->IsPlayerSkill(false);
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("policeBossWalk1.png"));
		this->runAction(m_vecUnitAction.at(2));
		m_CulAction = m_vecUnitAction.at(2);
		break;
	case PLAYERLEFTMOVE:
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("policeBossWalk1.png"));
		this->runAction(m_vecUnitAction.at(2));
		m_CulAction = m_vecUnitAction.at(2);
		break;
	case PLAYERDIE:
		m_Wing->setVisible(false);
		this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("policeBossHurt1.png"));
		this->runAction(m_vecUnitAction.at(3));
		m_CulAction = m_vecUnitAction.at(3);
		m_PlayerSptae = PLAYERDIE;
		break;
	default:
		break;
	}
}

Rect Player::getMagicRect()
{
	Rect rect = m_magicSprite->getBoundingBox();

	rect.origin = this->convertToWorldSpace(m_magicSprite->getBoundingBox().origin);
	rect.origin.x += 50;
	rect.size.width -= 50;
	return rect;
}

void Player::PlayerHit(int num)
{
	m_PlayerInfo.playerCulHp -= num;

	if (m_BlinkAction == NULL)
	{
		FadeOut *action = FadeOut::create(0.1f);    // 시간
		FadeIn *action2 = FadeIn::create(0.1f);    // 시간

		CallFunc *call = CallFunc::create(CC_CALLBACK_0(Player::CallfuncBlink, this));
		Sequence * seq = Sequence::create(action, action2, call, NULL);
		m_BlinkAction = seq;
		this->runAction(m_BlinkAction);
	}
}

bool Player::PlayerState()
{
	if (m_PlayerKey < 3)
		return true;

	return false;
}

void Player::CallfuncBlink()
{
	m_BlinkAction = NULL;
}


void Player::DrawNodeClear()
{
	m_drawNode->clear();
}

Player::~Player()
{
	for (auto iter = m_vecUnitAction.begin(); iter < m_vecUnitAction.end(); iter++)
	{
		CC_SAFE_RELEASE((*iter));
	}
	this->removeAllChildrenWithCleanup(true);
}
