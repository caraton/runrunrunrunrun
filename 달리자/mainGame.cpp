#include "stdafx.h" //stdafx�� ������ ��Ƴ��� ��������̹Ƿ� �ٸ������� stdafx�� ������ ��� ��ȣ������ 
					//�ƴϴ��� �����ϰ� cpp�� �������
#include "mainGame.h"
#include "MinseokTest.h"
#include "SiwoongTest.h"
#include "YounghuiTest.h"
#include "MapToolScene.h"

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

	_mapToolScene = new MapToolScene;
	_mapToolScene->init();

	return S_OK; //S_OK : ������ Boolean TRUE ��(0X0)���� S_FALSE�� �Բ� ���Ǹ� �Լ��� �����Ͽ����� �ǹ��Ѵ�.
}

//�޸� ������ ������ ���⿡�ٰ� �ض�
void mainGame::release(void)
{
	gameNode::release();
	delete _mapToolScene;
}

//������(��) ������ ���⿡�ٰ� �ض�
void mainGame::update(void)
{
	if (!_mapToolOn)
	{
		gameNode::update();

		SCENEMANAGER->update();
	}
	else
	{
		_mapToolScene->update();
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
		_mapToolScene->render();
	}
}

mainGame::mainGame()
	//:_isGameOver(false) 
{
}


mainGame::~mainGame()
{
}
