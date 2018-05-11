#include "stdafx.h" //stdafx는 참조를 모아놓은 헤더파일이므로 다른곳에서 stdafx를 참조할 경우 상호참조가 
					//아니더라도 안전하게 cpp에 적어놓기
#include "mainGame.h"
#include "MinseokTest.h"
#include "SiwoongTest.h"
#include "YounghuiTest.h"

//초기화는 앞으로 여기에다가 해라
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	//SCENEMANAGER->addScene("씬이름", new 씬클래스이름);
	//SCENEMANAGER->changeScene("씬이름");

	SCENEMANAGER->addScene("민석씬", new MinseokTest);
	SCENEMANAGER->addScene("시웅씬", new SiwoongTest);
	SCENEMANAGER->addScene("영휘씬", new YounghuiTest);
	SCENEMANAGER->changeScene("시웅씬");

	return S_OK; //S_OK : 때때로 Boolean TRUE 값(0X0)으로 S_FALSE와 함께 사용되며 함수가 성공하였음을 의미한다.
}

//메모리 해제는 앞으로 여기에다가 해라
void mainGame::release(void)
{
	gameNode::release();
}

//연산은(는) 앞으로 여기에다가 해라
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
		//%%민석커리큘럼 더블버퍼링

		//백버퍼 영역의 hMemDC 정보를 가져옴
		//HDC backDC = this->getBackBuffer()->getMemDC();
		//거기에 흰색 도화지 한장을 깔기
		//PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		//==============================================================================================================
		//IMAGEMANAGER->findImage("배경일껄")->render(getMemDC(), 0, 0);

		SCENEMANAGER->render();

		TIMEMANAGER->render(getMemDC()); //TIMEMANAGER는 SCENEMANAGER와 다르게 내부에서 MemDC에 접근할 수없다.
										 //SCENEMANAGER는 내부에서 gameNode*인 _currentScene을 통해 접근
		//==============================================================================================================
		//최종적으로 BackBuffer에서 hdc의 비트맵 도화지로 복사
		this->getBackBuffer()->render(getHDC(), 0, 0); //백버퍼에서 hdc로 복사
	}
	else
	{
		HDC mapToolDCtest;
		mapToolDCtest = GetDC(_hMapTool);
		char teststr[128] = "맵길이 :";
		sprintf_s(teststr, "맵길이 : %s", mstr);

		TextOut(mapToolDCtest, 30, 150, teststr, strlen(teststr));
		//TextOut(mapToolDCtest, 90, 150, mstr, strlen(mstr));

		char testtest[128];
		sprintf_s(testtest, "카운트 : %d", _buttonCount);

		TextOut(mapToolDCtest, 30, 200, testtest, strlen(testtest));
		//
		//if (_buttonCount == 10)
		//{
		//	PostMessage(_hMapTool, WM_COMMAND, 999, 0); //_hMapTool의 WM_COMMAND 메시지 포스트 wParam에 999저장
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
