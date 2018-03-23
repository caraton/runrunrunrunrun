#include "stdafx.h"
#include "rectItem.h"
#include "MinseokTest.h"
#include "player.h"

HRESULT rectItem::init(void)
{
	m_pPosition = { WINSIZEX * 3 / 4, -400 };
	m_rc = RectMakeCenter(m_pPosition.x, m_pPosition.y, 50, 50);
	m_pSpeed = { 0,5 };

	m_rcObstacle = RectMakeCenter(WINSIZEX / 2, WINSIZEY * 3 / 4, 100, 100);
	return S_OK;
}

void rectItem::release(void)
{
}

void rectItem::update(void)
{
	POINT finalPos;
	finalPos = m_pPosition;
	if (!m_pPlayer)
	{
		m_pPosition.y += m_pSpeed.y;
	}
	
	
	else if (m_pPlayer)
	{
		POINT tempPoint;
		if (!m_pItem)
		{
			tempPoint = { m_pPlayer->GetPoint().x + 32,m_pPlayer->GetPoint().y + 70 };
			linearInterpol(&tempPoint, &finalPos, 0.8);
			//m_pPosition = m_pPlayer->GetPoint();
			//m_pPosition.y += 100;
		}
		else if (m_pItem)
		{
			tempPoint = { m_pItem->GetPos().x ,m_pItem->GetPos().y + 70 };
			linearInterpol(&tempPoint, &finalPos, 0.8);
			//m_pPosition = m_pItem->GetPos();
			//m_pPosition.y += 100;
		}

		m_rc = RectMakeCenter(finalPos.x, finalPos.y, 50, 50);


		m_pPosition = finalPos;

		
	}
	

	
	
	

	//랙트위치 재조정
	m_rc = RectMakeCenter(m_pPosition.x, m_pPosition.y, 50, 50);


	RECT temp;
	if (IntersectRect(&temp, &m_rcObstacle, &m_rc))
	{
		int interW = temp.right - temp.left;
		int interH = temp.bottom - temp.top;

		if (interW > interH)
		{
			POINT tempPoint;
			if (temp.top == m_rcObstacle.top)
			{
				//tempPoint = GetPos();
				//tempPoint.y -= interH;
				//finalPos = tempPoint;
				OffsetRect(&m_rc, 0, -interH);
			}
			else if (temp.bottom == m_rcObstacle.bottom)
			{
				//tempPoint = GetPos();
				//tempPoint.y += interH;
				//finalPos = tempPoint;
				OffsetRect(&m_rc, 0, interH);
			}

		}
		else
		{
			POINT tempPoint;
			if (temp.left == m_rcObstacle.left)
			{
				//tempPoint = GetPos();
				//tempPoint.x -= interW;
				//finalPos = tempPoint;
				OffsetRect(&m_rc, -interW, 0);
			}
			else if (temp.right == m_rcObstacle.right)
			{
				//tempPoint = GetPos();
				//tempPoint.x += interW;
				//finalPos = tempPoint;
				OffsetRect(&m_rc, interW, 0);
			}
		}
	}
}

void rectItem::render()
{
	Rectangle(getMemDC(), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
}


rectItem::rectItem()
{
	m_pPlayer = NULL;
	m_pItem = NULL;
}


rectItem::~rectItem()
{
}
