#include "stdafx.h"
#include "player.h"

//���� �ʸ��� �´µ�

HRESULT player::init(void)
{
	//�÷��̾� ��ǥ �ʱ�ȭ(ȭ���߾�)
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;

	//�̹��� ���� �ʱ�ȭ ����
	_playerImage = IMAGEMANAGER->addImage("player", "plane.bmp", 64, 64, true, RGB(255, 0, 255));

	//IR �ʱ�ȭ
	_IR._image = _playerImage;
	_IR._rc = RectMake(_player.x, _player.y, 64, 64);

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	//�����̵�
	if (KEYMANAGER->isStayKeyDown('W') && _player.y > 0)
	{
		_player.y -= 5;
	}
	if (KEYMANAGER->isStayKeyDown('S') && _player.y + 64 < WINSIZEY)
	{
		_player.y += 5;
	}

	//�¿��̵�
	if (KEYMANAGER->isStayKeyDown('A') && _player.x > 0)
	{
		_player.x -= 5;
	}
	if (KEYMANAGER->isStayKeyDown('D') && _player.x + 64 <WINSIZEX)
	{
		_player.x += 5;
	}
}

void player::render()
{
	_IR._image->render(getMemDC(), _player.x, _player.y);
}

player::player()
{
	_playerImage = NULL;
}

player::~player()
{
}
