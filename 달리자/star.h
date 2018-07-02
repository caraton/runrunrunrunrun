#pragma once
#include "stdafx.h"
#include "Items.h"
class star : public Items
{
private:
	int m_nImageFrameX = 0;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float cameraY);
	star();
	~star();
};

