#include "stdafx.h"
#include "player.h"

//슝아 너말이 맞는듯

HRESULT player::init(void)
{
	//플레이어 좌표 초기화(화면중앙)
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;

	//이미지 관련 초기화 모음
	_playerImage = IMAGEMANAGER->addImage("player", "plane.bmp", 64, 64, true, RGB(255, 0, 255));

	//IR 초기화
	_IR._image = _playerImage;
	_IR._rc = RectMake(_player.x, _player.y, 64, 64);

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	//상하이동
	if (KEYMANAGER->isStayKeyDown('W') && _player.y > 0)
	{
		_player.y -= 5;
	}
	if (KEYMANAGER->isStayKeyDown('S') && _player.y + 64 < WINSIZEY)
	{
		_player.y += 5;
	}

	//좌우이동
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
