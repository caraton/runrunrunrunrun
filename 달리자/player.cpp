#include "stdafx.h"
#include "player.h"
#include "CollisionManager.h"

//���� �ʸ��� �´µ�

//ToDoList: �ӵ� ���ӵ�
//

HRESULT player::init(void)
{
	//�̹��� ���� �ʱ�ȭ ����
	_playerImage = IMAGEMANAGER->addFrameImage("player", "Image/player_walk.bmp", 200, 50, 4, 1, true, RGB(255, 0, 255));

	//�÷��̾� ��ǥ �ʱ�ȭ(ȭ���߾�)
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;

	_cameraY = WINSIZEY / 2;

	//IR �ʱ�ȭ
	_IR._image = _playerImage;
	_IR._rc = RectMake(_player.x, _player.y, 50, 50);

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	//�����̵�
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

	//�¿��̵�
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
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) //��ȣ�ۿ�
	{
		_test.clear();

		vector<IR*>* temp = new vector<IR*>;
		if (_colManager->findIRNear(&_IR, temp))
		{
			//�ֺ��� ���𰡰� �־ temp�� �����
			vector<IR*>::iterator iter;
			for (iter = temp->begin(); iter != temp->end(); ++iter)
			{
				RECT temp = (*iter)->_rc;
				_test.push_back(temp);
			}
		}

		//�پ� temp�����
		SAFE_DELETE(temp);
	}

	_IR._image->setFrameX((TIMEMANAGER->getFrameCount()/10) % 4);
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
