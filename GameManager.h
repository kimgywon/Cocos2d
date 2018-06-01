#pragma once
#include "cocos2d.h"
#include "beanManager.h"

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

USING_NS_CC;

enum SCENENAME
{
	BLACKSCENE,
	TITLESCENE,
	MAINSCENE,
	UPGRADESCENE,
	GAMESCENELAVEL1,
	GAMESCENELAVEL2,
	TEST,
};

enum PRESSEDKEY
{
	LEFTKEY,
	RIGHTKEY,
	NONKEY,
	SKILLKEY,
	DIEKEY,
};

class GameManager 
{
	GameManager();
	static GameManager*		m_this;

public:
	static GameManager*		 getInstance()
	{
		if (m_this == NULL)
		{
			m_this = new GameManager();
		}

		return m_this;
	}

	void Init();
	void	 SceneChange(SCENENAME SceneIndex, int index, float t);
	Scene * getScene(SCENENAME SceneIndex);
	TransitionScene * createTransition(int index, float t, Scene * s);

	void Destory();
	~GameManager();
};

