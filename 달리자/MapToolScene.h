#pragma once
#include "button.h"
#include "image.h"

static image* _backBufferMapTool = IMAGEMANAGER->addImage("backBufferMapTool", WINSIZEX + 200, WINSIZEY);

class MapToolScene : public singletonBase<MapToolScene>
{
private:
	HDC _hdcMapTool;

	button* _cityB;
	button* _jailB;

	vector<button*> _objectBs;
	int _totalObjectCount = 5;

	//char backgroundChoiceStr[128];
	static char backgroundChoiceStr[128];
	//backgroundChoiceStr은 static 콜백함수 cityButton과 jailButton에서 사용되므로 static 변수여야한다.
	//(static 함수는 멤버변수 사용 불가능하고 오직 static 변수만 사용 가능)

	float _loopY;

	vector<string> _obList;
	vector<string>::iterator _oliter;

	vector<button*> _bList;
	vector<button*>::iterator _bliter;

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
	HRESULT init2(void);
	void release(void);
	void update(void);
	void render(void);

	image* getBackBufferMapTool(void) { return _backBufferMapTool; };
	HDC getMemDCMapTool() { return _backBufferMapTool->getMemDC(); };
	HDC getHDCMapTool() { return _hdcMapTool; };

	static void cityButton(void); //static을 사용하지 않으면 이 함수를 가리키는 포인터의 타입은 
	static void jailButton(void); //void (MapToolScene::*) (void) 가 되어서 
	//void cityButton(void);	  //button 클래스의 CALLBACK_FUNCTION의 타입 void (*) (void)와 달라지므로
	//void jailButton(void);	  //button 클래스의 init에 넣을 수가 없다.

	static void obButton(void);

	MapToolScene();
	~MapToolScene();
};

