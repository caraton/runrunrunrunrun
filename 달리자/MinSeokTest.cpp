#include "stdafx.h"
#include "MinseokTest.h"
#include "rectItem.h"
#include "player.h"
#include "CollisionManager.h"
#include "prisoner.h"
#include "Obstacles.h"

HRESULT MinseokTest::init(void)
{
	
	m_pItem = new rectItem;
	m_pItem->init();

	m_pItem2 = new rectItem;
	m_pItem2->init();
	m_pItem2->SetPos(fPoint{ WINSIZEX/2, - 1000 });

	m_pPlayer = new player;
	m_pPlayer->init();

	m_pBack = new MinseokBack;
	m_pBack->init();

	m_pColManager = new CollisionManager;
	m_pColManager->init(WINSIZEY * 10);

	m_pBack->linkPlayer(m_pPlayer);
	m_pPlayer->linkColManager(m_pColManager);

	m_pBigRect = new Obstacles;
	m_pBigRect->init();
	m_pBigRect->SetPos({ WINSIZEX / 2,-10 });


	m_fCameraY = 0.f;

	m_rcObstacle = RectMakeCenter(WINSIZEX / 2, WINSIZEY * 3 / 4, 200, 200);

	//죄수들 초기화
	for (int i = 0; i < 4; i++)
	{
		prisoner* temp;
		temp = new prisoner;
		temp->init();
		float tempposy = -1 * 200 * i;
		temp->SetPos(fPoint{ WINSIZEX / 2,  tempposy });
		m_vecPrisoner.push_back(temp);
	}
	

	return S_OK;
}

void MinseokTest::release(void)
{
	for (int i = 0; i < m_vecPrisoner.size(); i++)
	{
		SAFE_DELETE(m_vecPrisoner[i]);
	}
	m_vecPrisoner.clear();
}

void MinseokTest::update(void)
{
	//테스트씬 끼리의 씬전환
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("시웅씬");
		return;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("영휘씬");
		return;
	}

	//상자의 위치를 옮겨줌
	m_rcObstacle.top -= 5;
	m_rcObstacle.bottom -= 5;

	m_pPlayer->update();
	m_pItem->update();
	m_pItem2->update();
	m_pBack->update();
	m_fCameraY = m_pPlayer->GetCamY();
	m_pBigRect->update();
	for (int i = 0; i < m_vecPrisoner.size(); i++)
	{
		m_vecPrisoner[i]->update();
	}


	//플레이어와 아이템의 충돌처리 - 플레이어의 코드를 건들지 않으므로 구조적으로 좋지못함 추후에 수정요망
	RECT temp;
	RECT temp2;
	temp2 = m_pPlayer->GetIR()._rc;
	if (IntersectRect(&temp, &temp2, &(m_pItem->GetIR()._rc)))
	{
		m_pItem->linkPlayer(m_pPlayer);
	}
	if (IntersectRect(&temp, &temp2, &(m_pItem2->GetIR()._rc)))
	{

		m_pItem2->linkPlayer(m_pPlayer);
		m_pItem2->linkItem(m_pItem);
	}
	
	//isCollisionReaction(&temp2, &(m_pItem->GetRect()));
	//isCollisionReaction(&temp2, &(m_pItem2->GetRect()));
	// ↑↑↑↑↑수정요망↑↑↑↑↑

	//플레이어와 아이템의 충돌처리 - 아이템끼리는 아직 못할듯 수정요망
	for (int i = 0; i < m_vecPrisoner.size(); i++)
	{
		if (IntersectRect(&temp, &temp2, &(m_vecPrisoner[i]->GetIR()._rc)))
		{
			m_vecPrisoner[i]->linkHead(m_pPlayer,t_player);
		}
	}
	//↑↑↑↑↑수정요망↑↑↑↑↑


}

void MinseokTest::render()
{
	
	
	
	m_pBack->render();
	m_pItem->render(m_fCameraY);
	m_pItem2->render(m_fCameraY);
	m_pPlayer->render(m_fCameraY);
	m_pBigRect->render(m_fCameraY);
	//Rectangle(getMemDC(), m_rcObstacle.left, m_rcObstacle.top - m_fCameraY, m_rcObstacle.right, m_rcObstacle.bottom - m_fCameraY);
	for (int i = 0; i < m_vecPrisoner.size(); i++)
	{
		m_vecPrisoner[i]->render(m_fCameraY);
	}


	//시웅씬과 안 햇갈리게 하기위한 글자
	char str[256];
	wsprintf(str, "민석이씬");
	TextOut(getMemDC(), 0, 80, str, strlen(str));
}

MinseokTest::MinseokTest()
{
	m_pItem = NULL;
	m_pPlayer = NULL;
	m_pBack = NULL;
	m_pItem2 = NULL;
}


MinseokTest::~MinseokTest()
{
	SAFE_DELETE(m_pItem);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pBack);
	SAFE_DELETE(m_pItem2);
}






HRESULT MinseokBack::init(void)
{
	m_pImage = IMAGEMANAGER->addImage("민석이배경", "Image/Background.bmp", 600, 800);
	m_nCameraY = 0;
	return S_OK;
}

void MinseokBack::release(void)
{
	SAFE_DELETE(m_pImage);
}

void MinseokBack::update(void)
{
	//m_nCameraY -= 5;
	//if (m_pPlayer->GetPoint().y < WINSIZEY / 2)
	//{
	//	POINT tempP;
	//	tempP.x = m_pPlayer->GetPoint().x;
	//	tempP.y = m_pPlayer->GetPoint().y + 5;
	//	m_pPlayer->SetPoint(tempP);
	//	m_nCameraY -= 5;
	//}
	
}

void MinseokBack::render()
{
	//m_pImage->render(getMemDC(), 0, 0);
	m_pImage->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, m_pPlayer->GetCamY());
}

MinseokBack::MinseokBack()
{
	m_pPlayer = NULL;
	m_pImage = NULL;
}

MinseokBack::~MinseokBack()
{
}


