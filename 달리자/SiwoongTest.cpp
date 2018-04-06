#include "stdafx.h"
#include "SiwoongTest.h"
#include "player.h"
#include "CollisionManager.h"

HRESULT SiwoongTest::init(void)
{
	IMAGEMANAGER->addImage("background_jail", "Image/background_jail.bmp", 600, 800, true, RGB(255, 0, 255));

	_colManager = new CollisionManager;
	_colManager->init(WINSIZEY * 2); //맵 총 길이를 넣어줄것

	_player = new player;
	_player->init();

	_colManager->linkPlayer(_player);
	_player->linkColManager(_colManager);

	_testIR._image = IMAGEMANAGER->addImage("테스트장애물", "Image/Obstacles/enemy.bmp", 40, 40, true, RGB(255,0,255));
	_testIR._rc = RectMakeCenter(100, -40, 40,40);
	_testIR._type = "devil";
	_testIRy = -40;

	for (int i = 0; i < _colManager->GetMapLength()/ 100; ++i)
	{
		IR temp;
		temp._image = IMAGEMANAGER->addImage("테스트장애물2", "Image/Obstacles/object_can.bmp", 50, 50, true, RGB(255, 0, 255));
		temp._rc = RectMakeCenter(WINSIZEX / 2 - 100, 25 + i*100 - _colManager->GetMapLength() + WINSIZEY,50,50);
		temp._type = "can";
		_trashcans.push_back(temp);
	}
	
	_colManager->addIR(&_testIR); //충돌처리할 IR들을 colManager에 보내주기
	for (_tcIter = _trashcans.begin(); _tcIter != _trashcans.end(); ++_tcIter)
	{
		_colManager->addIR(&*_tcIter);
	}
	_colManager->addIR(&_player->GetIR());

	_cameraY = 0;

	return S_OK;
}

void SiwoongTest::release(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_colManager);
}

void SiwoongTest::update(void)
{
	//민석씬 이동
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("민석씬");
		return; //changeScene을 하면 이 SiwoongTest의 release 함수가 실행되지만
		//changeScene이 실행된 update는 한번끝까지 실행되버린다 
		//release에서 _colManager를 지우고 밑에서 _colManager->GetGameover()를 하므로 터짐
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("영휘씬");
		return;
	}

	if (_colManager->GetGameover())
	{
		return;
	}

	//_cameraY -= 5;

	_player->update();

	if (_testIRy > -2*WINSIZEY +1)
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

	//오브젝트들의 rc에는 글로벌 좌표를 저장하고
	//렌더할때 _cameraY값을 이용해 플레이어 기준 로컬 좌표로 변환
	if (_testIR._rc.top - _cameraY > 0 && _testIR._rc.top - _cameraY <= WINSIZEY)
	{ 
		_testIR._image->render(getMemDC(), _testIR._rc.left, _testIR._rc.top - _cameraY);
	}

	for (_tcIter = _trashcans.begin(); _tcIter != _trashcans.end(); ++_tcIter)
	{
		if ((*_tcIter)._rc.top - _cameraY > 0 && (*_tcIter)._rc.top - _cameraY <= WINSIZEY)
		{
			(*_tcIter)._image->render(getMemDC(), (*_tcIter)._rc.left, (*_tcIter)._rc.top - _cameraY);
		}
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