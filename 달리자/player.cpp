#include "stdafx.h"
#include "player.h"
#include "CollisionManager.h"

//슝아 너말이 맞는듯

//ToDoList: 속도 가속도
//


HRESULT player::init(void)
{
	//이미지 관련 초기화 모음
	//m_pPlayerImage 라는 변수를 삭제해도 될듯
	m_IR._image = IMAGEMANAGER->addFrameImage("player", "Image/player_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	m_pPlayerImage = m_IR._image;
	IMAGEMANAGER->addFrameImage("prisoner01", "Image/prisoner01_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("guard", "Image/guard_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	//플레이어 좌표 초기화(화면중앙)
	m_fpPosition.x = WINSIZEX / 2;
	m_fpPosition.y = WINSIZEY / 2;

	_cameraY = 0;

	//물리값 관련 초기화
	m_fBasicSpeedY =  -5;
	m_fpSpeed = { 0.f,0.f };


	//IR 초기화
	//_IR._image = _playerImage;
	m_IR._rc = RectMake(m_fpPosition.x, m_fpPosition.y, 50, 50);

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	if (_cameraY >= -(_colManager->GetMapLength() -WINSIZEY))
	{
		_cameraY -= 5;
	}

	move();
	

	//z,x,c,space bar
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) //상호작용
	{
		_test.clear();

		vector<IR*>* temp = new vector<IR*>;
		if (_colManager->findIRNear(&m_IR, temp))
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
		m_IR._image = IMAGEMANAGER->findImage("prisoner01");
	}
	if (KEYMANAGER->isOnceKeyDown('X')) //이미지변경테스트
	{
		m_IR._image = IMAGEMANAGER->findImage("guard");
	}
	if (KEYMANAGER->isOnceKeyDown('C')) //이미지변경테스트
	{
		m_IR._image = IMAGEMANAGER->findImage("player");
	}

	m_IR._image->setFrameX((TIMEMANAGER->getFrameCount()/10) % 6);
}

void player::render()
{
	m_IR._image->frameRender(getMemDC(), m_fpPosition.x, m_fpPosition.y - _cameraY);
	for (_testIter = _test.begin(); _testIter != _test.end(); ++_testIter)
	{
		Rectangle(getMemDC(), (*_testIter).left, (*_testIter).top - _cameraY, (*_testIter).right, (*_testIter).bottom - _cameraY);
	}
}


void player::move()
{

	
	//상하이동
	if (KEYMANAGER->isStayKeyDown(VK_UP) && m_fpPosition.y - _cameraY > 0)
	{
		//_cameraY -= 5;
		m_fpSpeed.y = -10 + m_fBasicSpeedY;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_fpPosition.y - _cameraY < WINSIZEY)
	{
		//_cameraY += 5;
		m_fpSpeed.y = 10 + m_fBasicSpeedY;
	}
	else
	{
		m_fpSpeed.y = m_fBasicSpeedY;
	}

	//좌우이동
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_fpPosition.x > 0)
	{
		m_fpSpeed.x = -5;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_fpPosition.x + 64 <WINSIZEX)
	{
		m_fpSpeed.x = 5;
	}
	else
	{
		m_fpSpeed.x = 0;
	}


	//속도를 받아 이동해줌
	m_fpPosition.x += m_fpSpeed.x;
	m_fpPosition.y += m_fpSpeed.y;
	m_IR._rc = RectMake(m_fpPosition.x, m_fpPosition.y, 50, 50);
}






player::player()
{
	m_pPlayerImage = NULL;
	_colManager = NULL;
}

player::~player()
{
}

