#pragma once
#include "gameNode.h"


class Items : public gameNode
{
protected:
	SYNTHESIZE(IR, m_pIR, IR);
	SYNTHESIZE(fPoint, m_pPosition, Pos);
	SYNTHESIZE(fPoint, m_pSpeed, Speed);
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(float cameraY);

public:
	Items();
	virtual ~Items();
};

