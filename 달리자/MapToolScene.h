#pragma once
#include "button.h"
#include "image.h"

static image* _backBufferMapTool = IMAGEMANAGER->addImage("backBufferMapTool", WINSIZEX + 200, WINSIZEY);

struct newObjectData
{
	POINT _xycoordinate;
	string _imageName;
	image* _image;
};

class MapToolScene : public singletonBase<MapToolScene>
{
private:
	HDC _hdcMapTool;

	button* _cityB;
	button* _jailB;

	vector<button*> _objectBs;
	//int _totalObjectCount = 5;

	button* _saveB;
	button* _clearB;

	RECT _mapArea;

	float _loopY;
	float _maxY;

	vector<string> _obList;
	vector<string>::iterator _oliter;

	vector<button*> _bList;
	vector<button*>::iterator _bliter;

	static string _currentImageName;
	static image* _currentImage;
	static bool _isCurrentOn;
	vector<newObjectData*> _3tuplesList;
	vector<newObjectData*>::iterator _3tupleiter;

	vector<newObjectData*> _rearrangedList;
	void mapSave();
	static bool _savefbool;
	static bool _clearfbool;

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
	void update(void);
	void render(void);

	image* getBackBufferMapTool(void) { return _backBufferMapTool; };
	HDC getMemDCMapTool() { return _backBufferMapTool->getMemDC(); };
	HDC getHDCMapTool() { return _hdcMapTool; };

	static void cityButton(void); //static�� ������� ������ �� �Լ��� ����Ű�� �������� Ÿ���� 
	static void jailButton(void); //void (MapToolScene::*) (void) �� �Ǿ 
	//void cityButton(void);	  //button Ŭ������ CALLBACK_FUNCTION�� Ÿ�� void (*) (void)�� �޶����Ƿ�
	//void jailButton(void);	  //button Ŭ������ init�� ���� ���� ����.

	static void saveButton(void);
	static void clearButton(void);

	static void obButton(int imageNumer);

	MapToolScene();
	~MapToolScene();
};

