#pragma once
#include "stdafx.h"
#include "guards.h"
#include "Items.h"

class CollisionCheckManager;

class smokeBomb : public Items
{
private :

	int m_nImageFrameX = 0;

	image* m_pBombImage;
	image* m_pSmokeImage;

	vector<guards*> m_vecGuards;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float cameraY);
	void linkGuards(vector<guards*> vecGuards);
	smokeBomb();
	~smokeBomb();
};

