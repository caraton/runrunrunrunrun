#include "stdafx.h" //stdafx�� ������ ��Ƴ��� ��������̹Ƿ� �ٸ������� stdafx�� ������ ��� ��ȣ������ 
					//�ƴϴ��� �����ϰ� cpp�� �������
#include "mainGame.h"
#include "MinseokTest.h"
#include "SiwoongTest.h"

//�ʱ�ȭ�� ������ ���⿡�ٰ� �ض�
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	//SCENEMANAGER->addScene("���̸�", new ��Ŭ�����̸�);
	//SCENEMANAGER->changeScene("���̸�");

	SCENEMANAGER->addScene("�μ���", new MinseokTest);
	SCENEMANAGER->addScene("�ÿ���", new SiwoongTest);
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
}

mainGame::mainGame()
	//:_isGameOver(false) 
{
}


mainGame::~mainGame()
{
}
