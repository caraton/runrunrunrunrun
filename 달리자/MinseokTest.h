#pragma once
#include "gameNode.h"

class SiwoongTest;
class rectItem;
class player;
class prisoner;
class CollisionCheckManager;
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

	//Å×½ºÆ®
	IR _testIR;
	int _testIRy;
	
	MinseokBack * m_pBack;
	player* m_pPlayer;
	std::vector<prisoner*> m_vecPrisoner;
	CollisionCheckManager* m_pColManager;
	RECT m_rcObstacle;
	float m_fCameraY;
	Obstacles* m_pDeadLine;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();


	bool isCollisionReaction(const RECT* rcHold, RECT* rcMove);

	MinseokTest();
	~MinseokTest();

};