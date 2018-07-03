#pragma once
#include "gameNode.h"

class CollisionCheckManager;
class Items;

class player : public gameNode
{
private:
	//업데이트에 들어가는 함수들
	void move();

private:
	void useItem();
private:
	//ST_ImageAndRect _IR;

	//POINT _player;

	//float _cameraY;
	bool m_isStar = false;

	int m_nStarStartTime = 0;

	SYNTHESIZE(float, m_fCamaraY, CamY);
	SYNTHESIZE(fPoint, m_fpPosition, Pos);
	SYNTHESIZE(ST_ImageAndRect, m_IR, IR);
	SYNTHESIZE(fPoint, m_fpSpeed, Speed);
	float m_fBasicSpeedY;

	vector<RECT> _test;
	vector<RECT>::iterator _testIter;

	vector<IR*>::iterator _colIter;

	vector<Items*> _items;
	vector<Items*>::iterator _itemIter;

	image* m_pPlayerImage;
	image* _playerDeath;
	CollisionCheckManager* m_pColManager;

public:
	virtual HRESULT init(void);	
	virtual void release(void);		
	virtual void update(void);		
	virtual void render(float cameraY);
	virtual void render();
	virtual void render(bool gameover);

	void linkColManager(CollisionCheckManager* col) { m_pColManager = col; }

	player();
	~player();
};