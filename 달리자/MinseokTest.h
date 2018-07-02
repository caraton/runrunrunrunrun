#pragma once
#include "gameNode.h"

class SiwoongTest;
class rectItem;
class player;
class prisoner;
class CollisionCheckManager;
class Obstacles;
class guards;
class star;
class Items;

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
	std::vector<Items*> m_vecItems;
	CollisionCheckManager* m_pColManager;
	RECT m_rcObstacle;
	float m_fCameraY;
	std::vector<guards*> m_vecGaurd;


	//
	IR* testTemp;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();


	bool isCollisionReaction(const RECT* rcHold, RECT* rcMove);

	MinseokTest();
	~MinseokTest();

};