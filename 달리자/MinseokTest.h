#pragma once
#include "gameNode.h"

class MinseokTest : public gameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	MinseokTest();
	~MinseokTest();
};