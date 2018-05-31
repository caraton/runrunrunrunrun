#pragma once
#include "button.h"

class MapToolScene : public singletonBase<MapToolScene>
{
private:
	button* _cityB;
	button* _jailB;

	vector<button*> _objectBs;
	int _totalObjectCount = 5;

	//char backgroundChoiceStr[128];
	static char backgroundChoiceStr[128];
	//backgroundChoiceStr은 static 콜백함수 cityButton과 jailButton에서 사용되므로 static 변수여야한다.
	//(static 함수는 멤버변수 사용 불가능하고 오직 static 변수만 사용 가능)

	float _loopY;

public:
	//HWND _hMapTool; //맵툴 윈도우 핸들 //CreateWindow는 gameNode의 MainProc에서 한다
	static HWND _hMapTool; 
	//_hMapTool은 static 콜백함수 cityButton과 jailButton에서 사용되므로 static 변수여야한다.
	//(static 함수는 멤버변수 사용 불가능하고 오직 static 변수만 사용 가능)
	int _mapToolOn = 0;

	HWND _hInput;
	char mstr[128] = "맵길이";

	char nstr[128] = "맵이름";

	int _buttonCount = 0;

	float _scrollY;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	static void cityButton(void); //static을 사용하지 않으면 이 함수를 가리키는 포인터의 타입은 
	static void jailButton(void); //void (MapToolScene::*) (void) 가 되어서 
	//void cityButton(void);	  //button 클래스의 CALLBACK_FUNCTION의 타입 void (*) (void)와 달라지므로
	//void jailButton(void);	  //button 클래스의 init에 넣을 수가 없다.

	MapToolScene();
	~MapToolScene();
};

