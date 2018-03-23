#pragma once
#include "singletonBase.h"
#include "gameNode.h"
#include <vector>
#include <list>

class player;

class CollisionManager : public gameNode
{
private:
	vector<list<IR*>*> _hashTable;
	vector<list<IR*>*>::iterator _vecIter;
	list<IR*>::iterator _iter;

	player* _player;

	//bool _gameover;
	SYNTHESIZE(bool, _gameover, Gameover);

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	IR* addIR(IR* ir);
	void deleteIR(IR* ir);

	bool findIRNear(IR* ir, OUT vector<IR*>* IRList);
	bool checkCollision(IR* ir, OUT vector<IR*>* colList);

	void linkPlayer(player* player) { _player = player; }

	CollisionManager();
	~CollisionManager();
};