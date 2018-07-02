#pragma once
#include "gameNode.h"


typedef enum HEADTYPEinITEM
{
	t_idle,
	t_player,
	t_item,
	t_end
} headType;

class Items : public gameNode
{
protected:
	SYNTHESIZE(IR*, m_pIR, IR);
	SYNTHESIZE(fPoint, m_pPosition, Pos);
	SYNTHESIZE(fPoint, m_pSpeed, Speed);
	SYNTHESIZE(bool, m_isAlive,Alive);

	void* m_pHead;
	headType m_eHeadType;


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(float cameraY);
	
	void linkHead(void * Head, headType type);
public:
	Items();
	virtual ~Items();
};

