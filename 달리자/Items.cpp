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
	m_pIR->_rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50); 
	m_isAlive = true;
	return S_OK;
}

void Items::release(void)
{
}

void Items::update(void)
{
	m_pPosition = m_pPosition + m_pSpeed;
	m_pIR->_rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
}

void Items::linkHead(void * Head, headType type)
{
	m_eHeadType = type;
	m_pHead = Head;
}

void Items::render(float cameraY)
{
	if (m_pIR->_image)
		m_pIR->_image->render(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY);

}
