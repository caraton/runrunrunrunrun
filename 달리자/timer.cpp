#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h> //TimeGetTime�Լ� ����

//QueryPerformanceFrequency, QueryPerformanceCounter ����:http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=735

#pragma comment(lib, "winmm.lib") //�Ⱦ��� LNK2019/LNK1120 ���� �߻� (timeGetTime�� ������� ���� �Լ���� ����)

HRESULT timer::init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency)) 
	{//__int64�� _periodFrequency�� &(���ۼ�Ʈ)�� �޾� __int64*�� ������ �ּ� -> LARGE_INTEGER* �� ������ ����ȯ
	 //QueryPerformanceFrequency�� ���κ��� Ÿ�̸Ӱ� �����Ǹ� ���� ��ȯ�ϸ� _periodFrequency�� cpu ���ļ��� �����ϰ�
	 //Ÿ�̸Ӱ� �������������� ������ ��ȯ�ϰ� _periodFrequency�� 0�� ����
		_isGoodHardware = true; //Ÿ�̸Ӹ� �����Ͽ� QueryPerformanceFrequency�� ������ ��ȯ�����Ƿ�
		
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime); 
		//QueryPerformanceCounter�� _lastTime�� ���� cpu Ŭ������ ������ (�Լ� bool ��ȯ���� QueryPerformanceFrequency�� ����) 

		_timeScale = 1.0f / _periodFrequency; //���� �ѹ� (�� Ŭ��)�� �ɸ��� �ð� = 1�ʴ� �������� ����
	}
	else
	{
		_isGoodHardware = false; //���κ��� Ÿ�̸� ��������

		_lastTime = timeGetTime(); //�� �Լ��� ������ 10ms �Ѱ� �� �� �ִٰ� �Ѵ�. ����Ȯ
		_timeScale = 0.001f;
	}

	//���� �ʱ�ȭ
	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;

	return S_OK;
}

void timer::tick(float lockFPS)
{
	if (_isGoodHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
		//_curTime�� �� ������ cpu Ŭ������ ����
	}
	else
	{
		_curTime = timeGetTime();
	}

	_timeElapsed = (_curTime - _lastTime) * _timeScale;
	//_curTime - _lastTime�� ���� ������ �� ���� ���̿� Ŭ�� ���� ��
	//_timeScale �� ���� �ѹ��� �ɸ��� �ð� (��Ŭ��) ���̹Ƿ� (Ŭ�� ����) * (1Ŭ���� �ð�) = ����ð�

	//�ٽɺκ�
	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS)) //������ tick �Լ��� ����� �������κ��� ����ð��� (1.0f / lockFPS)���� ���� ���
		{
			if (_isGoodHardware)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			}
			else
			{
				_curTime = timeGetTime();
			}

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		} //����ð��� (1.0f / lockFPS) ���� �Ǹ� while�� �������� 
		  //������ worldTime ����� �����ϰ� tick�� �����Ѵ�
	}
	//%% tick �Լ��� ����ǰ� update�� render�� ����ǰ��� �ٽ� tick�Լ��� ����� �� ������ tick �Լ��� ����� ����
	//%% �������� �̹� _timeElapsed >= (1.0f / lockFPS) �ϰ�� while���� ������� �ʰ� �ٷ� tick�Լ��� ����������.
	//%% ==> update + render ����ð��� (1.0f / lockFPS) �� ��� ������ ������ �������� �ʴ´�.

	_lastTime = _curTime;
	_FPSFrameCount++; //tick�Լ� �ѹ� ����ɶ�, update�� render�� �ѹ��� ����� -> ��������
	_FPSTimeElapsed += _timeElapsed; //�� ���� 1�ʸ��� ���µ� (_FPSTimeElapsed �� 1�� �ɵ��� _FPSFrameCount���� ��� ���� 1�ʵ��� frame ������ ��´�)
	_worldTime += _timeElapsed;

	if (_FPSTimeElapsed > 1.0f) 
	{
		_frameRate = _FPSFrameCount; //_FPSTimeElapsed(1��) ���� frame ������ _FPSFrameCount�̹Ƿ� _frameRate = _FPSFrameCount / (_FPSTimeElapsed ~= 1��)
		
		//frameRate ����� �������Ƿ� count�� fps ���� ���ؽð� �ʱ�ȭ
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
	//_FPSTimeElapsed(fps ���� ���ؽð�)�� �� �����Ӹ��� _timeElapsed ��ŭ�� ��������
	//������Ʈ+���� ����ð��� ���� ����ð��� (1.0f / lockFPS)���� ª�� �̻����� ��쿡�� _timeElapsed = (1.0f / lockFPS) �̹Ƿ�
	//_FPSTimeElapsed �� 1�ʰ� �ɶ��� _FPSFrameCount = lockFPS�� �ȴ� (1�� = _timeElapsed * lockFPS)
	//%% �׷��� update + render ����ð��� (1.0f / lockFPS) �� ��� ������ ������ �������� �����Ƿ�
	//%% _timeElapsed �� (1.0f / lockFPS) ���� Ŀ���� �ǰ� ���� 1�� =  _timeElapsed * x , x < lockFPS�� �Ǿ�
	//%% _FPSFrameCount = x ��, lockFPS ���� �����ӷ���Ʈ�� �۾�����.
}

unsigned long timer::getFrameRate(char * str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate); //��ǲ���� ���� str �����Ϳ� "FPS : �����ӷ���Ʈ��"�� �־���
	}
	return _frameRate;
}

timer::timer()
{
}

timer::~timer()
{
}
