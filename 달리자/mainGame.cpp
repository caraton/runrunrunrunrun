#include "stdafx.h" //stdafx�� ������ ��Ƴ��� ��������̹Ƿ� �ٸ������� stdafx�� ������ ��� ��ȣ������ 
					//�ƴϴ��� �����ϰ� cpp�� �������
#include "mainGame.h"
#include "MinseokTest.h"
#include "SiwoongTest.h"
#include "YounghuiTest.h"

//�ʱ�ȭ�� ������ ���⿡�ٰ� �ض�
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	//SCENEMANAGER->addScene("���̸�", new ��Ŭ�����̸�);
	//SCENEMANAGER->changeScene("���̸�");

	SCENEMANAGER->addScene("�μ���", new MinseokTest);
	SCENEMANAGER->addScene("�ÿ���", new SiwoongTest);
	SCENEMANAGER->addScene("���־�", new YounghuiTest);
	SCENEMANAGER->changeScene("�ÿ���");

	return S_OK; //S_OK : ������ Boolean TRUE ��(0X0)���� S_FALSE�� �Բ� ���Ǹ� �Լ��� �����Ͽ����� �ǹ��Ѵ�.
}

//�޸� ������ ������ ���⿡�ٰ� �ض�
void mainGame::release(void)
{
	gameNode::release();
}

//������(��) ������ ���⿡�ٰ� �ض�
void mainGame::update(void)
{
	if (!_mapToolOn)
	{
		gameNode::update();

		SCENEMANAGER->update();
	}
}

void mainGame::render()
{
	if (!_mapToolOn)
	{
		//%%�μ�Ŀ��ŧ�� ������۸�

		//����� ������ hMemDC ������ ������
		//HDC backDC = this->getBackBuffer()->getMemDC();
		//�ű⿡ ��� ��ȭ�� ������ ���
		//PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		//==============================================================================================================
		//IMAGEMANAGER->findImage("����ϲ�")->render(getMemDC(), 0, 0);

		SCENEMANAGER->render();

		TIMEMANAGER->render(getMemDC()); //TIMEMANAGER�� SCENEMANAGER�� �ٸ��� ���ο��� MemDC�� ������ ������.
										 //SCENEMANAGER�� ���ο��� gameNode*�� _currentScene�� ���� ����
		//==============================================================================================================
		//���������� BackBuffer���� hdc�� ��Ʈ�� ��ȭ���� ����
		this->getBackBuffer()->render(getHDC(), 0, 0); //����ۿ��� hdc�� ����
	}
	else
	{
		HDC mapToolDCtest;
		mapToolDCtest = GetDC(_hMapTool);
		char teststr[128] = "�ʱ��� :";
		sprintf_s(teststr, "�ʱ��� : %s", mstr);

		TextOut(mapToolDCtest, 30, 150, teststr, strlen(teststr));
		//TextOut(mapToolDCtest, 90, 150, mstr, strlen(mstr));

		char testtest[128];
		sprintf_s(testtest, "ī��Ʈ : %d", _buttonCount);

		TextOut(mapToolDCtest, 30, 200, testtest, strlen(testtest));
		//
		//if (_buttonCount == 10)
		//{
		//	PostMessage(_hMapTool, WM_COMMAND, 999, 0); //_hMapTool�� WM_COMMAND �޽��� ����Ʈ wParam�� 999����
		//}

		ReleaseDC(_hMapTool, mapToolDCtest);
	}
}

mainGame::mainGame()
	//:_isGameOver(false) 
{
}


mainGame::~mainGame()
{
}
