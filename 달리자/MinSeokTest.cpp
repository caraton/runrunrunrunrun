#include "stdafx.h"
#include "MinseokTest.h"
#include "rectItem.h"
#include "player.h"
#include "CollisionCheckManager.h"
#include "prisoner.h"
#include "Obstacles.h"
#include "guards.h"
#include "star.h"
#include "smokeBomb.h"

HRESULT MinseokTest::init(void)
{
	m_pPlayer = new player;
	m_pPlayer->init();

	m_pBack = new MinseokBack;
	m_pBack->init();

	//콜리전 매니저 초기화
	m_pColManager = new CollisionCheckManager;
	m_pColManager->init(WINSIZEY * 2);
	m_pColManager->linkPlayer(m_pPlayer);

	m_pBack->linkPlayer(m_pPlayer);
	m_pPlayer->linkColManager(m_pColManager);



	m_fCameraY = 0.f;

	m_rcObstacle = RectMakeCenter(WINSIZEX / 2, WINSIZEY * 3 / 4, 200, 200);


	//가드들 초기화
	for (int i = 0; i < (int)(WINSIZEX / 50); i++)
	{
		guards* gTemp;
		gTemp = new guards;
		gTemp->init();
		gTemp->SetPos({ (float)i * 50 , (float)WINSIZEY - 50 });
		m_vecGaurd.push_back(gTemp);
		m_pColManager->addIR(gTemp->GetIR());

	}
	for (int i = 0; i < (int)(WINSIZEX / 50) + 1; i++)
	{
		guards* gTemp;
		gTemp = new guards;
		gTemp->init();
		gTemp->SetPos({ (float)i * 50 - 25, (float)WINSIZEY - 70 });
		m_vecGaurd.push_back(gTemp);
		m_pColManager->addIR(gTemp->GetIR());

	}



	//아이템들 초기화
	for (int i = 0; i < 4; i++)
	{
		Items* tttemp;
		
		if (i == 1)
		{
			tttemp = new smokeBomb;
			tttemp->init();
			tttemp->linkColManager(m_pColManager);
			tttemp->linkGuards(m_vecGaurd);
		}
		else if (i == 2)
		{
			tttemp = new star;
			tttemp->init();
		}
		else 
		{
			tttemp = new prisoner;
			tttemp->init();
			tttemp->linkColManager(m_pColManager);
		}
		float tempposy = -1 * 200 * i;
		tttemp->SetPos(fPoint{ WINSIZEX / 2,  tempposy });
		m_vecItems.push_back(tttemp);
		m_pColManager->addIR(tttemp->GetIR());

	}

	
	//for (int i = 0; i < 4; i++)
	//{
	//	m_pColManager->addIR(&(m_vecPrisoner[i]->GetIR()));
	//}

	int a = 1;


	//테스트 장애물
	testTemp = new IR;
	testTemp->_image = IMAGEMANAGER->addFrameImage("can", "Image/Obstacles/object_can_icon.bmp", 100, 50, 2, 1, true, RGB(255, 0, 255));
	testTemp->_rc = RectMakeCenter(WINSIZEX / 2 - 200, -500, 50, 50);
	testTemp->_type = "can";
	m_pColManager->addIR(testTemp);

	return S_OK;
}

void MinseokTest::release(void)
{
	for (int i = 0; i < m_vecItems.size(); i++)
	{
		SAFE_DELETE(m_vecItems[i]);
	}
	m_vecItems.clear();
	SAFE_DELETE(m_pColManager);
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

	if (m_pColManager->GetGameover())
	{
		return;
	}
	
	
	m_pPlayer->update();
	m_pBack->update();
	m_fCameraY = m_pPlayer->GetCamY();
	
	for (int i = 0; i < m_vecItems.size(); i++)
	{
		m_vecItems[i]->update();
	}
	for (int i = 0; i < m_vecGaurd.size(); i++)
	{
		m_vecGaurd[i]->update();
	}
	
	m_pColManager->update();



	//플레이어와 아이템의 충돌처리 - 플레이어의 코드를 건들지 않으므로 구조적으로 좋지못함 추후에 수정요망
	RECT temp;
	RECT temp2;
	temp2 = m_pPlayer->GetIR()._rc;
	
	//isCollisionReaction(&temp2, &(m_pItem->GetRect()));
	//isCollisionReaction(&temp2, &(m_pItem2->GetRect()));
	// ↑↑↑↑↑수정요망↑↑↑↑↑

	//플레이어와 아이템의 충돌처리 - 아이템끼리는 아직 못할듯 수정요망
	//for (int i = 0; i < m_vecPrisoner.size(); i++)
	//{
	//	if (IntersectRect(&temp, &temp2, &(m_vecPrisoner[i]->GetIR()._rc)))
	//	{
	//		m_vecPrisoner[i]->linkHead(m_pPlayer,t_player);
	//	}
	//}
	//↑↑↑↑↑수정요망↑↑↑↑↑


}

void MinseokTest::render()
{
	
	
	
	m_pBack->render();
	m_pPlayer->render(m_fCameraY);
	m_pPlayer->render(m_pColManager->GetGameover());

	if (testTemp)
	{
		testTemp->_image->frameRender(getMemDC(), testTemp->_rc.left, testTemp->_rc.top - m_fCameraY);
	}
	
	
	//Rectangle(getMemDC(), m_rcObstacle.left, m_rcObstacle.top - m_fCameraY, m_rcObstacle.right, m_rcObstacle.bottom - m_fCameraY);
	for (int i = 0; i < m_vecItems.size(); i++)
	{
		//Rectangle(getMemDC(),m_vecPrisoner[i]->GetIR()->_rc.left, m_vecPrisoner[i]->GetIR()->_rc.top - m_fCameraY, m_vecPrisoner[i]->GetIR()->_rc.right, m_vecPrisoner[i]->GetIR()->_rc.bottom - m_fCameraY);
		m_vecItems[i]->render(m_fCameraY);
	}
	for (int i = 0; i < m_vecGaurd.size(); i++)
	{
		m_vecGaurd[i]->render(m_fCameraY);
	}
	//m_pDeadLine->render(m_fCameraY);


	//시웅씬과 안 햇갈리게 하기위한 글자
	char str[256];
	wsprintf(str, "민석이씬");
	TextOut(getMemDC(), 0, 80, str, strlen(str));

	
}

MinseokTest::MinseokTest()
{

	m_pPlayer = NULL;
	m_pBack = NULL;
}


MinseokTest::~MinseokTest()
{
	
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pBack);
	SAFE_DELETE(m_pColManager);
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


