#pragma once
#include "gameNode.h"

class player;
class CollisionCheckManager;

class SiwoongTest : public gameNode
{
private:
	player* _player;
	CollisionCheckManager* _colManager;

	IR _testIR;
	int _testIRy;

	vector<IR> _trashcans;
	vector<IR>::iterator _tcIter;

	float _cameraY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	SiwoongTest();
	~SiwoongTest();
};