#include "stdafx.h"
#include "MinseokTest.h"
#include "rectItem.h"
#include "player.h"
#include "CollisionCheckManager.h"
#include "prisoner.h"
#include "Obstacles.h"

HRESULT MinseokTest::init(void)
{
	m_pPlayer = new player;
	m_pPlayer->init();

	m_pBack = new MinseokBack;
	m_pBack->init();

	//�ݸ��� �Ŵ��� �ʱ�ȭ
	m_pColManager = new CollisionCheckManager;
	m_pColManager->init(WINSIZEY * 2);
	m_pColManager->linkPlayer(m_pPlayer);

	m_pBack->linkPlayer(m_pPlayer);
	m_pPlayer->linkColManager(m_pColManager);


	m_pDeadLine = new Obstacles;
	m_pDeadLine->init();
	IR tempIR;
	tempIR._rc = RectMake(0, 0, WINSIZEX, 100);
	tempIR._image = IMAGEMANAGER->addImage("DeadRock", "Image/rock04.bmp", 600, 188, true, RGB(255, 0, 255));
	m_pDeadLine->SetIR(tempIR);
	m_pDeadLine->SetPos({0,WINSIZEY - 188});
	m_pDeadLine->SetSpeed({ 0,-5.f });


	m_fCameraY = 0.f;

	m_rcObstacle = RectMakeCenter(WINSIZEX / 2, WINSIZEY * 3 / 4, 200, 200);

	//�˼��� �ʱ�ȭ
	for (int i = 0; i < 4; i++)
	{
		prisoner* tttemp;
		tttemp = new prisoner;
		tttemp->init();
		//�̴��Լ�
		//m_pPosition = { WINSIZEX * 3 / 4, -400 };
		//m_pIR._rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
		//m_pSpeed = { 0,0 };
		//
		//m_pIR._type = "devil";
		//m_pIR._image = IMAGEMANAGER->addFrameImage("prisoner01", "Image/prisoner01_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
		float tempposy = -1 * 200 * i;
		tttemp->SetPos(fPoint{ WINSIZEX / 2,  tempposy });
		m_vecPrisoner.push_back(tttemp);
		m_pColManager->addIR(&(tttemp->GetIR()));

	}
	//for (int i = 0; i < 4; i++)
	//{
	//	m_pColManager->addIR(&(m_vecPrisoner[i]->GetIR()));
	//}
	

	//�׽�Ʈ
	_testIR._image = IMAGEMANAGER->addImage("�׽�Ʈ��ֹ�", "Image/Obstacles/enemy.bmp", 40, 40, true, RGB(255, 0, 255));
	_testIR._rc = RectMakeCenter(100, -40, 40, 40);
	_testIR._type = "devil";
	_testIRy = -40;
	m_pColManager->addIR(&_testIR);

	int a = 1;

	return S_OK;
}

void MinseokTest::release(void)
{
	for (int i = 0; i < m_vecPrisoner.size(); i++)
	{
		SAFE_DELETE(m_vecPrisoner[i]);
	}
	m_vecPrisoner.clear();
	SAFE_DELETE(m_pColManager);
}


void MinseokTest::update(void)
{

	//�׽�Ʈ�� ������ ����ȯ
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("�ÿ���");
		return;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("���־�");
		return;
	}

	
	
	m_pPlayer->update();
	m_pBack->update();
	m_fCameraY = m_pPlayer->GetCamY();
	m_pDeadLine->update();
	for (int i = 0; i < m_vecPrisoner.size(); i++)
	{
		m_vecPrisoner[i]->update();
	}
	_testIR._rc = RectMakeCenter(100, _testIRy, 40, 40);
	
	m_pColManager->update();



	//�÷��̾�� �������� �浹ó�� - �÷��̾��� �ڵ带 �ǵ��� �����Ƿ� ���������� �������� ���Ŀ� �������
	RECT temp;
	RECT temp2;
	temp2 = m_pPlayer->GetIR()._rc;
	
	//isCollisionReaction(&temp2, &(m_pItem->GetRect()));
	//isCollisionReaction(&temp2, &(m_pItem2->GetRect()));
	// ������������������

	//�÷��̾�� �������� �浹ó�� - �����۳����� ���� ���ҵ� �������
	//for (int i = 0; i < m_vecPrisoner.size(); i++)
	//{
	//	if (IntersectRect(&temp, &temp2, &(m_vecPrisoner[i]->GetIR()._rc)))
	//	{
	//		m_vecPrisoner[i]->linkHead(m_pPlayer,t_player);
	//	}
	//}
	//������������������


}

void MinseokTest::render()
{
	
	
	
	m_pBack->render();
	m_pPlayer->render(m_fCameraY);
	
	//Rectangle(getMemDC(), m_rcObstacle.left, m_rcObstacle.top - m_fCameraY, m_rcObstacle.right, m_rcObstacle.bottom - m_fCameraY);
	for (int i = 0; i < m_vecPrisoner.size(); i++)
	{
		Rectangle(getMemDC(),m_vecPrisoner[i]->GetIR()._rc.left, m_vecPrisoner[i]->GetIR()._rc.top - m_fCameraY, m_vecPrisoner[i]->GetIR()._rc.right, m_vecPrisoner[i]->GetIR()._rc.bottom - m_fCameraY);
		m_vecPrisoner[i]->render(m_fCameraY);
	}
	m_pDeadLine->render(m_fCameraY);

	//�����Ҷ� _cameraY���� �̿��� �÷��̾� ���� ���� ��ǥ�� ��ȯ
	if (_testIR._rc.top - m_fCameraY > 0 && _testIR._rc.top - m_fCameraY <= WINSIZEY)
	{
		_testIR._image->render(getMemDC(), _testIR._rc.left, _testIR._rc.top - m_fCameraY);
	}


	//�ÿ����� �� �ް����� �ϱ����� ����
	char str[256];
	wsprintf(str, "�μ��̾�");
	TextOut(getMemDC(), 0, 80, str, strlen(str));

}

MinseokTest::MinseokTest()
{
	
	m_pPlayer = NULL;
	m_pBack = NULL;
	m_pDeadLine = NULL;
}


MinseokTest::~MinseokTest()
{
	
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pBack);
	SAFE_DELETE(m_pDeadLine);
	SAFE_DELETE(m_pColManager);
}






HRESULT MinseokBack::init(void)
{
	m_pImage = IMAGEMANAGER->addImage("�μ��̹��", "Image/Background.bmp", 600, 800);
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


