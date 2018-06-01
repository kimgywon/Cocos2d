#include "GameManager.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "BlackScene.h"
#include "MainScene.h"
#include "GameSceneLevel1.h"
#include "GameSceneLevel2.h"
#include "UpgradeScene.h"

GameManager *GameManager::m_this = nullptr;

GameManager::GameManager()
{
}

void GameManager::Init()
{
	srand(time(NULL));

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/enemy1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/enemy2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/enemy3.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/enemy4.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/enemyBoss1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/enemyBoss2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("police/police1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("police/police2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("police/police3.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("police/police4.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("police/policeBoss.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/stageButton.plist");

	beanManager::getInstance()->Init();
}

void GameManager::SceneChange(SCENENAME SceneIndex,int index, float t)
{
	Scene *  scene ;

	switch (SceneIndex)
	{
	case BLACKSCENE:
	{
		scene = BlackScene::createScene();
		dynamic_cast<BlackScene *>(scene)->SceneChange((SCENENAME)index);
		Director::getInstance()->replaceScene(createTransition(13, 0.5f, scene));
		break;
	}
	case TITLESCENE:
		scene = TitleScene::createScene();
		Director::getInstance()->replaceScene(createTransition(index, t, scene));
		break;
	case MAINSCENE:
		scene = MainScene::createScene();
		Director::getInstance()->replaceScene(createTransition(index, t, scene));
		break;
	case UPGRADESCENE:
		scene = UpgradeScene::createScene();
		Director::getInstance()->replaceScene(createTransition(index, t, scene));
		break;
	case GAMESCENELAVEL1:
		scene = GameSceneLevel1::createScene();
		Director::getInstance()->replaceScene(createTransition(index, t, scene));
		break;
	case GAMESCENELAVEL2:
		scene = GameSceneLevel2::createScene();
		Director::getInstance()->replaceScene(createTransition(index, t, scene));
		break;
	case TEST:
		scene = TestScene::createScene();
		Director::getInstance()->replaceScene(createTransition(index, t, scene));
		break;
	}
}

Scene * GameManager::getScene(SCENENAME SceneIndex)
{
	Scene *  scene = NULL;

	switch (SceneIndex)
	{
	case TITLESCENE:
		scene = TitleScene::createScene();
		break;
	case GAMESCENELAVEL1:
		scene = GameSceneLevel1::createScene();
		break;
	}

	return scene;
}

TransitionScene * GameManager::createTransition(int index, float t, Scene * s)
{
	Director::getInstance()->setDepthTest(false);

	switch (index)
	{
	case 0: return TransitionProgressHorizontal::create(t, s);
	case 1: return 	TransitionProgressVertical::create(t, s);
	case 2: return 	TransitionProgressInOut::create(t, s);
	case 3: return 	TransitionProgressOutIn::create(t, s);

		//교차
	case 4: return 	TransitionFade::create(t, s);
		//페이지 넘김 형식 : PageTransitionForward
	case 5: return 	TransitionPageTurn::create(t, s, false);
		//페이지 넘김 형식 : PageTransitionBackward
	case 6: return 	TransitionPageTurn::create(t, s, true);
		//바둑판 무늬 좌측 하단부터 우측 상단 순으로 사라짐
	case 7: return 	TransitionFadeTR::create(t, s);
		//바둑판 무늬 우측 상단부터 좌측 하단 순으로 사라짐
	case 8: return 	TransitionFadeBL::create(t, s);
		//하단에서 상단으로 잘라냄
	case 9: return 	TransitionFadeUp::create(t, s);
		//상단에서 하단으로 잘라냄
	case 10: return 	TransitionFadeDown::create(t, s);

		//가로로 세 등분 나눔
	case 11: return 	TransitionSplitRows::create(t, s);
		//세로로 세 등분 나눔, 양끝의 두 등분은 밑으로 나머지는 위로
	case 12: return 	TransitionSplitCols::create(t, s);

		//페이드인아웃 : 검정 화면
	case 13: return 	TransitionFade::create(t, s);
		//페이드인아웃 : 하얀 화면
	case 14: return 	TransitionFade::create(t, s, Color3B::WHITE);

		//X축(횡선)을 기준으로 회전 : FilpXLeftOver
	case 15: return 	TransitionFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		//X축(횡선)을 기준으로 회전 : FilpXRightOver
	case 16: return 	TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		//Y축(종선)을 기준으로 회전 : FlipYUpOver
	case 17: return 	TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		//Y축(종선)을 기준으로 회전 : FlipYDownOver
	case 18: return 	TransitionFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);

		// 뒤집어지면서 다음장면으로 넘어감 (확대) : ZoomFlipAngularLeftOver
	case 19: return 	TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// 뒤집어지면서 다음장면으로 넘어감 (확대) : ZoomFlipAngularRightOver
	case 20: return 	TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);

		// 이전장면 수축 다음장면 확대
	case 21: return 	TransitionShrinkGrow::create(t, s);
		// 회전하면서 Zoom
	case 22: return 	TransitionRotoZoom::create(t, s);

		// 왼쪽에서 다음장면이 나타나서 이전장면을 덮어씀
	case 23: return 	TransitionMoveInL::create(t, s);
		// 오른쪽에서 다음장면이 나타남
	case 24: return 	TransitionMoveInR::create(t, s);
		// 위쪽에서 다음장면이 나타남
	case 25: return 	TransitionMoveInT::create(t, s);
		// 아래쪽에서 다음장면이 나타남
	case 26: return 	TransitionMoveInB::create(t, s);

		// 왼쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 27: return 	TransitionSlideInL::create(t, s);
		// 오른쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 28: return 	TransitionSlideInR::create(t, s);
		// 위쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 29: return 	TransitionSlideInT::create(t, s);
		// 아래쪽에서 다음장면이 나타나서 이전장면을 밀어냄
	case 30: return 	TransitionSlideInB::create(t, s);


	default:break;
	}

	return NULL;
}

void GameManager::Destory()
{
	beanManager::getInstance()->Destory();
	SAFE_DELETE(m_this);
}

GameManager::~GameManager()
{
}
