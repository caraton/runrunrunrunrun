#pragma once
#include "gameNode.h"

class SiwoongTest;
class rectItem;

class MinseokTest : public gameNode
{
private:

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