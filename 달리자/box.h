#pragma once
#include "stdafx.h"
#include "Obstacles.h"
class box : public Obstacles
{
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float cameraY);
	box();
	~box();
};

