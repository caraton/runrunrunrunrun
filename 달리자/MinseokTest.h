#pragma once
#include "gameNode.h"

class SiwoongTest;
class rectItem;
class player;

class Minseokplayer : public gameNode
{
private:
	SYNTHESIZE(ST_ImageAndRect ,_IR,IR);

	SYNTHESIZE(fPoint, _player, Point);

	image* _playerImage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	Minseokplayer();
	~Minseokplayer();
};

class MinseokBack : public gameNode
{
private:
	int m_nCameraY;
	image * m_pImage;
	Minseokplayer* m_pPlayer;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	void linkPlayer(Minseokplayer* player) { m_pPlayer = player; }

	MinseokBack();
	~MinseokBack();
};



class MinseokTest : public gameNode
{
private:

	MinseokBack * m_pBack;
	Minseokplayer* m_pPlayer;
	RECT m_rPlayer;
	rectItem* m_pItem;
	rectItem* m_pItem2;
	RECT m_rcObstacle;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();


	bool isCollisionReaction(const RECT* rcHold, RECT* rcMove);

	MinseokTest();
	~MinseokTest();

};