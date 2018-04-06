#include "stdafx.h"
#include "prisoner.h"
#include "player.h"


HRESULT prisoner::init(void)
{
	m_pPosition = { WINSIZEX * 3 / 4, -400 };
	m_pIR._rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
	m_pSpeed = { 0,0 };

	
	m_pIR._image = IMAGEMANAGER->addFrameImage("prisoner01", "Image/prisoner01_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));

	return S_OK;
	
}

void prisoner::release(void)
{
}

void prisoner::update(void)
{
	fPoint goalPoint;
	goalPoint = { 0.0f,0.0f };
	
	//�ص尡 ������ ��������
	if (!m_pHead)
	{
		m_pSpeed.y = 0;
	}

	//�ص尡 ������ �ص带 ����
	if (m_pHead)
	{
		float maxSpeed = 15.f;
		//�ص尡 �÷��̾��� ���
		if (m_eHeadType == t_player)
		{
		
			goalPoint = { ((player*)m_pHead)->GetPos().x ,((player*)m_pHead)->GetPos().y + 30 };
			m_pSpeed = linearInterpol(&goalPoint, &m_pPosition, 0.9) - m_pPosition;
			if (m_pSpeed.x >= maxSpeed) m_pSpeed.x = maxSpeed;
			else if (m_pSpeed.x <= -maxSpeed) m_pSpeed.x = -maxSpeed;
			if (m_pSpeed.y >= maxSpeed) m_pSpeed.y = maxSpeed;
			else if (m_pSpeed.y <= -maxSpeed) m_pSpeed.y = -maxSpeed;
		}
		//�ص尡 �������� ���
		else if (m_eHeadType == t_item)
		{
			goalPoint = { ((prisoner*)m_pHead)->GetPos().x ,((prisoner*)m_pHead)->GetPos().y + 30 };
			if (m_pSpeed.x >= maxSpeed) m_pSpeed.x = maxSpeed;
			else  if (m_pSpeed.x <= -maxSpeed) m_pSpeed.x = -maxSpeed;
			if (m_pSpeed.y >= maxSpeed) m_pSpeed.y = maxSpeed;
			else  if (m_pSpeed.y <= -maxSpeed) m_pSpeed.y = -maxSpeed;
		}
	}

	//obstacle ���� �浹������ ��� ����


	//�ӵ����޾Ƽ� �������� - �����浹 ���� ����****************************
	m_pPosition = m_pPosition + m_pSpeed;
	m_pIR._rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
	

	m_nImageFrameX = TIMEMANAGER->getFrameCount() / 10 % 6;
}

void prisoner::render(float cameraY)
{
	//���¿� �������� ��ȭ
	if (!m_pHead)
	{
		m_pIR._image->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY, 2, 0);
	}
	else if (m_pHead)
	{

		m_pIR._image->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY, m_nImageFrameX , 0);
	}
}

void prisoner::linkHead(void * Head, headType type)
{
	m_eHeadType = type;
	m_pHead = Head;
}

prisoner::prisoner()
{
	m_pHead = NULL;
	m_eHeadType = t_idle;
}


prisoner::~prisoner()
{
}
