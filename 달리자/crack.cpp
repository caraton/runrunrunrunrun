#include "stdafx.h"
#include "crack.h"


HRESULT crack::init(void)
{
	m_pPosition = { 0,0 };
	m_pSpeed = { 0,0 };
	m_pIR = new IR;
	m_pIR->_rc = RectMake(m_pPosition.x, m_pPosition.y, 100, 50);
	m_pIR->_image = IMAGEMANAGER->addFrameImage("crack", "Image/Obstacles/crack.bmp", 200, 50, 2, 1, true, RGB(255, 0, 255));
	m_pIR->_node = this;
	m_pIR->_type = "can";
	m_pPosition = { 0,WINSIZEY - 50 };
	return S_OK;
}

void crack::release(void)
{
}

void crack::update(void)
{
	Obstacles::update();
	m_nImageFrameX = TIMEMANAGER->getFrameCount() / 10 % 2;
}

void crack::render(float cameraY)
{
	m_pIR->_image->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY, m_nImageFrameX, 0);
}

crack::crack()
{
}


crack::~crack()
{
}
