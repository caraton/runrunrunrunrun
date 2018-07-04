#include "stdafx.h"
#include "box.h"


HRESULT box::init(void)
{
	m_pPosition = { 0,0 };
	m_pSpeed = { 0,0 };
	m_pIR = new IR;
	m_pIR->_rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
	m_pIR->_image = IMAGEMANAGER->addFrameImage("object_box_icon", "Image/Obstacles/object_box_icon.bmp", 100, 50, 2, 1, true, RGB(255, 0, 255));
	m_pIR->_node = this;
	m_pIR->_type = "can";
	m_pPosition = { 0,WINSIZEY - 50 };
	m_isAlive = true;
	return S_OK;
}

void box::release(void)
{
}

void box::update(void)
{
	Obstacles::update();
	m_nImageFrameX = TIMEMANAGER->getFrameCount() / 10 % 2;
}

void box::render(float cameraY)
{
	if (!m_isAlive) return;
	m_pIR->_image->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY, 0, 0);
}

box::box()
{
}


box::~box()
{
}
