#pragma once
#include "stdafx.h"
#include "Obstacles.h"
class guards : public Obstacles
{
private:
	
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float cameraY);

	guards();
	~guards();
};

