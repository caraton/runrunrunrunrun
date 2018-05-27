#pragma once
#include "gameNode.h"

class MinseokTest;
class YounghuiTest;
class SiwoongTest;
class MapToolScene;

class mainGame : public gameNode
{
private:
	MapToolScene * _mapToolScene;
public:
	virtual HRESULT init(void);		//WM_CREATE ���ӳ�忡�� ��ӹ��� FAILED(_mg.init())�� ����ϱ� ���ؼ��� HRESULT�� �����ؾ���
	virtual void release(void);		//WM_DESTROY ���ӳ�忡�� ��ӹ���
	virtual void update(void);		//WM_TIMER ���ӳ�忡�� ��ӹ���
	virtual void render();			//WM_PAINT ���ӳ�忡�� ��ӹ���
									//���, �������̵�, virtual�� ���� ����:http://blog.eairship.kr/175

	mainGame();
	~mainGame();
};