#pragma once
#include "gameNode.h"
class player;


class rectItem : public gameNode
{
private:
	SYNTHESIZE(IR, m_pIR, IR);
	SYNTHESIZE(fPoint, m_pPosition, Pos);
	SYNTHESIZE(fPoint, m_pSpeed, Speed);
	player* m_pPlayer;
	rectItem* m_pItem;
	RECT m_rcObstacle;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float cameraY);
	void linkPlayer(player* player) { m_pPlayer = player; }
	void linkItem(rectItem* item) { m_pItem = item; }
	
	

	rectItem();
	~rectItem();
};

