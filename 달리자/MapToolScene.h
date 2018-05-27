#pragma once
#include "button.h"

class MapToolScene
{
private:
	button* _cityB;
	button* _jailB;

	static char backgroundChoiceStr[128];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	static void cityButton(void);
	static void jailButton(void);

	MapToolScene();
	~MapToolScene();
};

