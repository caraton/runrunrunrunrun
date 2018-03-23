#include "stdafx.h"
#include "rectItem.h"
#include "MinseokTest.h"
#include "player.h"

HRESULT rectItem::init(void)
{
	m_pPosition = { WINSIZEX * 3 / 4, -400 };
	m_rc = RectMakeCenter(m_pPosition.x, m_pPosition.y, 50, 50);
	m_pSpeed = { 0,5 };
	return S_OK;
}

void rectItem::release(void)
{
}

void rectItem::update(void)
{
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
			linearInterpol(&tempPoint, &m_pPosition, 0.9);
			//m_pPosition = m_pPlayer->GetPoint();
			//m_pPosition.y += 100;
		}
		else if (m_pItem)
		{
			tempPoint = { m_pItem->GetPos().x ,m_pItem->GetPos().y + 70 };
			linearInterpol(&tempPoint, &m_pPosition, 0.9);
			//m_pPosition = m_pItem->GetPos();
			//m_pPosition.y += 100;
		}
	}




	//랙트위치 재조정
	m_rc = RectMakeCenter(m_pPosition.x, m_pPosition.y, 50, 50);
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
