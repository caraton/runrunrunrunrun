#pragma once
#include "gameNode.h"

class SiwoongTest;
class rectItem;
class player;

class MinseokTest : public gameNode
{
private:

	player* m_pPlayer;
	RECT m_rPlayer;
	rectItem* m_pItem;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	MinseokTest();
	~MinseokTest();
};