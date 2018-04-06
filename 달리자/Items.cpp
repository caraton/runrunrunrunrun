#include "stdafx.h"
#include "Items.h"


Items::Items()
{
}


Items::~Items()
{
}

HRESULT Items::init(void)
{
	m_pPosition = { 0, 0 };
	m_pSpeed = { 0,0 };
	return S_OK;
}

void Items::release(void)
{
}

void Items::update(void)
{
	m_pPosition = m_pPosition + m_pSpeed;
}

void Items::render(float cameraY)
{
	if (m_pIR._image)
		m_pIR._image->render(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY);
	else
		m_pIR._image->frameRender(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY);
}
