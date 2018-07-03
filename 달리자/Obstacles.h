#pragma once
#include "gameNode.h"
class Obstacles : public gameNode
{
protected:

	int m_nImageFrameX = 0;
	SYNTHESIZE(IR*, m_pIR, IR);
	SYNTHESIZE(fPoint, m_pPosition, Pos);
	SYNTHESIZE(fPoint, m_pSpeed, Speed);
	SYNTHESIZE(bool, m_isAlive, Alive);
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(float cameraY);
public:
	Obstacles();
	virtual ~Obstacles();
};

