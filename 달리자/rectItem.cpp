#include "stdafx.h"
#include "rectItem.h"
#include "MinseokTest.h"
#include "player.h"

HRESULT rectItem::init(void)
{
	m_pPosition = { WINSIZEX * 3 / 4, -400 };
	m_rc = RectMakeCenter(m_pPosition.x, m_pPosition.y, 50, 50);
	m_pSpeed = { 0,0 };

	m_rcObstacle = RectMakeCenter(WINSIZEX / 2, WINSIZEY * 3 / 4, 200, 200);

	
	return S_OK;
}

void rectItem::release(void)
{
}

void rectItem::update(void)
{
	fPoint goalPoint;
	goalPoint = { 0.0f,0.0f };
	if (!m_pPlayer)
	{
		m_pSpeed.y = 5;
	}
	
	//플레이어에게 종속되엇을때 속도를 계산해주는 함수
	else if (m_pPlayer)
	{
		float maxSpeed = 15.f;
		if (!m_pItem)
		{
			goalPoint = { m_pPlayer->GetPos().x + 32,m_pPlayer->GetPos().y + 70 };
			m_pSpeed.x = linearInterpol(&goalPoint, &m_pPosition, 0.9).x - m_pPosition.x;
			m_pSpeed.y = linearInterpol(&goalPoint, &m_pPosition, 0.9).y - m_pPosition.y;

			if (m_pSpeed.x >= maxSpeed) m_pSpeed.x = maxSpeed;
			else if (m_pSpeed.x <= -maxSpeed) m_pSpeed.x = -maxSpeed;
			if (m_pSpeed.y >= maxSpeed) m_pSpeed.y = maxSpeed;
			else if (m_pSpeed.y <= -maxSpeed) m_pSpeed.y = -maxSpeed;
			
		} 
		else if (m_pItem)
		{
			goalPoint = { m_pItem->GetPos().x ,m_pItem->GetPos().y + 70 };
			m_pSpeed.x = linearInterpol(&goalPoint, &m_pPosition, 0.9).x - m_pPosition.x;
			m_pSpeed.y = linearInterpol(&goalPoint, &m_pPosition, 0.9).y - m_pPosition.y;

			if (m_pSpeed.x >= maxSpeed) m_pSpeed.x = maxSpeed;
			else  if (m_pSpeed.x <= -maxSpeed) m_pSpeed.x = -maxSpeed;
			if (m_pSpeed.y >= maxSpeed) m_pSpeed.y = maxSpeed;
			else  if (m_pSpeed.y <= -maxSpeed) m_pSpeed.y = -maxSpeed;
		}
	}

	

	RECT temp;
	if (IntersectRect(&temp, &m_rcObstacle, &m_rc))
	{
		int interW = temp.right - temp.left;
		int interH = temp.bottom - temp.top;

		if (interW > interH)
		{
			
			//위쪽에서 충돌
			if (temp.top == m_rcObstacle.top)
			{
				//tempPoint = GetPos();
				//tempPoint.y -= interH;
				//finalPos = tempPoint;
				OffsetRect(&m_rc, 0, -interH);
				//if (goalPoint.y > m_pPosition.y)
				//{
					m_pSpeed.y = 0.0f;
				//}
				
			}
			else if (temp.bottom == m_rcObstacle.bottom)
			{
				//tempPoint = GetPos();
				//tempPoint.y += interH;
				//finalPos = tempPoint;
				OffsetRect(&m_rc, 0, interH);
				//if (goalPoint.y < m_pPosition.y)
				//{
					m_pSpeed.y = 0.0f;
				//}
			}

		}
		else
		{
			
			if (temp.left == m_rcObstacle.left)
			{
				//tempPoint = GetPos();
				//tempPoint.x -= interW;
				//finalPos = tempPoint;
				
				OffsetRect(&m_rc, -interW, 0);
				//if (goalPoint.x > m_pPosition.x)
				//{
					m_pSpeed.x = 0.0f;
				//}
				
			}
			else if (temp.right == m_rcObstacle.right)
			{
				//tempPoint = GetPos();
				//tempPoint.x += interW;
				//finalPos = tempPoint;
				
				OffsetRect(&m_rc, interW, 0);
				//if (goalPoint.x < m_pPosition.x)
				//{
					m_pSpeed.x = 0.0f;
				//}
				
			}
		}

		m_pPosition.x = (m_rc.right + m_rc.left) / 2;
		m_pPosition.y = (m_rc.bottom + m_rc.top) / 2;

	}

	//당연히 속도를받아서 움직여줌
	fPoint finalPos;
	finalPos.x = m_pPosition.x + m_pSpeed.x;
	finalPos.y = m_pPosition.y + m_pSpeed.y;
	RECT m_rc1 = RectMakeCenter(finalPos.x, m_pPosition.y, 50, 50);
	RECT m_rc2 = RectMakeCenter(m_pPosition.x, finalPos.y, 50, 50);
	if ( ! IntersectRect(&temp, &m_rcObstacle, &m_rc1))
	{
		m_pPosition.x = finalPos.x;
	}
	
	if (!IntersectRect(&temp, &m_rcObstacle, &m_rc2))
	{
		m_pPosition.y = finalPos.y;
	}

	m_rc = RectMakeCenter(m_pPosition.x, m_pPosition.y, 50, 50);

	

	
	
}

void rectItem::render(float cameraY)
{
	Rectangle(getMemDC(), m_rc.left, m_rc.top- cameraY, m_rc.right, m_rc.bottom - cameraY);
}


rectItem::rectItem()
{
	m_pPlayer = NULL;
	m_pItem = NULL;
}


rectItem::~rectItem()
{
}
