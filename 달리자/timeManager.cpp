#include "stdafx.h"
#include "timeManager.h"

HRESULT timeManager::init()
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release()
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

void timeManager::render(HDC hdc)
{
	char str[256];
	string frameRate;
	SetBkMode(hdc, TRANSPARENT);
	//��Ʈ ��׶��� ����
	//TRANSPARENT	: ����
	//OPAQUE		: ������

//#��ó�� ���ǹ����� ����׿� ������ ����
#ifdef _DEBUG
	{
		//FPS
		wsprintf(str, "�����ð��� �����Ӱ��� (FPS) : %d", _timer->getFrameRate()); //_timer->getFrameRate() �μ� str*�� ���ڸ��� �ξ� NULL ���� -> �Լ� ������ wsprintf �������� �ʰ� �ٷ� FPS �� return�� ��
		TextOut(hdc, 0, 0, str, strlen(str));

		//WorldTime
		sprintf_s(str, "�Ѱ����ð� : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		//ElapsedTime
		sprintf_s(str, "����ð�(���������ӱ���) : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}
#else //������
	{
		//FPS
		wsprintf(str, "�����ð��� �����Ӱ��� (FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif
}

timeManager::timeManager()
	: _timer(NULL) //������ ���� ������ _timer ������ �ʱ�ȭ
{
}

timeManager::~timeManager()
{
}
