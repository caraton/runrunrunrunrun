#pragma once
#include "gameNode.h"
class rectItem : public gameNode
{
private:
	SYNTHESIZE(RECT, m_rc, Rect);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	rectItem();
	~rectItem();
};

