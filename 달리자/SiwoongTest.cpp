#include "stdafx.h"
#include "SiwoongTest.h"
#include "player.h"

HRESULT SiwoongTest::init(void)
{
	_player = new player;
	_player->init();

	return S_OK;
}

void SiwoongTest::release(void)
{
}

void SiwoongTest::update(void)
{
	//�μ��� �̵�
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("�μ���");
	}

	_player->update();
}

void SiwoongTest::render(void)
{
	_player->render();
}

SiwoongTest::SiwoongTest()
{
	_player = NULL;
}

SiwoongTest::~SiwoongTest()
{
}