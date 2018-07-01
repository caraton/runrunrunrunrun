#pragma once
#include "button.h"
#include "image.h"

static image* _backBufferMapTool = IMAGEMANAGER->addImage("backBufferMapTool", WINSIZEX + 400, WINSIZEY);

struct newObjectData
{
	POINT _xycoordinate;
	string _imageName;
	image* _image;
	bool _isItem;
};

class MapToolScene : public singletonBase<MapToolScene>
{
private:
	HDC _hdcMapTool;

	button* _cityB;
	button* _jailB;

	button* _saveB;
	button* _loadB;
	button* _clearB;
	button* _eraseB;

	RECT _mapArea;

	float _loopY;
	float _maxY;

	vector<string> _obList;
	vector<string> _itemList;
	vector<string>::iterator _oliter;

	vector<button> _bList;
	vector<button> _itembList;
	vector<button>::iterator _bliter;

	static string _currentImageName;
	static image* _currentImage;
	static bool _isCurrentOn;
	static bool _isItemnow;
	vector<newObjectData*> _4tuplesList;
	vector<newObjectData*>::iterator _4tupleiter;

	vector<newObjectData*> _rearrangedList;
	
	void mapSave();
	static bool _savefbool;

	void mtLoadMap(); //loadMap은 gameNode에서 실행하는 함수이고, mtLoadMap은 맵툴 내에서 로드 버튼이 눌렸을 떄 실행하는 함수
	static bool _loadfbool;
	vector<string> _mapData;

	static bool _clearfbool;
	static bool _erasefbool;
	bool _isErasing;

public:
	//HWND _hMapTool; //맵툴 윈도우 핸들 //CreateWindow는 gameNode의 MainProc에서 한다
	static HWND _hMapTool; 
	//_hMapTool은 static 콜백함수 cityButton과 jailButton에서 사용되므로 static 변수여야한다.
	//(static 함수는 멤버변수 사용 불가능하고 오직 static 변수만 사용 가능)
	int _mapToolOn = 0;

	HWND _hInput;
	char mstr[128] = "0";
	int mint;

	HWND _hInput2;
	char mstr2[128] = "0";
	string _mapname;
	

	char nstr[128] = "맵이름";

	//char backgroundChoiceStr[128];
	static char backgroundChoiceStr[128];
	//backgroundChoiceStr은 static 콜백함수 cityButton과 jailButton에서 사용되므로 static 변수여야한다.
	//(static 함수는 멤버변수 사용 불가능하고 오직 static 변수만 사용 가능)

	int _buttonCount = 0;

	float _scrollY;

	HRESULT init(void);
	HRESULT init2(void);
	void release(void);
	void release2(void);
	void update(void);
	void render(void);

	image* getBackBufferMapTool(void) { return _backBufferMapTool; };
	HDC getMemDCMapTool() { return _backBufferMapTool->getMemDC(); };
	HDC getHDCMapTool() { return _hdcMapTool; };

	void loadMap(vector<string> data);

	static void cityButton(void); //static을 사용하지 않으면 이 함수를 가리키는 포인터의 타입은 
	static void jailButton(void); //void (MapToolScene::*) (void) 가 되어서 
	//void cityButton(void);	  //button 클래스의 CALLBACK_FUNCTION의 타입 void (*) (void)와 달라지므로
	//void jailButton(void);	  //button 클래스의 init에 넣을 수가 없다.

	static void saveButton(void);
	static void loadButton(void);
	static void clearButton(void);
	static void eraseButton(void);

	static void obButton(int imageNumer);
	static void itemButton(int imageNumer);

	MapToolScene();
	~MapToolScene();
};

