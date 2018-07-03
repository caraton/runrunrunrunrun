#include "stdafx.h"
#include "guards.h"


HRESULT guards::init(void)
{

	m_pPosition = { 0,0 };
	m_pSpeed = { 0,0 };
	m_pIR = new IR;
	m_pIR->_rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
	m_pIR->_image = IMAGEMANAGER->addFrameImage("guard_walk", "Image/guard_walk.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	m_pIR->_node = this;
	m_pIR->_type = "deadline";
	m_pPosition = { 0,WINSIZEY - 50 };
	m_pSpeed = { 0,-5.0f };
	m_isAlive = true;
	return S_OK;
	
}

void guards::release(void)
{
}

void guards::update(void)
{
	Obstacles::update();
	m_nImageFrameX = TIMEMANAGER->getFrameCount() / 10 % 6;

}

void guards::render(float cameraY)
{
	
	m_pIR->_image->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY, m_nImageFrameX, 0);
	
}

guards::guards()
{
}


guards::~guards()
{
}
