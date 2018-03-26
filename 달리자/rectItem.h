#pragma once
#include "gameNode.h"
class player;
class Minseokplayer;

class rectItem : public gameNode
{
private:
	SYNTHESIZE(RECT, m_rc, Rect);
	SYNTHESIZE(fPoint, m_pPosition, Pos);
	SYNTHESIZE(fPoint, m_pSpeed, Speed);
	Minseokplayer* m_pPlayer;
	rectItem* m_pItem;
	RECT m_rcObstacle;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
	void linkPlayer(Minseokplayer* player) { m_pPlayer = player; }
	void linkItem(rectItem* item) { m_pItem = item; }
	
	

	rectItem();
	~rectItem();
};

