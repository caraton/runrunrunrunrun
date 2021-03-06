// API 영휘비행기.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "mainGame.h"
#include "달리자.h"

//%% stdafx에서 선언된 extern 전역변수 정의(메모리 할당)하는 곳 
HINSTANCE	_hInstance;		//window App 고유번호
HWND		_hWnd;			//윈도우 핸들


int _cmdShow; //맵툴 윈도우를 ShowWindow로 표시할때 사용하기 위해 cmdShow를 extern으로 저장
POINT _ptMouse;		//마우스 좌표 받을 POINT 변수

LPTSTR _lpszClass = TEXT("Theta API");	//윈도우 창 텍스트 창의 이름을 변경할 수 있다
//%%

mainGame _mg; //mainGame 클래스 정적생성

//함수 전방선언 == 함수의 프로토타입 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //WndProc 함수를 먼저 선언해주고 정의는 역시 밑에서

//LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM); 두개의 윈프로시저가 있을때는 WNDCLASS도 2개이어야 한다
//두개 만들기 참조:http://gandus.tistory.com/330

void setWindowSize(int x, int y, int width, int height); //여기서 함수를 먼저 선언해주고 정의는 맨 밑에서 한다.

														 //이게 메인함수(이름은 WinMain, APIENTRY를 적어야 API?)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;	//운영체제에서 발생하는 메시지 정보를 저장하기 위한 구조체
	WNDCLASS	wndClass;	//윈도우(창)의 정보를 저장하기 위한 구조체

	_hInstance = hInstance;
	_cmdShow = cmdShow;

	wndClass.cbClsExtra = 0;										//클래스 여분 메모리 설정
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리 설정
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 백그라운드 칼라
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//윈도우 커서 모양 (현재 화살표)
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//윈도우 아이콘 모양
	wndClass.hInstance = hInstance;									//윈도우 인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져 //여기서 wndClass와 WndProc이 연결됨
	wndClass.lpszClassName = _lpszClass;							//윈도우 클래스이름
	wndClass.lpszMenuName = NULL;									//윈도우 메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 스타일

																	//윈도우 정보 등록
	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		_lpszClass,         //위에 정의한 wndClass의 이름이 들어감 wndClass에 WndProc의 정보가 들어있으므로 _hMapTool이 다른 윈도우 프로시저를 쓰지 않는 이상 (예:WndProc2) 동일하게 집어넣기
		_lpszClass,			//창의 타이틀 바에 나올 문자열
		WS_OVERLAPPEDWINDOW,
		//200,				//윈도우 창 시작위치 X //왼손좌표계 //왼쪽 모니터는 - 값으로 좌표 지정
		//50,				//윈도우 창 시작위치 y
		//1600,				//윈도우 창 가로크기 (픽셀단위)
		//950,				//윈도우 창 세로크기 (픽셀단위) 이제는 stdafx에 define한 것을 사용한다
		WINSTARTX,				//윈도우 창 시작위치 X		
		WINSTARTY,				//윈도우 창 시작위치 y		
		WINSIZEX,				//윈도우 창 가로크기		
		WINSIZEY,				//윈도우 창 세로크기		
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	//클라이언트 영역 재조정 완료.
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//윈도우 창 화면에 보여주는 명령어
	ShowWindow(_hWnd, cmdShow);

	if (FAILED(_mg.init())) //이 FAILED가 init()을 실행시켜주는 역할도 한다
	{
		//FAILED(_mg.init())는 bool값을 계산하기 위해 init을 실행하고 실패하면 true를 줌
		//메인게임 클래스의 이닛(초기화) 함수가 실패하면
		//종료처리
		return 0;
	}

	//TranslateMessage(&message)는 WM_KEYDOWN을 받아서 현재 눌려진 키의 값을 가지고 문자를 만들어 내는 기능
	//WM_KEYDOWN에서 WM_CHAR을 만들어 내는 것
	//메시지 루프
	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);		//키보드 입력하는 순간 그 메시지 처리를 담당
	//	DispatchMessage(&message);		//실제로 윈도우로 메시지들을 전달하는 담당
	//}

	while (true) //GetMessage는 신호를 받지 않을 때 어떠한 행동을 하라고 명령할 수 없다
	{			 //PeekMessage는 가능
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) //메시지를 받을 때 ->message에 저장
		{							  //0, 0이면 모든 메시지를 받음	PM_REMOVE: 메시지 큐에서 메시지를 제거, PM_NOREMOVE: 메시지 큐에서 메시지를 제거하지 않음
									  //PM_REMOVE라도 WM_PAINT는 메시지 큐에서 제거하지 않고 처리될때까지 남겨둠
			if (message.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&message);		//키보드 입력하는 순간 그 메시지 처리를 담당
			DispatchMessage(&message);		//실제로 윈도우로 메시지들을 전달하는 담당
		}
		else //메시지를 받지 않을 때
		{
			TIMEMANAGER->update(60.0f);
			_mg.update();
			_mg.render(); //이제는 WM_PAINT 메시지를 받을 때 실행하지 않고 아무런 메시지가 없을 때 일정 시간마다 실행됨
		}
	}

	//GetMessage와 PeekMessage의 차이 :http://skmagic.tistory.com/282

	//릴리즈 함수가 밑에 있다는건 메시지를 다 돌았으면 메인게임 해제해라
	_mg.release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//기존의 윈도우프로시저 내용은 0922 파일 보기
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

//클라이언트 영역 재조정 함수
void setWindowSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left), (winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}
