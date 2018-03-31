#pragma once
#include "gameNode.h"

class CollisionManager;

class player : public gameNode
{
private:
	//업데이트에 들어가는 함수들
	void move();
private:
	//ST_ImageAndRect _IR;

	//POINT _player;

	//float _cameraY;

	SYNTHESIZE(float, _cameraY, CamY);
	SYNTHESIZE(fPoint, m_fpPosition, Pos);
	SYNTHESIZE(ST_ImageAndRect, m_IR, IR);
	SYNTHESIZE(fPoint, m_fpSpeed, Speed);
	float m_fBasicSpeedY;

	vector<RECT> _test;
	vector<RECT>::iterator _testIter;

	image* m_pPlayerImage;
	CollisionManager* m_pColManager;

public:
	virtual HRESULT init(void);	
	virtual void release(void);		
	virtual void update(void);		
	virtual void render();		

	void linkColManager(CollisionManager* col) { m_pColManager = col; }

	player();
	~player();
};