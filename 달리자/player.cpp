#include "stdafx.h"
#include "player.h"
#include "CollisionCheckManager.h"
#include "Items.h"
#include "prisoner.h"
#include "star.h"
#include "guards.h"

//슝아 너말이 맞는듯

//ToDoList: 속도 가속도
//아이템 슬롯은 벡터로
//can과 충돌시 밀려나기(can방향으로 이동하는것 막기)

//SiwoongTest에서 아이템들의 IR은 colManager에 저장하고
//player가 아이템을 먹은 후에
//player에 저장된 아이템의 정보는 (포인터)
//내부: 아이템을 사용하기 (또 플레이어가 취득한 죄수들은 플레이어 정보를 받아 이동)
//외부: 아이템 정보를 이용 (예: 3번째 먹은 아이템이 2번째 아이템의 포인터를 받아야함, )

//아이템 사용하기

HRESULT player::init(void)
{
	//이미지 관련 초기화 모음
	//m_pPlayerImage 라는 변수를 삭제해도 될듯
	m_IR._image = IMAGEMANAGER->addFrameImage("player_walk", "Image/player_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	_playerDeath = IMAGEMANAGER->addImage("player_down_50", "Image/player_down_50.bmp", 50, 50, true, RGB(255, 0, 255));
	m_pPlayerImage = m_IR._image;
	IMAGEMANAGER->addFrameImage("prisoner01_walk", "Image/prisoner01_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("guard_walk", "Image/guard_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	//플레이어 좌표 초기화(화면중앙)
	m_fpPosition.x = WINSIZEX / 2;
	m_fpPosition.y = WINSIZEY / 2;

	m_fCamaraY = 0;

	//물리값 관련 초기화
	m_fBasicSpeedY =  -5;
	m_fpSpeed = { 0.f,0.f };


	//IR 초기화
	//_IR._image = _playerImage;
	m_IR._rc = RectMake(m_fpPosition.x, m_fpPosition.y, 50, 50);

	//무적 초기화
	m_isStar = false;

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	move();
	
	if ((m_pColManager) && m_fCamaraY >= -(m_pColManager->GetMapLength() - WINSIZEY))
	{
		m_fCamaraY += m_fBasicSpeedY;
	}

	//무적 지속시간
	if (TIMEMANAGER->getWorldTime() - m_nStarStartTime >= 6.0f)
	{
		m_isStar = false;
	}

	//z,x,c,space bar
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) //상호작용
	{
		_test.clear();

		vector<IR*>* temp = new vector<IR*>;
		if (m_pColManager->findIRNear(&m_IR, temp))
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
	//if (KEYMANAGER->isOnceKeyDown('Z')) //이미지변경테스트
	//{
	//	m_IR._image = IMAGEMANAGER->findImage("prisoner01");
	//}
	//if (KEYMANAGER->isOnceKeyDown('X')) //이미지변경테스트
	//{
	//	m_IR._image = IMAGEMANAGER->findImage("guard");
	//}
	//if (KEYMANAGER->isOnceKeyDown('C')) //이미지변경테스트
	//{
	//	m_IR._image = IMAGEMANAGER->findImage("player");
	//}

	if (KEYMANAGER->isOnceKeyDown('K')) //아이템 사용
	{
		useItem();
	}

	m_IR._image->setFrameX((TIMEMANAGER->getFrameCount()/10) % 6);
	//이 이후에 충돌 체크를 해야 프레임 이미지에 맞게 픽셀충돌이 실행된다

	//플레이어 충돌처리 부분
	vector<IR*>* temp = new vector<IR*>;

	if (m_pColManager->checkCollision(&m_IR, temp))
	{
		for (_colIter = temp->begin(); _colIter != temp->end(); ++_colIter)
		{
			if (!strncmp((*_colIter)->_type, "devil", 10))
			{
				if (m_isStar) continue;
				m_IR._image = IMAGEMANAGER->findImage("playerDeath");
				m_pColManager->SetGameover(true);
				break;
			}
			else if (!strncmp((*_colIter)->_type, "can", 10))
			{

				fPoint tempf;
				tempf.x = ((*_colIter)->_rc.left + (*_colIter)->_rc.right) / 2;
				tempf.y = ((*_colIter)->_rc.top + (*_colIter)->_rc.bottom) / 2;
				fPoint tempm;
				tempm.x = 25;
				tempm.y = 25;

				float t = 1.00;

				while (pixelCol(&m_IR, *_colIter))
				{
					t = t + 0.07;
					m_fpPosition = (tempf + (((m_fpPosition + tempm) - tempf) * t)) - tempm;
					m_IR._rc = RectMake(m_fpPosition.x, m_fpPosition.y, 50, 50);
				}
				break;
			}
			else if (!strncmp((*_colIter)->_type, "prisoner", 10))
			{

				if (_items.size() < 3)
				{
					_items.push_back((prisoner *)(*_colIter)->_node);



					//아이템 이동관련
					if (_items.size() == 1)
					{
						(*_items.begin())->linkHead(this, t_player);
					}
					else
					{
						_items[_items.size() - 1]->linkHead(_items[_items.size() - 2], t_item);
						//(*(_items.end()--))->linkHead(*((_items.end()--)--), t_item);
					}
				}


				m_pColManager->deleteIR((*_colIter));
			}
			else if (!strncmp((*_colIter)->_type, "star", 10))
			{

				if (_items.size() < 3)
				{
					_items.push_back((star*)(*_colIter)->_node);


					//아이템 이동관련
					if (_items.size() == 1)
					{
						(*_items.begin())->linkHead(this, t_player);
					}
					else
					{
						_items[_items.size() - 1]->linkHead(_items[_items.size() - 2], t_item);
						//(*(_items.end()--))->linkHead(*((_items.end()--)--), t_item);
					}
				}


				m_pColManager->deleteIR((*_colIter));
			}
			else if (!strncmp((*_colIter)->_type, "smokeBomb", 10))
			{

				if (_items.size() < 3)
				{
					_items.push_back((star*)(*_colIter)->_node);


					//아이템 이동관련
					if (_items.size() == 1)
					{
						(*_items.begin())->linkHead(this, t_player);
					}
					else
					{
						_items[_items.size() - 1]->linkHead(_items[_items.size() - 2], t_item);
						//(*(_items.end()--))->linkHead(*((_items.end()--)--), t_item);
					}
				}


				m_pColManager->deleteIR((*_colIter));
			}
			else if (!strncmp((*_colIter)->_type, "deadline", 10))
			{
				if (m_isStar)
				{
					guards* guardTemp;
					guardTemp = (guards*)(*_colIter)->_node;
					m_fpSpeed = guardTemp->GetSpeed();
					//fPoint tempf;
					//tempf.x = ((*_colIter)->_rc.left + (*_colIter)->_rc.right) / 2;
					//tempf.y = ((*_colIter)->_rc.top + (*_colIter)->_rc.bottom) / 2;
					//fPoint tempm;
					//tempm.x = 25;
					//tempm.y = 25;
					//
					//float t = 1.00;

					while (pixelCol(&m_IR, *_colIter))
					{
						//m_fBasicSpeedY += 0.2f;
						m_fpPosition.y -= 2.0f;
						m_IR._rc = RectMake(m_fpPosition.x, m_fpPosition.y, 50, 50);
					}
					break;
					continue;
				}
				m_IR._image = IMAGEMANAGER->findImage("player_down_50");
				m_pColManager->SetGameover(true);
				break;
			}
		}
	}

	SAFE_DELETE(temp);
}

void player::render(float cameraY)
{
	m_IR._image->frameRender(getMemDC(), m_fpPosition.x, m_fpPosition.y- cameraY);
	for (_testIter = _test.begin(); _testIter != _test.end(); ++_testIter)
	{
		Rectangle(getMemDC(), (*_testIter).left, (*_testIter).top - cameraY, (*_testIter).right, (*_testIter).bottom - cameraY);
	}
}

void player::render()
{
	m_IR._image->frameRender(getMemDC(), m_fpPosition.x, m_fpPosition.y - m_fCamaraY);
	for (_testIter = _test.begin(); _testIter != _test.end(); ++_testIter)
	{
		Rectangle(getMemDC(), (*_testIter).left, (*_testIter).top - m_fCamaraY, (*_testIter).right, (*_testIter).bottom - m_fCamaraY);
	}
}


void player::render(bool gameover)
{
	if (!gameover)
	{
		m_IR._image->frameRender(getMemDC(), m_fpPosition.x, m_fpPosition.y - m_fCamaraY);
	}
	else
	{
		m_IR._image->render(getMemDC(), m_fpPosition.x, m_fpPosition.y - m_fCamaraY);
	}

	for (_testIter = _test.begin(); _testIter != _test.end(); ++_testIter)
	{
		Rectangle(getMemDC(), (*_testIter).left, (*_testIter).top - m_fCamaraY, (*_testIter).right, (*_testIter).bottom - m_fCamaraY);
	}
}


void player::move()
{


	//달리기 속도 조절
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		m_fBasicSpeedY += 2;
		if (m_fBasicSpeedY >= -1)
		{
			m_fBasicSpeedY = -1;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('X'))
	{
		m_fBasicSpeedY -= 2;
		if (m_fBasicSpeedY <= -9)
		{
			m_fBasicSpeedY = -9;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('C'))
	{
		m_fBasicSpeedY = 0;
	}




	//상하이동
	if (KEYMANAGER->isStayKeyDown(VK_UP) && m_fpPosition.y - m_fCamaraY > 0)
	{
		//_cameraY -= 5;
		m_fpSpeed.y = -10 + m_fBasicSpeedY;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_fpPosition.y - m_fCamaraY < WINSIZEY)
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

void player::useItem()
{
	if (_items.size() == 0) return;
	else 
	{
		if (!strncmp(_items[0]->GetIR()->_type, "prisoner", 10))
		{
			_items[0]->SetFire(true);
			//아이템 사용효과를 넣어줄것
		}
		else if (!strncmp(_items[0]->GetIR()->_type, "star", 10))
		{
			m_nStarStartTime = TIMEMANAGER->getWorldTime();
			m_isStar = true;
			_items[0]->SetAlive(false);
		}
		else if (!strncmp(_items[0]->GetIR()->_type, "smokeBomb", 10))
		{

			_items[0]->SetFire(true);
			_items[0]->SetStartTime(TIMEMANAGER->getWorldTime());
		}


		//사용한 아이템을 없애줌
		
		vector<Items*> temp;
		if (_items.size() == 1)
		{
			_items.clear();
			return;
		}
		else
		{
			for (int i = 1; i < _items.size(); i++)
			{
				temp.push_back(_items[i]);
				if (temp.size() == 1)
				{
					(*temp.begin())->linkHead(this, t_player);
				}
				else
				{
					_items[_items.size() - 1]->linkHead(_items[_items.size() - 2], t_item);
					//(*(_items.end()--))->linkHead(*((_items.end()--)--), t_item);
				}
			}
			_items.clear();
			_items = temp;
			
		}

	}

}






player::player()
{
	m_pPlayerImage = NULL;
	m_pColManager = NULL;
}

player::~player()
{
}

