#include "stdafx.h"
#include "star.h"
#include "player.h"


HRESULT star::init(void)
{
	m_isAlive = true;
	m_pPosition = { WINSIZEX * 3 / 4, -400 };
	m_pIR = new IR;
	m_pIR->_rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
	m_pSpeed = { 0,0 };

	m_pHead = NULL;
	m_pIR->_type = "star";
	m_pIR->_node = this;
	m_pImageStarSize = IMAGEMANAGER->addFrameImage("star_size", "Image/Items/star_size.bmp", 100, 50, 2, 1, true, RGB(255, 0, 255));
	m_pImageStarRotate = IMAGEMANAGER->addFrameImage("star_rotate", "Image/Items/star_rotate.bmp", 100, 50, 2, 1, true, RGB(255, 0, 255));
	m_pIR->_image = m_pImageStarSize;
	return S_OK;
}

void star::release(void)
{
}

void star::update(void)
{
	if (!m_isAlive) return;
	fPoint goalPoint;
	goalPoint = { 0.0f,0.0f };

	//해드가 없으면 멈춰있음
	if (!m_pHead)
	{
		m_pSpeed.y = 0;
	}

	//해드가 있으면 해드를 따라감
	if (m_pHead)
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


	
	m_nImageFrameX = TIMEMANAGER->getFrameCount() / 10 % 2;
	
}

void star::render(float cameraY)
{

	if (!m_isAlive) return;
	if (!m_pHead)
	{
		m_pImageStarSize->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY, m_nImageFrameX, 0);
	}
	else if (m_pHead)
	{

		m_pImageStarRotate->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY, m_nImageFrameX, 0);
	}
}

star::star()
{
	m_pHead = NULL;
	m_eHeadType = t_idle;
}


star::~star()
{
}
