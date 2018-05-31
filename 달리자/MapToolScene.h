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
	//backgroundChoiceStr�� static �ݹ��Լ� cityButton�� jailButton���� ���ǹǷ� static ���������Ѵ�.
	//(static �Լ��� ������� ��� �Ұ����ϰ� ���� static ������ ��� ����)

	float _loopY;

public:
	//HWND _hMapTool; //���� ������ �ڵ� //CreateWindow�� gameNode�� MainProc���� �Ѵ�
	static HWND _hMapTool; 
	//_hMapTool�� static �ݹ��Լ� cityButton�� jailButton���� ���ǹǷ� static ���������Ѵ�.
	//(static �Լ��� ������� ��� �Ұ����ϰ� ���� static ������ ��� ����)
	int _mapToolOn = 0;

	HWND _hInput;
	char mstr[128] = "�ʱ���";

	char nstr[128] = "���̸�";

	int _buttonCount = 0;

	float _scrollY;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	static void cityButton(void); //static�� ������� ������ �� �Լ��� ����Ű�� �������� Ÿ���� 
	static void jailButton(void); //void (MapToolScene::*) (void) �� �Ǿ 
	//void cityButton(void);	  //button Ŭ������ CALLBACK_FUNCTION�� Ÿ�� void (*) (void)�� �޶����Ƿ�
	//void jailButton(void);	  //button Ŭ������ init�� ���� ���� ����.

	MapToolScene();
	~MapToolScene();
};

