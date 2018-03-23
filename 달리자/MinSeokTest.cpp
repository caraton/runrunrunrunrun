#include "stdafx.h"
#include "MinseokTest.h"
#include "rectItem.h"
#include "player.h"

HRESULT MinseokTest::init(void)
{
	m_rPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 40, 40);
	
	m_pItem = new rectItem;
	m_pItem->init();

	m_pItem2 = new rectItem;
	m_pItem2->init();
	m_pItem2->SetPos(POINT{ WINSIZEX/2, - 1000 });

	m_pPlayer = new Minseokplayer;
	m_pPlayer->init();

	m_pBack = new MinseokBack;
	m_pBack->init();

	m_pBack->linkPlayer(m_pPlayer);

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
	m_pItem2->update();
	m_pBack->update();


	//�÷��̾�� �������� �浹ó�� - �÷��̾��� �ڵ带 �ǵ��� �����Ƿ� ���������� �������� ���Ŀ� �������
	RECT temp;
	RECT temp2;
	temp2 = m_pPlayer->GetIR()._rc;
	if (IntersectRect(&temp, &temp2, &m_pItem->GetRect()))
	{
		m_pItem->linkPlayer(m_pPlayer);
	}
	if (IntersectRect(&temp, &temp2, &m_pItem2->GetRect()))
	{

		m_pItem2->linkPlayer(m_pPlayer);
		m_pItem2->linkItem(m_pItem);
	}
	// ������������������

}

void MinseokTest::render()
{
	
	
	
	m_pBack->render();
	m_pItem->render();
	m_pItem2->render();
	m_pPlayer->render();




	//�ÿ����� �� �ް����� �ϱ����� ����
	char str[256];
	wsprintf(str, "�μ��̾�");
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
	m_nCameraY -= 5;
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
	m_pImage->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, m_nCameraY);
}

MinseokBack::MinseokBack()
{
	m_pPlayer = NULL;
	m_pImage = NULL;
}

MinseokBack::~MinseokBack()
{
}






HRESULT Minseokplayer::init(void)
{
	//�÷��̾� ��ǥ �ʱ�ȭ(ȭ���߾�)
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;

	//�̹��� ���� �ʱ�ȭ ����
	_playerImage = IMAGEMANAGER->addImage("player", "plane.bmp", 64, 64, true, RGB(255, 0, 255));

	//IR �ʱ�ȭ
	_IR._image = _playerImage;
	_IR._rc = RectMake(_player.x, _player.y, 64, 64);

	return S_OK;
}

void Minseokplayer::release(void)
{
}

void Minseokplayer::update(void)
{
	//�����̵�
	if (KEYMANAGER->isStayKeyDown('W') && _player.y > 0)
	{
		_player.y -= 5;
	}
	if (KEYMANAGER->isStayKeyDown('S') && _player.y + 64 < WINSIZEY)
	{
		_player.y += 5;
	}

	//�¿��̵�
	if (KEYMANAGER->isStayKeyDown('A') && _player.x > 0)
	{
		_player.x -= 5;
	}
	if (KEYMANAGER->isStayKeyDown('D') && _player.x + 64 <WINSIZEX)
	{
		_player.x += 5;
	}


	_IR._rc = RectMake(_player.x, _player.y, 64, 64);
}

void Minseokplayer::render()
{
	_IR._image->render(getMemDC(), _player.x, _player.y);
}

Minseokplayer::Minseokplayer()
{
	_playerImage = NULL;
}

Minseokplayer::~Minseokplayer()
{

}
