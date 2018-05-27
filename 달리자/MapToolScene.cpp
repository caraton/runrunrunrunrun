#include "stdafx.h"
#include "MapToolScene.h"

char MapToolScene::backgroundChoiceStr[128] = " ";

MapToolScene::MapToolScene()
{
}


MapToolScene::~MapToolScene()
{
}

HRESULT MapToolScene::init(void)
{
	_jailB = new button;
	_jailB->init("bg_jail_mini_02", 280, 140, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), &jailButton);
	_cityB = new button;
	_cityB->init("bg_city_mini_02", 350, 140, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), &cityButton);

	return S_OK;
}

void MapToolScene::release(void)
{
}

void MapToolScene::update(void)
{
	_jailB->update();
	_cityB->update();
}

void MapToolScene::render(void)
{
	HDC _hdcMapTool = GetDC(_hMapTool);

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

