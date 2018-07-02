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

	//�߻����̸� ����
	if (m_isFire)
	{
		m_pSpeed = { 0.f,-15.0f };


		//�߻��� ������Ʈ�� �ε����ٸ�?! - ������Ʈ�� �ı���
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


		//���� �Ÿ��� ���󰡸� ������
		if (m_pPosition.y - m_nCameraY < 0)
		{
			m_isFire = false;
			m_isAlive = false;
		}
	}
	
	//�ص尡 ������ ��������
	else if (!m_pHead)
	{
		m_pSpeed.y = 0;
	}

	//�ص尡 ������ �ص带 ����
	else if (m_pHead)
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
			goalPoint = { ((Items*)m_pHead)->GetPos().x ,((Items*)m_pHead)->GetPos().y + 30 };
			m_pSpeed = linearInterpol(&goalPoint, &m_pPosition, 0.9) - m_pPosition;
			if (m_pSpeed.x >= maxSpeed) m_pSpeed.x = maxSpeed;
			else  if (m_pSpeed.x <= -maxSpeed) m_pSpeed.x = -maxSpeed;
			if (m_pSpeed.y >= maxSpeed) m_pSpeed.y = maxSpeed;
			else  if (m_pSpeed.y <= -maxSpeed) m_pSpeed.y = -maxSpeed;
		}
	}

	//obstacle ���� �浹������ ��� ����


	//�ӵ����޾Ƽ� �������� - �����浹 ���� ����****************************
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
	//���¿� �������� ��ȭ
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
