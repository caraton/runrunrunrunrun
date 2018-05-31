#include "stdafx.h"
#include "MapToolScene.h"

char MapToolScene::backgroundChoiceStr[128] = " ";
HWND MapToolScene::_hMapTool = NULL;

MapToolScene::MapToolScene()
{
}


MapToolScene::~MapToolScene()
{
}

HRESULT MapToolScene::init(void)
{

	//%%������
	IMAGEMANAGER->addFrameImage("bg_jail_mini_02", "Image/bg_jail_mini_02.bmp", 180, 80, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bg_city_mini_02", "Image/bg_city_mini_02.bmp", 180, 80, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("object_box", "Image/Obstacles/object_box.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("object_can", "Image/Obstacles/object_can.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("object_greeen", "Image/Obstacles/object_greeen.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("object_yellow", "Image/Obstacles/object_yellow.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�׽�Ʈ��ֹ�", "Image/Obstacles/enemy.bmp", 40, 40, true, RGB(255, 0, 255));

	_mapToolOn = 0;
	_jailB = new button;
	_jailB->init("bg_jail_mini_02", 280, 140, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), &jailButton);
	_cityB = new button;
	_cityB->init("bg_city_mini_02", 350, 140, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), &cityButton);

	//for (int i = 0; i < _totalObjectCount; ++i)
	//{
	//	button* temp = new button;
	//	temp->init
	//}

	//button* temp = new button;
	//temp->init("object_box", 700, 50, )

	_loopY = 0;
	_scrollY = 0;

	return S_OK;
}

void MapToolScene::release(void)
{
}

void MapToolScene::update(void)
{
	if (_mapToolOn == 1)
	{
		_jailB->update();
		_cityB->update();
	}
	else if (_mapToolOn == 2)
	{
		//������ �ε�� ��� ����Ǵ� ������Ʈ�� �ƴ϶� _mapToolOn�� 2���Ǵ� ���� �ѹ��� ����ǵ��� �ٲٱ�
		//vector<string> toLoad;

		//toLoad = TXTDATA->txtLoad("���� ����.txt");

		//*(mstr) = '\0'; //'\0'�� ���ڿ����� �����Ͱ� ����ִ� ������ĭ �ٷ� ������ ĭ�� ����ִ� ��
		//				//���� ù��°ĭ�� �� ���� �־��ָ� ����ִ� ���ڿ��� �ȴ�.
		//				//memset(mstr, 0, sizeof(mstr)); �̹�ĵ� ����

		//_buttonCount = 0;

		//////������ mstr�� TextOut �׷��� �κ��� �����ش�
		////RECT clearbox = RectMake(0, 0, WINSIZEX, WINSIZEY);
		////InvalidateRect(_hMapTool, &clearbox, true);

		//strcpy_s(mstr, (*toLoad.begin()).c_str());
		//_buttonCount = stoi((*(toLoad.begin() + 1)));

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_loopY -= 5;
		}	
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_loopY += 5;
		}
	}
}

void MapToolScene::render(void)
{
	HDC _hdcMapTool = GetDC(_hMapTool);

	if (_mapToolOn == 1)
	{
		//PatBlt(getMemDCMapTool(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		////==============================================================================================================
		char teststr[128] = "�ʱ��� :";
		sprintf_s(teststr, "�ʱ��� : %s", mstr);

		TextOut(_hdcMapTool, 30, 150, teststr, strlen(teststr));
		//TextOut(_hdcMapTool, 90, 150, mstr, strlen(mstr));

		char testtest[128];
		sprintf_s(testtest, "ī��Ʈ : %d", _buttonCount);

		TextOut(_hdcMapTool, 30, 200, testtest, strlen(testtest));

		//IMAGEMANAGER->findImage("background_jail")->render(_hdcMapTool, 250, 100, 60, 80, 0, 0, 600, 800);
		//IMAGEMANAGER->findImage("background")->render(_hdcMapTool, 320, 100, 60, 80, 0, 0, 600, 800);
		_jailB->render(_hdcMapTool);
		_cityB->render(_hdcMapTool);

		char backgroundChoiceStr2[128] = "��� : ";
		sprintf_s(backgroundChoiceStr2, "��� : %s", backgroundChoiceStr);

		TextOut(_hdcMapTool, 250, 200, backgroundChoiceStr2, strlen(backgroundChoiceStr2));

		//char teststr[128] = "�ʱ��� :";
		//sprintf_s(teststr, "�ʱ��� : %s", mstr);

		//TextOut(_hdcMapTool, 30, 150, teststr, strlen(teststr));

		//
		//if (_buttonCount == 10)
		//{
		//	PostMessage(_hMapTool, WM_COMMAND, 999, 0); //_hMapTool�� WM_COMMAND �޽��� ����Ʈ wParam�� 999����
		//}

		//IMAGEMANAGER->findImage("background_jail")->render()

		//ReleaseDC(_hMapTool, mapToolDCtest);
		//==============================================================================================================
		//���������� BackBuffer���� hdc�� ��Ʈ�� ��ȭ���� ����

		//this->getBackBufferMapTool()->render(_hdcMapTool, 0, 0); //����ۿ��� hdc�� ����
	}
	else if (_mapToolOn == 2)
	{
		IMAGEMANAGER->findImage("background_jail")->loopRender(_hdcMapTool, &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _loopY);
		IMAGEMANAGER->findImage("object_box")->render(_hdcMapTool, 650, 20 + _scrollY);
		IMAGEMANAGER->findImage("object_can")->render(_hdcMapTool, 650, 120 + _scrollY);
		IMAGEMANAGER->findImage("object_greeen")->render(_hdcMapTool, 650, 220 + _scrollY);
		IMAGEMANAGER->findImage("object_yellow")->render(_hdcMapTool, 650, 320 + _scrollY);
		IMAGEMANAGER->findImage("�׽�Ʈ��ֹ�")->render(_hdcMapTool, 650, 420 + _scrollY);
	}

	ReleaseDC(_hMapTool, _hdcMapTool);
}

void MapToolScene::cityButton(void)
{
	RECT clearbox = RectMake(250, 200, 500, 100);
	InvalidateRect(_hMapTool, &clearbox, true);
	strcpy_s(backgroundChoiceStr, "bg_city_mini_02");
}

void MapToolScene::jailButton(void)
{
	RECT clearbox = RectMake(250, 200, 500, 100);
	InvalidateRect(_hMapTool, &clearbox, true);
	strcpy_s(backgroundChoiceStr, "bg_jail_mini_02");
}

