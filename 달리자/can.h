#pragma once
#include "stdafx.h"
#include "Obstacles.h"
class can : public Obstacles
{
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float cameraY);
	can();
	~can();
};

