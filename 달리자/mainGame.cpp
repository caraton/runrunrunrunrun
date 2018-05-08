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
	gameNode::update();

	SCENEMANAGER->update();
}

void mainGame::render()
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

	if (_mapToolOn)
	{
		HDC mapToolDCtest;
		mapToolDCtest = GetDC(_hMapTool);

		char str[256] = "�����׽�Ʈ";
		TextOut(mapToolDCtest, WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));

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
