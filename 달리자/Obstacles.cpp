#include "stdafx.h"
#include "Obstacles.h"


Obstacles::Obstacles()
{
}


Obstacles::~Obstacles()
{
}

HRESULT Obstacles::init(void)
{
	m_pPosition = { 0, 0 };
	m_pSpeed = { 0,0 };
	//랙트를 만들어주지 않을경우 랙트 초기화
	m_pIR->_rc = RectMake(m_pPosition.x, m_pPosition.y, 50, 50);
	m_isAlive = true;
	return S_OK;
}

void Obstacles::release(void)
{
}

void Obstacles::update(void)
{
	if (!m_isAlive) return;
	m_pPosition = m_pPosition + m_pSpeed;

	
	m_pIR->_rc = RectMake(m_pPosition.x, m_pPosition.y, m_pIR->_rc.right - m_pIR->_rc.left, m_pIR->_rc.bottom - m_pIR->_rc.top);
}

void Obstacles::render(float cameraY)
{
	if (!m_isAlive) return;
	if (m_pIR->_image)
		m_pIR->_image->render(getMemDC(), m_pPosition.x, m_pPosition.y - cameraY);
	else
	{
	  Rectangle(getMemDC(), m_pIR->_rc.left, m_pIR->_rc.top - cameraY, m_pIR->_rc.right, m_pIR->_rc.bottom - cameraY);
	}
}
