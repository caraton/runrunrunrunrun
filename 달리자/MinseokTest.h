#pragma once
#include "gameNode.h"

class SiwoongTest;
class rectItem;
class player;
class CollisionManager;

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
	RECT m_rPlayer;
	rectItem* m_pItem;
	rectItem* m_pItem2;
	CollisionManager* m_pColManager;
	RECT m_rcObstacle;
	float m_fCameraY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();


	bool isCollisionReaction(const RECT* rcHold, RECT* rcMove);

	MinseokTest();
	~MinseokTest();

};