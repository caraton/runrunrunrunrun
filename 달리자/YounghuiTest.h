#pragma once
#include "gameNode.h"

class player;

class YounghuiTest : public gameNode
{
private:

	player* _player;

	float _cameraX;
	float _cameraY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	YounghuiTest();
	~YounghuiTest();
};