#pragma once
#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
	timer* _timer; 

public:
	HRESULT init();
	void release();
	void update(float lock = 0.0f); //1�ʴ� ���� frame��(lock)�� �޾� tick�� ������
	void render(HDC hdc); //����� ����� ��� �����ӷ���Ʈ, ���ؽð�, ������ ���� ����ð��� ȭ�鿡 ǥ������ 

	inline float getElapsedTime() const { return _timer->getElapsedTime(); }; //unity�� Time.deltaTimeó�� ��밡��
	inline float getWorldTime() const { return _timer->getWorldTime(); };

	timeManager();
	~timeManager();
};