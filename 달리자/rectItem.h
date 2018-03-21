#pragma once
#include "gameNode.h"
class rectItem : public gameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	rectItem();
	~rectItem();
};

