#include "stdafx.h"
#include "rectItem.h"
#include "MinseokTest.h"
#include "player.h"

HRESULT rectItem::init(void)
{
	m_pPosition = { WINSIZEX * 3 / 4, -400 };
	m_pIR._rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
	m_pSpeed = { 0,0 };

	m_rcObstacle = RectMakeCenter(WINSIZEX / 2, WINSIZEY * 3 / 4, 200, 200);
	m_pIR._image = IMAGEMANAGER->addFrameImage("prisoner02", "Image/guard_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	
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
		m_pSpeed.y = 0;
	}
	
	//플레이어에게 종속되엇을때 속도를 계산해주는 함수
	if (m_pPlayer)
	{
		float maxSpeed = 15.f;
		if (!m_pItem)
		{
			goalPoint = { m_pPlayer->GetPos().x ,m_pPlayer->GetPos().y +30 };
			m_pSpeed.x = linearInterpol(&goalPoint, &m_pPosition, 0.9).x - m_pPosition.x;
			m_pSpeed.y = linearInterpol(&goalPoint, &m_pPosition, 0.9).y - m_pPosition.y;

			if (m_pSpeed.x >= maxSpeed) m_pSpeed.x = maxSpeed;
			else if (m_pSpeed.x <= -maxSpeed) m_pSpeed.x = -maxSpeed;
			if (m_pSpeed.y >= maxSpeed) m_pSpeed.y = maxSpeed;
			else if (m_pSpeed.y <= -maxSpeed) m_pSpeed.y = -maxSpeed;
			
		} 
		else if (m_pItem)
		{
			goalPoint = { m_pItem->GetPos().x ,m_pItem->GetPos().y + 30 };
			m_pSpeed.x = linearInterpol(&goalPoint, &m_pPosition, 0.9).x - m_pPosition.x;
			m_pSpeed.y = linearInterpol(&goalPoint, &m_pPosition, 0.9).y - m_pPosition.y;

			if (m_pSpeed.x >= maxSpeed) m_pSpeed.x = maxSpeed;
			else  if (m_pSpeed.x <= -maxSpeed) m_pSpeed.x = -maxSpeed;
			if (m_pSpeed.y >= maxSpeed) m_pSpeed.y = maxSpeed;
			else  if (m_pSpeed.y <= -maxSpeed) m_pSpeed.y = -maxSpeed;
		}
	}
	
	
	//물체를 옮겨줌 - 지울것
	m_rcObstacle.top -= 5;
	m_rcObstacle.bottom -= 5;

	
	
	//물체와 충돌하엿을경우의 계산
	RECT temp;
	/*RECT thisRCTemp;
	thisRCTemp = m_pIR._rc;
	thisRCTemp.top += m_pSpeed.y;*/
	if (IntersectRect(&temp, &m_rcObstacle, &m_pIR._rc))
	{
		int interW = temp.right - temp.left;
		int interH = temp.bottom - temp.top;

		if (interW > interH)
		{
			float m_pObstacleSpeed = -5.0f;

			//위쪽에서 충돌
			if (temp.top == m_rcObstacle.top)
			{
				//tempPoint = GetPos();
				//tempPoint.y -= interH;
				//finalPos = tempPoint;
				OffsetRect(&m_pIR._rc, 0, -interH);
				//if (goalPoint.y > m_pPosition.y)
				//{
					m_pSpeed.y = m_pObstacleSpeed;
				//}

				
			}
			else if (temp.bottom == m_rcObstacle.bottom)
			{
				//tempPoint = GetPos();
				//tempPoint.y += interH;
				//finalPos = tempPoint;
				OffsetRect(&m_pIR._rc, 0, interH);
				//if (goalPoint.y < m_pPosition.y)
				//{
					m_pSpeed.y = m_pObstacleSpeed;
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
				
				OffsetRect(&m_pIR._rc, -interW, 0);
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
				
				OffsetRect(&m_pIR._rc, interW, 0);
				//if (goalPoint.x < m_pPosition.x)
				//{
					m_pSpeed.x = 0.0f;
				//}
				
			}
		}

		m_pPosition.x = m_pIR._rc.left;
		m_pPosition.y =  m_pIR._rc.top;

	}

	

	//당연히 속도를받아서 움직여줌
	fPoint finalPos;
	finalPos.x = m_pPosition.x + m_pSpeed.x;
	finalPos.y = m_pPosition.y + m_pSpeed.y;
	RECT m_rc1 = RectMake(finalPos.x, m_pPosition.y, 50, 50);
	RECT m_rc2 = RectMake(m_pPosition.x, finalPos.y, 50, 50);
	if (!IntersectRect(&temp, &m_rcObstacle, &m_rc1))
	{
		m_pPosition.x = finalPos.x;
	}
	
	if (!IntersectRect(&temp, &m_rcObstacle, &m_rc2))
	{

		m_pPosition.y = finalPos.y;
	}

	m_pIR._rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
	

	//이미지 프레임 돌려주기
 	m_pIR._image->setFrameX((TIMEMANAGER->getFrameCount() / 10 ) % 6);



	

}

void rectItem::render(float cameraY)
{
	//Rectangle(getMemDC(), m_rcObstacle.left, m_rcObstacle.top - cameraY, m_rcObstacle.right, m_rcObstacle.bottom - cameraY);



	Rectangle(getMemDC(), m_pIR._rc.left, m_pIR._rc.top- cameraY, m_pIR._rc.right, m_pIR._rc.bottom - cameraY);


	

	

	//상태에 따른랜더 변화
	if (!m_pPlayer)
	{
		m_pIR._image->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY, 2, 0);
	}
	else
	{
		m_pIR._image->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY);
	}

	
}



rectItem::rectItem()
{
	m_pPlayer = NULL;
	m_pItem = NULL;
}


rectItem::~rectItem()
{
}
