#pragma once
#include "Items.h"


class CollisionCheckManager;

class prisoner : public Items
{
private:


	int m_nImageFrameX = 0;
	int m_nCameraY = 0;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float cameraY);
	//void linkHead(void * Head, headType type);
	prisoner();
	~prisoner();

};

