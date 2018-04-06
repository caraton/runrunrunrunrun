#pragma once
#include "Items.h"

typedef enum HEADTYPEinITEM
{
	t_idle,
	t_player,
	t_item,
	t_end
} headType;

class prisoner : public Items
{
private:

	int m_nImageFrameX = 0;
	void* m_pHead;
	headType m_eHeadType;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(float cameraY);
	void linkHead(void * Head, headType type);
	prisoner();
	~prisoner();
};

