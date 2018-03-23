#include "stdafx.h"
#include "SiwoongTest.h"
#include "player.h"
#include "CollisionManager.h"

HRESULT SiwoongTest::init(void)
{
	IMAGEMANAGER->addImage("배경", "Image/Backgrounds/background.bmp", 600, 800, true, RGB(255,0,255));

	_colManager = new CollisionManager;
	_colManager->init();

	_player = new player;
	_player->init();

	_colManager->linkPlayer(_player);
	_player->linkColManager(_colManager);

	_testIR._image = IMAGEMANAGER->addImage("테스트장애물", "Image/Obstacles/enemy.bmp", 40, 40, true, RGB(255,0,255));
	_testIR._rc = RectMakeCenter(40, WINSIZEY/2, 40,40);

	_colManager->addIR(&_testIR); //충돌처리할 IR들을 colManager에 보내주기

	_cameraY = 0;

	return S_OK;
}

void SiwoongTest::release(void)
{
}

void SiwoongTest::update(void)
{
	//민석씬 이동
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("민석씬");
	}

	if (_colManager->GetGameover())
	{
		return;
	}

	_player->update();
	_colManager->update();
}

void SiwoongTest::render(void)
{
	_cameraY = _player->GetCamY();
	IMAGEMANAGER->findImage("배경")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _cameraY);

	_testIR._image->render(getMemDC(), _testIR._rc.left, _testIR._rc.top);
	//_colManager->render();

	_player->render();
}

SiwoongTest::SiwoongTest()
{
	_player = NULL;
}

SiwoongTest::~SiwoongTest()
{
}