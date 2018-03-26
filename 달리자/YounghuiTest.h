#pragma once
#include "gameNode.h"


class YounghuiTest : public gameNode
{
private:
	


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	YounghuiTest();
	~YounghuiTest();
};