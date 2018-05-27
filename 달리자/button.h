#pragma once
#include "gameNode.h"

//콜백함수: 함수의 호출 실행 시점을 프로그래머가 아닌 시스템에서 결정하는 함수 API의 WndProc이 그 예
//콜백은 다른 코드(함수)의 인수로서 넘겨주는 실행 가능한 코드(함수)를 말한다. 콜백을 넘겨받는 코드(함수)는
//이 콜백을 필요에 따라 즉시 실행할 수도 있고, 아니면 나중에 실행할 수도 있다.
//콜백함수, 함수포인터 참조: https://stackoverflow.com/questions/2298242/callback-functions-in-c
//함수포인터 추가내용은 스트럭쳐,포인터, 함수포인터 프로젝트에서 확인하기

//함수포인터를 이용해 콜백함수를 구현한다.
typedef void(*CALLBACK_FUNCTION)(void);
//void func (void) 인 함수의 포인터 void (*) (void)를 typedef를 이용해 CALLBACK_FUNCTION으로 정의

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL, //버튼이 안눌릴 때
	BUTTONDIRECTION_MOUSEOVER, //버튼이 안눌렸지만 마우스가 버튼 위에 있을 때
	BUTTONDIRECTION_UP,   //버튼이 눌렸다가 올라갈 때
	BUTTONDIRECTION_DOWN  //버튼이 눌렸을 때
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction; //버튼의 상태를 알려줄 enum BUTTONDIRECTION 의 인스턴스

	const char* _imageName; //버튼 이미지 이름
	image* _image; //이미지 매니저의 findImage(_imageName)으로 리턴받은 이미지 포인터 저장
	RECT _rc; //버튼 인식부분 영역을 담을 렉트
	float _x, _y; //버튼의 중점 x,y 좌표값들 init에서 받아 저장

	POINT _btnDownFramePoint; //버튼이 눌릴 때 프레임렌더에서 몇번째 그림을 렌더할지 알려줄 정보 담음
	POINT _btnUpFramePoint; //버튼이 눌리지 않을 때 프레임렌더에서 몇번째 그림을 렌더할지 알려줄 정보 담음
	POINT _btnMouseoverFramePoint; //마우스오버 상태일 때 프레임렌더에서 몇번째 그림을 렌더할지 알려줄 정보 담음

	CALLBACK_FUNCTION _callbackFunction; //버튼이 눌리면 실행할 함수의 포인터를 담을 변수

public:
	HRESULT init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, POINT btnMouseoverFramePoint, CALLBACK_FUNCTION cbFunction);
	//이미지매니저에서 이미지를 불러들일때 사용할 imageName, 버튼 중점 x좌표, 버튼 중점 y좌표 (RectMakeCenter사용)
	//, POINT btnDownFramePoint, POINT btnUpFramePoint 둘은 버튼의 상태에 따라 프레임 렌더로 버튼 이미지 그림을 바꿀 때 필요한
	//프레임 렌더 x,y 좌표값 저장, 버튼이 눌렸을 때 실행할 콜백함수 포인터 cbFunction
	
	void release();
	void update();
	void render(HDC hdc); //맵툴에서도 이 버튼 클래스를 사용할 수 있도록 render함수 변경(HDC를 인수로 받도록)

	button();
	~button();
};

