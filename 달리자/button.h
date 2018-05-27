#pragma once
#include "gameNode.h"

//�ݹ��Լ�: �Լ��� ȣ�� ���� ������ ���α׷��Ӱ� �ƴ� �ý��ۿ��� �����ϴ� �Լ� API�� WndProc�� �� ��
//�ݹ��� �ٸ� �ڵ�(�Լ�)�� �μ��μ� �Ѱ��ִ� ���� ������ �ڵ�(�Լ�)�� ���Ѵ�. �ݹ��� �Ѱܹ޴� �ڵ�(�Լ�)��
//�� �ݹ��� �ʿ信 ���� ��� ������ ���� �ְ�, �ƴϸ� ���߿� ������ ���� �ִ�.
//�ݹ��Լ�, �Լ������� ����: https://stackoverflow.com/questions/2298242/callback-functions-in-c
//�Լ������� �߰������� ��Ʈ����,������, �Լ������� ������Ʈ���� Ȯ���ϱ�

//�Լ������͸� �̿��� �ݹ��Լ��� �����Ѵ�.
typedef void(*CALLBACK_FUNCTION)(void);
//void func (void) �� �Լ��� ������ void (*) (void)�� typedef�� �̿��� CALLBACK_FUNCTION���� ����

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL, //��ư�� �ȴ��� ��
	BUTTONDIRECTION_MOUSEOVER, //��ư�� �ȴ������� ���콺�� ��ư ���� ���� ��
	BUTTONDIRECTION_UP,   //��ư�� ���ȴٰ� �ö� ��
	BUTTONDIRECTION_DOWN  //��ư�� ������ ��
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction; //��ư�� ���¸� �˷��� enum BUTTONDIRECTION �� �ν��Ͻ�

	const char* _imageName; //��ư �̹��� �̸�
	image* _image; //�̹��� �Ŵ����� findImage(_imageName)���� ���Ϲ��� �̹��� ������ ����
	RECT _rc; //��ư �νĺκ� ������ ���� ��Ʈ
	float _x, _y; //��ư�� ���� x,y ��ǥ���� init���� �޾� ����

	POINT _btnDownFramePoint; //��ư�� ���� �� �����ӷ������� ���° �׸��� �������� �˷��� ���� ����
	POINT _btnUpFramePoint; //��ư�� ������ ���� �� �����ӷ������� ���° �׸��� �������� �˷��� ���� ����
	POINT _btnMouseoverFramePoint; //���콺���� ������ �� �����ӷ������� ���° �׸��� �������� �˷��� ���� ����

	CALLBACK_FUNCTION _callbackFunction; //��ư�� ������ ������ �Լ��� �����͸� ���� ����

public:
	HRESULT init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, POINT btnMouseoverFramePoint, CALLBACK_FUNCTION cbFunction);
	//�̹����Ŵ������� �̹����� �ҷ����϶� ����� imageName, ��ư ���� x��ǥ, ��ư ���� y��ǥ (RectMakeCenter���)
	//, POINT btnDownFramePoint, POINT btnUpFramePoint ���� ��ư�� ���¿� ���� ������ ������ ��ư �̹��� �׸��� �ٲ� �� �ʿ���
	//������ ���� x,y ��ǥ�� ����, ��ư�� ������ �� ������ �ݹ��Լ� ������ cbFunction
	
	void release();
	void update();
	void render(HDC hdc); //���������� �� ��ư Ŭ������ ����� �� �ֵ��� render�Լ� ����(HDC�� �μ��� �޵���)

	button();
	~button();
};

