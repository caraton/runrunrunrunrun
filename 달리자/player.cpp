#include "stdafx.h"
#include "player.h"
#include "CollisionManager.h"
#include "Items.h"

//���� �ʸ��� �´µ�

//ToDoList: �ӵ� ���ӵ�
//������ ������ ���ͷ�
//can�� �浹�� �з�����(can�������� �̵��ϴ°� ����)

//SiwoongTest���� �����۵��� IR�� colManager�� �����ϰ�
//player�� �������� ���� �Ŀ�
//player�� ����� �������� ������ (������)
//����: �������� ����ϱ� (�� �÷��̾ ����� �˼����� �÷��̾� ������ �޾� �̵�)
//�ܺ�: ������ ������ �̿� (��: 3��° ���� �������� 2��° �������� �����͸� �޾ƾ���, )

HRESULT player::init(void)
{
	//�̹��� ���� �ʱ�ȭ ����
	//m_pPlayerImage ��� ������ �����ص� �ɵ�
	m_IR._image = IMAGEMANAGER->addFrameImage("player", "Image/player_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	_playerDeath = IMAGEMANAGER->addImage("playerDeath", "Image/player_down_50.bmp", 50, 50, true, RGB(255, 0, 255));
	m_pPlayerImage = m_IR._image;
	IMAGEMANAGER->addFrameImage("prisoner01", "Image/prisoner01_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("guard", "Image/guard_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	//�÷��̾� ��ǥ �ʱ�ȭ(ȭ���߾�)
	m_fpPosition.x = WINSIZEX / 2;
	m_fpPosition.y = WINSIZEY / 2;

	m_fCamaraY = 0;

	//������ ���� �ʱ�ȭ
	m_fBasicSpeedY =  -5;
	m_fpSpeed = { 0.f,0.f };


	//IR �ʱ�ȭ
	//_IR._image = _playerImage;
	m_IR._rc = RectMake(m_fpPosition.x, m_fpPosition.y, 50, 50);

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	move();
	
	if ((m_pColManager) && m_fCamaraY >= -(m_pColManager->GetMapLength() - WINSIZEY))
	{
		m_fCamaraY += m_fBasicSpeedY;
	}

	//z,x,c,space bar
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) //��ȣ�ۿ�
	{
		_test.clear();

		vector<IR*>* temp = new vector<IR*>;
		if (m_pColManager->findIRNear(&m_IR, temp))
		{
			//�ֺ��� ���𰡰� �־ temp�� �����
			vector<IR*>::iterator iter;
			for (iter = temp->begin(); iter != temp->end(); ++iter)
			{
				RECT temp = (*iter)->_rc;
				_test.push_back(temp);
			}
		}

		//�پ� temp�����
		SAFE_DELETE(temp);
	}
	//if (KEYMANAGER->isOnceKeyDown('Z')) //�̹��������׽�Ʈ
	//{
	//	m_IR._image = IMAGEMANAGER->findImage("prisoner01");
	//}
	//if (KEYMANAGER->isOnceKeyDown('X')) //�̹��������׽�Ʈ
	//{
	//	m_IR._image = IMAGEMANAGER->findImage("guard");
	//}
	//if (KEYMANAGER->isOnceKeyDown('C')) //�̹��������׽�Ʈ
	//{
	//	m_IR._image = IMAGEMANAGER->findImage("player");
	//}

	m_IR._image->setFrameX((TIMEMANAGER->getFrameCount()/10) % 6);
	//�� ���Ŀ� �浹 üũ�� �ؾ� ������ �̹����� �°� �ȼ��浹�� ����ȴ�

	vector<IR*>* temp = new vector<IR*>;

	if (m_pColManager->checkCollision(&m_IR, temp))
	{
		for (_colIter = temp->begin(); _colIter != temp->end(); ++_colIter)
		{
			if (!strncmp((*_colIter)->_type, "devil", 10))
			{
				m_IR._image = IMAGEMANAGER->findImage("playerDeath");
				m_pColManager->SetGameover(true);
				break;
			}
			else if (!strncmp((*_colIter)->_type, "can", 10))
			{
				fPoint tempf;
				tempf.x = ((*_colIter)->_rc.left + (*_colIter)->_rc.right) / 2;
				tempf.y = ((*_colIter)->_rc.top + (*_colIter)->_rc.bottom) / 2;
				fPoint tempm;
				tempm.x = 25;
				tempm.y = 25;

				float t = 1.00;

				while (pixelCol(&m_IR, *_colIter))
				{
					t = t + 0.07;
					m_fpPosition = (tempf + (((m_fpPosition + tempm) - tempf) * t)) - tempm;
					m_IR._rc = RectMake(m_fpPosition.x, m_fpPosition.y, 50, 50);
				}
				break;
			}
		}
	}

	SAFE_DELETE(temp);
}

void player::render(float cameraY)
{
	m_IR._image->frameRender(getMemDC(), m_fpPosition.x, m_fpPosition.y- cameraY);
	for (_testIter = _test.begin(); _testIter != _test.end(); ++_testIter)
	{
		Rectangle(getMemDC(), (*_testIter).left, (*_testIter).top - cameraY, (*_testIter).right, (*_testIter).bottom - cameraY);
	}
}

void player::render()
{
	m_IR._image->frameRender(getMemDC(), m_fpPosition.x, m_fpPosition.y - m_fCamaraY);
	for (_testIter = _test.begin(); _testIter != _test.end(); ++_testIter)
	{
		Rectangle(getMemDC(), (*_testIter).left, (*_testIter).top - m_fCamaraY, (*_testIter).right, (*_testIter).bottom - m_fCamaraY);
	}
}


void player::render(bool gameover)
{
	if (!gameover)
	{
		m_IR._image->frameRender(getMemDC(), m_fpPosition.x, m_fpPosition.y - m_fCamaraY);
	}
	else
	{
		m_IR._image->render(getMemDC(), m_fpPosition.x, m_fpPosition.y - m_fCamaraY);
	}

	for (_testIter = _test.begin(); _testIter != _test.end(); ++_testIter)
	{
		Rectangle(getMemDC(), (*_testIter).left, (*_testIter).top - m_fCamaraY, (*_testIter).right, (*_testIter).bottom - m_fCamaraY);
	}
}


void player::move()
{


	//�޸��� �ӵ� ����
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		m_fBasicSpeedY += 2;
		if (m_fBasicSpeedY >= -1)
		{
			m_fBasicSpeedY = -1;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('X'))
	{
		m_fBasicSpeedY -= 2;
		if (m_fBasicSpeedY <= -9)
		{
			m_fBasicSpeedY = -9;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('C'))
	{
		m_fBasicSpeedY = 0;
	}




	//�����̵�
	if (KEYMANAGER->isStayKeyDown(VK_UP) && m_fpPosition.y - m_fCamaraY > 0)
	{
		//_cameraY -= 5;
		m_fpSpeed.y = -10 + m_fBasicSpeedY;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_fpPosition.y - m_fCamaraY < WINSIZEY)
	{
		//_cameraY += 5;
		m_fpSpeed.y = 10 + m_fBasicSpeedY;
	}
	else
	{
		m_fpSpeed.y = m_fBasicSpeedY;
	}

	//�¿��̵�
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_fpPosition.x > 0)
	{
		m_fpSpeed.x = -5;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_fpPosition.x + 64 <WINSIZEX)
	{
		m_fpSpeed.x = 5;
	}
	else
	{
		m_fpSpeed.x = 0;
	}


	//�ӵ��� �޾� �̵�����
	m_fpPosition.x += m_fpSpeed.x;
	m_fpPosition.y += m_fpSpeed.y;
	m_IR._rc = RectMake(m_fpPosition.x, m_fpPosition.y, 50, 50);
}






player::player()
{
	m_pPlayerImage = NULL;
	m_pColManager = NULL;
}

player::~player()
{
}

