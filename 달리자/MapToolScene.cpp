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

	//%%맵툴용
	IMAGEMANAGER->addFrameImage("bg_jail_mini_02", "Image/bg_jail_mini_02.bmp", 180, 80, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bg_city_mini_02", "Image/bg_city_mini_02.bmp", 180, 80, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("object_box", "Image/Obstacles/object_box.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("object_can", "Image/Obstacles/object_can.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("object_greeen", "Image/Obstacles/object_greeen.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("object_yellow", "Image/Obstacles/object_yellow.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("테스트장애물", "Image/Obstacles/enemy.bmp", 40, 40, true, RGB(255, 0, 255));

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
		//데이터 로드는 계속 실행되는 업데이트가 아니라 _mapToolOn가 2가되는 순간 한번만 실행되도록 바꾸기
		//vector<string> toLoad;

		//toLoad = TXTDATA->txtLoad("맵툴 실험.txt");

		//*(mstr) = '\0'; //'\0'은 문자열에서 데이터가 들어있는 마지막칸 바로 다음의 칸에 들어있는 값
		//				//따라서 첫번째칸에 이 값을 넣어주면 비어있는 문자열이 된다.
		//				//memset(mstr, 0, sizeof(mstr)); 이방식도 가능

		//_buttonCount = 0;

		//////기존의 mstr로 TextOut 그려진 부분을 지워준다
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
		char teststr[128] = "맵길이 :";
		sprintf_s(teststr, "맵길이 : %s", mstr);

		TextOut(_hdcMapTool, 30, 150, teststr, strlen(teststr));
		//TextOut(_hdcMapTool, 90, 150, mstr, strlen(mstr));

		char testtest[128];
		sprintf_s(testtest, "카운트 : %d", _buttonCount);

		TextOut(_hdcMapTool, 30, 200, testtest, strlen(testtest));

		//IMAGEMANAGER->findImage("background_jail")->render(_hdcMapTool, 250, 100, 60, 80, 0, 0, 600, 800);
		//IMAGEMANAGER->findImage("background")->render(_hdcMapTool, 320, 100, 60, 80, 0, 0, 600, 800);
		_jailB->render(_hdcMapTool);
		_cityB->render(_hdcMapTool);

		char backgroundChoiceStr2[128] = "배경 : ";
		sprintf_s(backgroundChoiceStr2, "배경 : %s", backgroundChoiceStr);

		TextOut(_hdcMapTool, 250, 200, backgroundChoiceStr2, strlen(backgroundChoiceStr2));

		//char teststr[128] = "맵길이 :";
		//sprintf_s(teststr, "맵길이 : %s", mstr);

		//TextOut(_hdcMapTool, 30, 150, teststr, strlen(teststr));

		//
		//if (_buttonCount == 10)
		//{
		//	PostMessage(_hMapTool, WM_COMMAND, 999, 0); //_hMapTool의 WM_COMMAND 메시지 포스트 wParam에 999저장
		//}

		//IMAGEMANAGER->findImage("background_jail")->render()

		//ReleaseDC(_hMapTool, mapToolDCtest);
		//==============================================================================================================
		//최종적으로 BackBuffer에서 hdc의 비트맵 도화지로 복사

		//this->getBackBufferMapTool()->render(_hdcMapTool, 0, 0); //백버퍼에서 hdc로 복사
	}
	else if (_mapToolOn == 2)
	{
		IMAGEMANAGER->findImage("background_jail")->loopRender(_hdcMapTool, &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _loopY);
		IMAGEMANAGER->findImage("object_box")->render(_hdcMapTool, 650, 20 + _scrollY);
		IMAGEMANAGER->findImage("object_can")->render(_hdcMapTool, 650, 120 + _scrollY);
		IMAGEMANAGER->findImage("object_greeen")->render(_hdcMapTool, 650, 220 + _scrollY);
		IMAGEMANAGER->findImage("object_yellow")->render(_hdcMapTool, 650, 320 + _scrollY);
		IMAGEMANAGER->findImage("테스트장애물")->render(_hdcMapTool, 650, 420 + _scrollY);
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

