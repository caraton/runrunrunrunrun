#include "stdafx.h"
#include "YounghuiTest.h"

HRESULT YounghuiTest::init(void)
{
	return S_OK;
}

void YounghuiTest::release(void)
{
}

void YounghuiTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("�ÿ���");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("�μ���");
	}

	


}

void YounghuiTest::render(void)
{
}

YounghuiTest::YounghuiTest()
{
}

YounghuiTest::~YounghuiTest()
{
}
