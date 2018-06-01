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

		//����
	case 4: return 	TransitionFade::create(t, s);
		//������ �ѱ� ���� : PageTransitionForward
	case 5: return 	TransitionPageTurn::create(t, s, false);
		//������ �ѱ� ���� : PageTransitionBackward
	case 6: return 	TransitionPageTurn::create(t, s, true);
		//�ٵ��� ���� ���� �ϴܺ��� ���� ��� ������ �����
	case 7: return 	TransitionFadeTR::create(t, s);
		//�ٵ��� ���� ���� ��ܺ��� ���� �ϴ� ������ �����
	case 8: return 	TransitionFadeBL::create(t, s);
		//�ϴܿ��� ������� �߶�
	case 9: return 	TransitionFadeUp::create(t, s);
		//��ܿ��� �ϴ����� �߶�
	case 10: return 	TransitionFadeDown::create(t, s);

		//���η� �� ��� ����
	case 11: return 	TransitionSplitRows::create(t, s);
		//���η� �� ��� ����, �糡�� �� ����� ������ �������� ����
	case 12: return 	TransitionSplitCols::create(t, s);

		//���̵��ξƿ� : ���� ȭ��
	case 13: return 	TransitionFade::create(t, s);
		//���̵��ξƿ� : �Ͼ� ȭ��
	case 14: return 	TransitionFade::create(t, s, Color3B::WHITE);

		//X��(Ⱦ��)�� �������� ȸ�� : FilpXLeftOver
	case 15: return 	TransitionFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		//X��(Ⱦ��)�� �������� ȸ�� : FilpXRightOver
	case 16: return 	TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
		//Y��(����)�� �������� ȸ�� : FlipYUpOver
	case 17: return 	TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER);
		//Y��(����)�� �������� ȸ�� : FlipYDownOver
	case 18: return 	TransitionFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER);

		// ���������鼭 ����������� �Ѿ (Ȯ��) : ZoomFlipAngularLeftOver
	case 19: return 	TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER);
		// ���������鼭 ����������� �Ѿ (Ȯ��) : ZoomFlipAngularRightOver
	case 20: return 	TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);

		// ������� ���� ������� Ȯ��
	case 21: return 	TransitionShrinkGrow::create(t, s);
		// ȸ���ϸ鼭 Zoom
	case 22: return 	TransitionRotoZoom::create(t, s);

		// ���ʿ��� ��������� ��Ÿ���� ��������� ���
	case 23: return 	TransitionMoveInL::create(t, s);
		// �����ʿ��� ��������� ��Ÿ��
	case 24: return 	TransitionMoveInR::create(t, s);
		// ���ʿ��� ��������� ��Ÿ��
	case 25: return 	TransitionMoveInT::create(t, s);
		// �Ʒ��ʿ��� ��������� ��Ÿ��
	case 26: return 	TransitionMoveInB::create(t, s);

		// ���ʿ��� ��������� ��Ÿ���� ��������� �о
	case 27: return 	TransitionSlideInL::create(t, s);
		// �����ʿ��� ��������� ��Ÿ���� ��������� �о
	case 28: return 	TransitionSlideInR::create(t, s);
		// ���ʿ��� ��������� ��Ÿ���� ��������� �о
	case 29: return 	TransitionSlideInT::create(t, s);
		// �Ʒ��ʿ��� ��������� ��Ÿ���� ��������� �о
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
