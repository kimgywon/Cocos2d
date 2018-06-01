#pragma once
#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class GameScene;


struct PlayerBasicInformation
{
	int playerCulHp;
	int playerHp;
	int PlayerMana;
	int PlayerEnegy;
	int UnitAttackDamage;
	int UnitDefense;
	int UnitMoveSpeed;
	int MagicSize;
};

enum PLAYERSTATE
{
	PLAYERBASE,
	PLAYERATTECK,
	PLAYERRIGHTMOVE,
	PLAYERLEFTMOVE,
	PLAYERDIE,
};

class Player :public Sprite
{
	Size													m_VisibleSize;
	Vector<Action *>						m_vecUnitAction;
	std::vector<PlayerBean *>		m_vecPlayerInfo;
	Sprite *											m_magicSprite;
	Sprite *											m_Wing;
	DrawNode *									m_drawNode;
	PRESSEDKEY								m_PlayerKey;
	GameScene *								m_GameScne;
	PlayerBasicInformation			m_PlayerInfo;
	Action *											m_CulAction;
	Action*											m_BlinkAction;
	PLAYERSTATE								m_PlayerSptae;
public:
	Player();

	static Player * createSprite(GameScene * scene);

	void Init(GameScene * scene);
	void Draw();
	void createUnitAction();

	inline void setPlayerKey(PRESSEDKEY Key) { m_PlayerKey = Key; m_PlayerKey = NONKEY; }

	void PlayerActionChange(PLAYERSTATE state);
	Rect getMagicRect();
	
	void PlayerHit(int num);

	bool PlayerState();
	void CallfuncBlink();
	inline PlayerBasicInformation getPlayerInfo() { return m_PlayerInfo; };

	void DrawNodeClear();
	~Player();
};

