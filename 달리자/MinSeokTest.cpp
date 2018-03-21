#include "stdafx.h"
#include "MinseokTest.h"
#include "rectItem.h"

HRESULT MinseokTest::init(void)
{
	m_rPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 40, 40);
	
	m_pItem = new rectItem;
	m_pItem->init();

	return S_OK;
}

void MinseokTest::release(void)
{
}

void MinseokTest::update(void)
{
	//Å×½ºÆ®¾À ³¢¸®ÀÇ ¾ÀÀüÈ¯
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("½Ã¿õ¾À");
	}


	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_rPlayer.top -= 5;
		m_rPlayer.bottom -= 5;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_rPlayer.left -= 5;
		m_rPlayer.right -= 5;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_rPlayer.top += 5;
		m_rPlayer.bottom += 5;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_rPlayer.left += 5;
		m_rPlayer.right += 5;
	}


	m_pItem->update();



}

void MinseokTest::render()
{
	Rectangle(getMemDC(), m_rPlayer.left, m_rPlayer.top, m_rPlayer.right, m_rPlayer.bottom);
	m_pItem->render();
}

MinseokTest::MinseokTest()
{
	m_pItem = NULL;
}


MinseokTest::~MinseokTest()
{
	SAFE_DELETE(m_pItem);
}
