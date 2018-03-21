#pragma once
#include "gameNode.h"

class player : public gameNode
{
private:
	ST_ImageAndRect _IR;

	POINT _player;

	image* _playerImage;

public:
	virtual HRESULT init(void);	
	virtual void release(void);		
	virtual void update(void);		
	virtual void render();			

	player();
	~player();
};