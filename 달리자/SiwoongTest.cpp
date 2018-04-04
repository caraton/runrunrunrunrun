#include "stdafx.h"
#include "SiwoongTest.h"
#include "player.h"
#include "CollisionManager.h"

HRESULT SiwoongTest::init(void)
{
	IMAGEMANAGER->addImage("background_jail", "Image/background_jail.bmp", 600, 800, true, RGB(255, 0, 255));

	_colManager = new CollisionManager;
	_colManager->init(WINSIZEY * 10); //�� �� ���̸� �־��ٰ�

	_player = new player;
	_player->init();

	_colManager->linkPlayer(_player);
	_player->linkColManager(_colManager);

	_testIR._image = IMAGEMANAGER->addImage("�׽�Ʈ��ֹ�", "Image/Obstacles/enemy.bmp", 40, 40, true, RGB(255,0,255));
	_testIR._rc = RectMakeCenter(100, -40, 40,40);
	_testIRy = -40;
	
	_colManager->addIR(&_testIR); //�浹ó���� IR���� colManager�� �����ֱ�
	//_colManager->addIR(&_player->GetIR());

	_cameraY = 0;

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
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("���־�");
	}

	if (_colManager->GetGameover())
	{
		return;
	}

	//_cameraY -= 5;

	_player->update();

	if (_testIRy > -2 * WINSIZEY)
	{
		_testIRy -= 1;
	}
	_testIR._rc = RectMakeCenter(100, _testIRy, 40, 40);

	_colManager->update();
}

void SiwoongTest::render(void)
{
	_cameraY = _player->GetCamY();
	IMAGEMANAGER->findImage("background_jail")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _cameraY);

	//������Ʈ���� rc���� �۷ι� ��ǥ�� �����ϰ�
	//�����Ҷ� _cameraY���� �̿��� �÷��̾� ���� ���� ��ǥ�� ��ȯ
	if (_testIR._rc.top - _cameraY > 0 && _testIR._rc.top - _cameraY <= WINSIZEY)
	{ 
		_testIR._image->render(getMemDC(), _testIR._rc.left, _testIR._rc.top - _cameraY);
	}
	
	//_colManager->render();

	_player->render(_colManager->GetGameover());
}

SiwoongTest::SiwoongTest()
{
	_player = NULL;
}

SiwoongTest::~SiwoongTest()
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_colManager);
}