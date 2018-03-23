#include "stdafx.h"
#include "MinseokTest.h"
#include "rectItem.h"
#include "player.h"

HRESULT MinseokTest::init(void)
{
	m_rPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 40, 40);
	
	m_pItem = new rectItem;
	m_pItem->init();

	m_pPlayer = new player;
	m_pPlayer->init();

	return S_OK;
}

void MinseokTest::release(void)
{
}

void MinseokTest::update(void)
{
	//�׽�Ʈ�� ������ ����ȯ
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("�ÿ���");
	}

	m_pPlayer->update();
	m_pItem->update();



}

void MinseokTest::render()
{
	//�ÿ����� �� �ް����� �ϱ����� ��Ʈ
	Rectangle(getMemDC(), 0, 0, 100, 100);
	m_pPlayer->render();
	m_pItem->render();
}

MinseokTest::MinseokTest()
{
	m_pItem = NULL;
	m_pPlayer = NULL;
}


MinseokTest::~MinseokTest()
{
	SAFE_DELETE(m_pItem);
	SAFE_DELETE(m_pPlayer);
}
