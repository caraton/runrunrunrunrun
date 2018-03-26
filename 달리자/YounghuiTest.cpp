#include "stdafx.h"
#include "YounghuiTest.h"
#include "player.h"

HRESULT YounghuiTest::init(void)
{
	IMAGEMANAGER->addImage("background_jail", "Image/background_jail.bmp", 600, 800, true, RGB(255, 0, 255));

	_cameraX = 0;
	_cameraY = 0;

	_player = new player;
	_player->init();

	return S_OK;
}

void YounghuiTest::release(void)
{
}

void YounghuiTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("½Ã¿õ¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("¹Î¼®¾À");
	}

	_cameraY -= 3;

	_player->update();
}

void YounghuiTest::render(void)
{

	IMAGEMANAGER->findImage("background_jail")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _cameraX, _cameraY);
	_player->render();
}

YounghuiTest::YounghuiTest()
{
	_player = NULL;
}

YounghuiTest::~YounghuiTest()
{
}
