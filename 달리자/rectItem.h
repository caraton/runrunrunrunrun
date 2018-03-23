#pragma once
#include "gameNode.h"
class player;
class Minseokplayer;

class rectItem : public gameNode
{
private:
	SYNTHESIZE(RECT, m_rc, Rect);
	SYNTHESIZE(POINT, m_pPosition, Pos);
	SYNTHESIZE(POINT, m_pSpeed, Speed);
	Minseokplayer* m_pPlayer;
	rectItem* m_pItem;
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

