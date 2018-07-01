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

	void mtLoadMap(); //loadMap�� gameNode���� �����ϴ� �Լ��̰�, mtLoadMap�� ���� ������ �ε� ��ư�� ������ �� �����ϴ� �Լ�
	static bool _loadfbool;
	vector<string> _mapData;

	static bool _clearfbool;
	static bool _erasefbool;
	bool _isErasing;

public:
	//HWND _hMapTool; //���� ������ �ڵ� //CreateWindow�� gameNode�� MainProc���� �Ѵ�
	static HWND _hMapTool; 
	//_hMapTool�� static �ݹ��Լ� cityButton�� jailButton���� ���ǹǷ� static ���������Ѵ�.
	//(static �Լ��� ������� ��� �Ұ����ϰ� ���� static ������ ��� ����)
	int _mapToolOn = 0;

	HWND _hInput;
	char mstr[128] = "0";
	int mint;

	HWND _hInput2;
	char mstr2[128] = "0";
	string _mapname;
	

	char nstr[128] = "���̸�";

	//char backgroundChoiceStr[128];
	static char backgroundChoiceStr[128];
	//backgroundChoiceStr�� static �ݹ��Լ� cityButton�� jailButton���� ���ǹǷ� static ���������Ѵ�.
	//(static �Լ��� ������� ��� �Ұ����ϰ� ���� static ������ ��� ����)

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

	static void cityButton(void); //static�� ������� ������ �� �Լ��� ����Ű�� �������� Ÿ���� 
	static void jailButton(void); //void (MapToolScene::*) (void) �� �Ǿ 
	//void cityButton(void);	  //button Ŭ������ CALLBACK_FUNCTION�� Ÿ�� void (*) (void)�� �޶����Ƿ�
	//void jailButton(void);	  //button Ŭ������ init�� ���� ���� ����.

	static void saveButton(void);
	static void loadButton(void);
	static void clearButton(void);
	static void eraseButton(void);

	static void obButton(int imageNumer);
	static void itemButton(int imageNumer);

	MapToolScene();
	~MapToolScene();
};

