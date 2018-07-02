#include "stdafx.h"
#include "prisoner.h"
#include "player.h"
#include "CollisionCheckManager.h"

HRESULT prisoner::init(void)
{
	m_isAlive = true;
	m_pPosition = { WINSIZEX * 3 / 4, -400 };
	m_pIR = new IR;
	m_pIR->_rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
	m_pSpeed = { 0,0 };

	m_pIR->_type = "prisoner";
	m_pIR->_node = this;
	m_pIR->_image = IMAGEMANAGER->addFrameImage("prisoner01", "Image/prisoner01_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	m_isFire = false;

	return S_OK;
	
}

void prisoner::release(void)
{
}

void prisoner::update(void)
{
	if (!m_isAlive) return;
	fPoint goalPoint;
	goalPoint = { 0.0f,0.0f };

	//발사중이면 날라감
	if (m_isFire)
	{
		m_pSpeed = { 0.f,-15.0f };


		//발사중 오브젝트와 부딛힌다면?! - 오브젝트를 파괴함
		vector<IR*>* temp = new vector<IR*>;
		if (m_pColManager->checkCollision(m_pIR, temp))
		{
			for (_colIter = temp->begin(); _colIter != temp->end(); ++_colIter)
			{
				if (!strncmp((*_colIter)->_type, "can", 10))
				{
					IR* temp = *_colIter;
					m_pColManager->deleteIR(*_colIter);
					//SAFE_DELETE(temp);
				}
			}
		}


		//일정 거리를 날라가면 없어짐
		if (m_pPosition.y - m_nCameraY < 0)
		{
			m_isFire = false;
			m_isAlive = false;
		}
	}
	
	//해드가 없으면 멈춰있음
	else if (!m_pHead)
	{
		m_pSpeed.y = 0;
	}

	//해드가 있으면 해드를 따라감
	else if (m_pHead)
	{
		float maxSpeed = 15.f;
		//해드가 플레이어일 경우
		if (m_eHeadType == t_player)
		{
		
			goalPoint = { ((player*)m_pHead)->GetPos().x ,((player*)m_pHead)->GetPos().y + 30 };
			m_pSpeed = linearInterpol(&goalPoint, &m_pPosition, 0.9) - m_pPosition;
			if (m_pSpeed.x >= maxSpeed) m_pSpeed.x = maxSpeed;
			else if (m_pSpeed.x <= -maxSpeed) m_pSpeed.x = -maxSpeed;
			if (m_pSpeed.y >= maxSpeed) m_pSpeed.y = maxSpeed;
			else if (m_pSpeed.y <= -maxSpeed) m_pSpeed.y = -maxSpeed;
		}
		//해드가 아이템일 경우
		else if (m_eHeadType == t_item)
		{
			goalPoint = { ((Items*)m_pHead)->GetPos().x ,((Items*)m_pHead)->GetPos().y + 30 };
			m_pSpeed = linearInterpol(&goalPoint, &m_pPosition, 0.9) - m_pPosition;
			if (m_pSpeed.x >= maxSpeed) m_pSpeed.x = maxSpeed;
			else  if (m_pSpeed.x <= -maxSpeed) m_pSpeed.x = -maxSpeed;
			if (m_pSpeed.y >= maxSpeed) m_pSpeed.y = maxSpeed;
			else  if (m_pSpeed.y <= -maxSpeed) m_pSpeed.y = -maxSpeed;
		}
	}

	//obstacle 과의 충돌연산은 잠시 생략


	//속도를받아서 움직여줌 - 가상충돌 적용 안함****************************
	m_pPosition = m_pPosition + m_pSpeed;
	m_pIR->_rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
	
	if (m_pHead)
	{
		m_nImageFrameX = TIMEMANAGER->getFrameCount() / 10 % 6;
	}
	
}

void prisoner::render(float cameraY)
{
	m_nCameraY = cameraY;
	if (!m_isAlive) return;
	//상태에 따른랜더 변화
	if (!m_pHead)
	{
		m_pIR->_image->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY, 2, 0);
	}
	else if (m_pHead)
	{

		m_pIR->_image->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY, m_nImageFrameX , 0);
	}
}



prisoner::prisoner()
{
	m_pHead = NULL;
	m_eHeadType = t_idle;
}


prisoner::~prisoner()
{
}
