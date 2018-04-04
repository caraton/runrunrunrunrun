#pragma once
#include "gameNode.h"

class player;
class CollisionManager;

class SiwoongTest : public gameNode
{
private:
	player* _player;
	CollisionManager* _colManager;

	IR _testIR;


	float _cameraY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	SiwoongTest();
	~SiwoongTest();
};