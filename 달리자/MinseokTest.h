#pragma once
#include "gameNode.h"

class SiwoongTest;
class rectItem;
class player;
class prisoner;
class CollisionManager;
class Obstacles;

class MinseokBack : public gameNode
{
private:
	int m_nCameraY;
	image * m_pImage;
	player* m_pPlayer;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	void linkPlayer(player* player) { m_pPlayer = player; }

	MinseokBack();
	~MinseokBack();
};



class MinseokTest : public gameNode
{
private:

	MinseokBack * m_pBack;
	player* m_pPlayer;
	rectItem* m_pItem;
	rectItem* m_pItem2;
	std::vector<prisoner*> m_vecPrisoner;
	CollisionManager* m_pColManager;
	RECT m_rcObstacle;
	float m_fCameraY;
	Obstacles* m_pBigRect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();


	bool isCollisionReaction(const RECT* rcHold, RECT* rcMove);

	MinseokTest();
	~MinseokTest();

};