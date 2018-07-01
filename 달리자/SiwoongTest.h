#pragma once
#include "gameNode.h"

class player;
class CollisionCheckManager;

class SiwoongTest : public gameNode
{
	//typedef HRESULT(SiwoongTest::*initP) (void);
	typedef void(SiwoongTest::*updateP) (void);
	typedef void(SiwoongTest::*renderP) (void);

private:
	player* _player;
	CollisionCheckManager* _colManager;

	IR _testIR;
	int _testIRy;

	vector<IR> _trashcans;
	vector<IR>::iterator _tcIter;

	float _cameraY;

	vector<string> _obList;
	vector<string> _itemList;
	vector<string>::iterator _oliter;

	vector<IR*> _obIRList; //�ʵ����Ϳ��� �о���� ��ֹ����� IR* ��Ƴ��� ������ ��� + �޸� ������ ��밡��?
	vector<IR*> _itemIRList;
	vector<IR*>::iterator _obIRIter;

	int _frameCount; //��� �������� 0~39 ���̰� ����

	void loadMap(vector<string> data, CollisionCheckManager* _colM);

public:
	//initP _initP;
	updateP _updateP;
	renderP _renderP;

	HWND _sInput;
	string _mapName;
	int _mLength;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void selectUpdate(void);
	void selectRender(void);

	HRESULT gameInit(void);
	void gameUpdate(void);
	void gameRender(void);

	SiwoongTest();
	~SiwoongTest();
};