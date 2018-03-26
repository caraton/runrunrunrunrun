#include "stdafx.h"
#include "player.h"
#include "CollisionManager.h"

//슝아 너말이 맞는듯

//ToDoList: 속도 가속도
//

HRESULT player::init(void)
{
	//이미지 관련 초기화 모음
	_playerImage = IMAGEMANAGER->addFrameImage("player", "Image/player_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("prisoner01", "Image/prisoner01_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("guard", "Image/guard_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	//플레이어 좌표 초기화(화면중앙)
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;

	_cameraY = WINSIZEY / 2;

	//IR 초기화
	_IR._image = _playerImage;
	_IR._rc = RectMake(_player.x, _player.y, 50, 50);

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	//상하이동
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player.y > 0)
	{
		//_cameraY -= 5;
		_player.y -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player.y + 64 < WINSIZEY)
	{
		//_cameraY += 5;
		_player.y += 5;
	}

	//좌우이동
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player.x > 0)
	{
		_player.x -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player.x + 64 <WINSIZEX)
	{
		_player.x += 5;
	}

	_IR._rc = RectMake(_player.x, _player.y, 50, 50);

	//z,x,c,space bar
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) //상호작용
	{
		_test.clear();

		vector<IR*>* temp = new vector<IR*>;
		if (_colManager->findIRNear(&_IR, temp))
		{
			//주변에 무언가가 있어서 temp에 저장됨
			vector<IR*>::iterator iter;
			for (iter = temp->begin(); iter != temp->end(); ++iter)
			{
				RECT temp = (*iter)->_rc;
				_test.push_back(temp);
			}
		}

		//다쓴 temp지우기
		SAFE_DELETE(temp);
	}
	if (KEYMANAGER->isOnceKeyDown('Z')) //이미지변경테스트
	{
		_IR._image = IMAGEMANAGER->findImage("prisoner01");
	}
	if (KEYMANAGER->isOnceKeyDown('X')) //이미지변경테스트
	{
		_IR._image = IMAGEMANAGER->findImage("guard");
	}
	if (KEYMANAGER->isOnceKeyDown('C')) //이미지변경테스트
	{
		_IR._image = IMAGEMANAGER->findImage("player");
	}

	_IR._image->setFrameX((TIMEMANAGER->getFrameCount()/10) % 6);
}

void player::render()
{
	_IR._image->frameRender(getMemDC(), _player.x, _player.y);
	for (_testIter = _test.begin(); _testIter != _test.end(); ++_testIter)
	{
		Rectangle(getMemDC(), (*_testIter).left, (*_testIter).top, (*_testIter).right, (*_testIter).bottom);
	}
}

player::player()
{
	_playerImage = NULL;
	_colManager = NULL;
}

player::~player()
{
}
