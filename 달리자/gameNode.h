#pragma once
#include "image.h"

//���� gameNode�� ��ӹ޴� Ŭ�������� �����̹Ƿ� class �ٱ��� static���� ����
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);
//hdc�� ��Ʈ�� ��ȭ���� ���� �̹������� �ٷ� �������� �ʰ� _backBuffer�� hMemDC�� ��Ʈ�ʵ�ȭ���� �ϴ� ���� ������
//�� �� �� ����� ������ hMemDC�� ��Ʈ�� ��ȭ������ hdc�� ��Ʈ�� ��ȭ���� ����
static image* _backBufferMapTool = IMAGEMANAGER->addImage("backBufferMapTool", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	//HDC _hdcMapTool;
	bool _managerInit; //gameNode�� init���� �̱��� �Ŵ������� init �Լ����� �����ϴ°�?

	//image* _backBuffer;	
	//hdc�� ��Ʈ�� ��ȭ���� ���� �̹������� �ٷ� �������� �ʰ� _backBuffer�� hMemDC�� ��Ʈ�ʵ�ȭ���� �ϴ� ���� ������
	//�� �� �� ����� ������ hMemDC�� ��Ʈ�� ��ȭ������ hdc�� ��Ʈ�� ��ȭ���� ����
	
	//void setBackBuffer(); �̹����Ŵ��� ���� �Ŀ��� �ʿ����

	//�浹���� �߰� ������ (2018/03/28)
	//bool _isTrigger;
	//bool _isOnCollision;

public:
	virtual HRESULT init(void);    //WM_CREATE  FAILED(_mg.init())�� ����ϱ� ���ؼ��� HRESULT�� �����ؾ���
	virtual HRESULT init(bool managerInit); //�� init�Լ�
	virtual void release(void);    //WM_DESTROY
	virtual void update(void);     //WM_TIMER
	virtual void render();  //WM_PAINT
	//�θ𿡼� virtual�� ������ �ڼ�Ŭ���������� virtual�� �Ƚᵵ ������ ���ʻ�, ���������� �����ش�
	//���, �������̵�, virtual�� ���� ����:http://blog.eairship.kr/175

	image* getBackBuffer(void) { return _backBuffer; }; //_backBuffer ����(get) �Լ�
	image* getBackBufferMapTool(void) { return _backBufferMapTool; };

	HDC getMemDC() { return _backBuffer->getMemDC(); };
	HDC getHDC() { return _hdc; };
	HDC getMemDCMapTool() { return _backBufferMapTool->getMemDC(); };
	//HDC getHDCMapTool() { return _hdcMapTool; };

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	//�浹���� �߰� �Լ��� (2018/03/28)
	//virtual void OnCollisionEnter(IR* toWhich);
	//virtual void OnTriggerEnter(IR* toWhich);

	//virtual void OnCollisionExit(IR* toWhich);
	//virtual void OnTriggerExit(IR* toWhich);



	gameNode();
	virtual ~gameNode(); //�Ҹ��ڸ� virtual�� �صθ� �Ҹ��ڿ��� �޸� ������ ��
};						 //gameNode* Ÿ�� �����Ϳ� �ڼ�Ŭ������ ������ ���
						 //�� �����͸� ���� �Ҹ��ڰ� ����Ǿ �˾Ƽ� �ڼ�Ŭ������ �Ҹ��ڰ� ����ȴ�