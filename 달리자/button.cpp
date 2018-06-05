#include "stdafx.h"
#include "button.h"

//�ݹ��Լ�: �Լ��� ȣ�� ���� ������ ���α׷��Ӱ� �ƴ� �ý��ۿ��� �����ϴ� �Լ� API�� WndProc�� �� ��
//�ݹ��� �ٸ� �ڵ�(�Լ�)�� �μ��μ� �Ѱ��ִ� ���� ������ �ڵ�(�Լ�)�� ���Ѵ�. �ݹ��� �Ѱܹ޴� �ڵ�(�Լ�)��
//�� �ݹ��� �ʿ信 ���� ��� ������ ���� �ְ�, �ƴϸ� ���߿� ������ ���� �ִ�.
//�ݹ��Լ�, �Լ������� ����: https://stackoverflow.com/questions/2298242/callback-functions-in-c
//�Լ������� �߰������� ��Ʈ����,������, �Լ������� ������Ʈ���� Ȯ���ϱ�

button::button()
{
}


button::~button()
{
}

//�̹����Ŵ������� �̹����� �ҷ����϶� ����� imageName, ��ư ���� x��ǥ, ��ư ���� y��ǥ (RectMakeCenter���)
//, POINT btnDownFramePoint, POINT btnUpFramePoint ���� ��ư�� ���¿� ���� ������ ������ ��ư �̹��� �׸��� �ٲ� �� �ʿ���
//������ ���� x,y ��ǥ�� ����, ��ư�� ������ �� ������ �ݹ��Լ� ������ cbFunction
HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, POINT btnMouseoverFramePoint, CALLBACK_FUNCTION cbFunction)
{
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	//c++ ������ ����ȯ�� ���� 4���� ����ȯ �����ڵ� : http://egloos.zum.com/sweeper/v/1907485

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;
	_btnMouseoverFramePoint = btnMouseoverFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	//if (_image->getFrameHeight() != 0)
	//{
		_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	//}
	//else //��ư �̹����� �����ӷ��� �̿� �̹����� �ƴ� ���
	//{
		//_rc = RectMakeCenter(x, y, _image->getWidth(), _image->getHeight());
	//}

	return S_OK;
}

HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunction)
{
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	//c++ ������ ����ȯ�� ���� 4���� ����ȯ �����ڵ� : http://egloos.zum.com/sweeper/v/1907485

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;
	_btnMouseoverFramePoint = btnUpFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	//if (_image->getFrameHeight() != 0)
	//{
	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	//}
	//else //��ư �̹����� �����ӷ��� �̿� �̹����� �ƴ� ���
	//{
	//_rc = RectMakeCenter(x, y, _image->getWidth(), _image->getHeight());
	//}

	return S_OK;
}

HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION2 cbFunction2)
{
	_callbackFunction2 = static_cast<CALLBACK_FUNCTION2>(cbFunction2);
	//c++ ������ ����ȯ�� ���� 4���� ����ȯ �����ڵ� : http://egloos.zum.com/sweeper/v/1907485

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;
	_btnMouseoverFramePoint = btnUpFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	//if (_image->getFrameHeight() != 0)
	//{
	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	//}
	//else //��ư �̹����� �����ӷ��� �̿� �̹����� �ƴ� ���
	//{
	//_rc = RectMakeCenter(x, y, _image->getWidth(), _image->getHeight());
	//}

	return S_OK;
}

void button::release()
{
}

void button::update()
{
	if (PtInRect(&_rc, _ptMouse)) //��ư ���� �ȿ� ���콺�� ���Դ°�?
	{
		if (KEYMANAGER ->isOnceKeyDown(VK_LBUTTON)) //VK_LBUTTON ���콺 ����Ű
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction(); //�ݹ��Լ��� ��ư�� ���� ������ �ƴ϶� ������ ���� ������ ������ ����
		}
		else if (_direction != BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_MOUSEOVER;
		}
	}
	else
	{
		_direction = BUTTONDIRECTION_NULL;
	}
}

void button::update2()
{
	if (PtInRect(&_rc, _ptMouse)) //��ư ���� �ȿ� ���콺�� ���Դ°�?
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) //VK_LBUTTON ���콺 ����Ű
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			//string temp(_imageName);
			_callbackFunction2(_image); //�ݹ��Լ��� ��ư�� ���� ������ �ƴ϶� ������ ���� ������ ������ ����
		}
		else if (_direction != BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_MOUSEOVER;
		}
	}
	else
	{
		_direction = BUTTONDIRECTION_NULL;
	}
}

void button::render(HDC hdc)
{
	switch (_direction)
	{
	case BUTTONDIRECTION_NULL:
	{
		//if (_image->getFrameHeight() != 0)
		//{
			_image->frameRender(hdc, _rc.left, _rc.top, _btnUpFramePoint.x, _btnUpFramePoint.y);
		//}
		//else
		//{
		//	_image->render(hdc, _rc.left, _rc.top);
		//}

		break;
	}
	case BUTTONDIRECTION_MOUSEOVER:
	{
		//if (_image->getFrameHeight() != 0)
		//{
			_image->frameRender(hdc, _rc.left, _rc.top, _btnMouseoverFramePoint.x, _btnMouseoverFramePoint.y);
		//}
		//else
		//{
		//	_image->render(hdc, _rc.left, _rc.top);
		//}

		break;
	}
	case BUTTONDIRECTION_UP:
	{
		//if (_image->getFrameHeight() != 0)
		//{
			_image->frameRender(hdc, _rc.left, _rc.top, _btnMouseoverFramePoint.x, _btnMouseoverFramePoint.y);
		//}
		//else
		//{
		//	_image->render(hdc, _rc.left, _rc.top);
		//}

		break;
	}
	case BUTTONDIRECTION_DOWN:
	{
		//if (_image->getFrameHeight() != 0)
		//{
			_image->frameRender(hdc, _rc.left, _rc.top, _btnDownFramePoint.x, _btnDownFramePoint.y);
		//}
		//else
		//{
		//	_image->render(hdc, _rc.left, _rc.top);
		//}

		break;
	}
	}
}

