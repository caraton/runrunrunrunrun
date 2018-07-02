#pragma once
#include "gameNode.h"

class CollisionCheckManager;

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
	SYNTHESIZE(bool, m_isFire, Fire);
	SYNTHESIZE(IR*, m_pIR, IR);
	SYNTHESIZE(fPoint, m_pPosition, Pos);
	SYNTHESIZE(fPoint, m_pSpeed, Speed);
	SYNTHESIZE(bool, m_isAlive,Alive);

	void* m_pHead;
	headType m_eHeadType;
	CollisionCheckManager* m_pColManager;
	vector<IR*>::iterator _colIter;


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(float cameraY);
	
	void linkHead(void * Head, headType type);
	void linkColManager(CollisionCheckManager* col) { m_pColManager = col; }

public:
	Items();
	virtual ~Items();
};

