#pragma once
#include "gameNode.h"

class CollisionManager;

class player : public gameNode
{
private:
	//ST_ImageAndRect _IR;

	//POINT _player;

	//float _cameraY;

	SYNTHESIZE(float, _cameraY, CamY);
	SYNTHESIZE(POINT, _player, PlayerPoint);
	SYNTHESIZE(ST_ImageAndRect, _IR, IR);

	vector<RECT> _test;
	vector<RECT>::iterator _testIter;

	image* _playerImage;
	CollisionManager* _colManager;

public:
	virtual HRESULT init(void);	
	virtual void release(void);		
	virtual void update(void);		
	virtual void render();		

	void linkColManager(CollisionManager* col) { _colManager = col; }

	player();
	~player();
};