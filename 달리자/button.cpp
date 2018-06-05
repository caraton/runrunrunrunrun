#include "stdafx.h"
#include "button.h"

//콜백함수: 함수의 호출 실행 시점을 프로그래머가 아닌 시스템에서 결정하는 함수 API의 WndProc이 그 예
//콜백은 다른 코드(함수)의 인수로서 넘겨주는 실행 가능한 코드(함수)를 말한다. 콜백을 넘겨받는 코드(함수)는
//이 콜백을 필요에 따라 즉시 실행할 수도 있고, 아니면 나중에 실행할 수도 있다.
//콜백함수, 함수포인터 참조: https://stackoverflow.com/questions/2298242/callback-functions-in-c
//함수포인터 추가내용은 스트럭쳐,포인터, 함수포인터 프로젝트에서 확인하기

button::button()
{
}


button::~button()
{
}

//이미지매니저에서 이미지를 불러들일때 사용할 imageName, 버튼 중점 x좌표, 버튼 중점 y좌표 (RectMakeCenter사용)
//, POINT btnDownFramePoint, POINT btnUpFramePoint 둘은 버튼의 상태에 따라 프레임 렌더로 버튼 이미지 그림을 바꿀 때 필요한
//프레임 렌더 x,y 좌표값 저장, 버튼이 눌렸을 때 실행할 콜백함수 포인터 cbFunction
HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, POINT btnMouseoverFramePoint, CALLBACK_FUNCTION cbFunction)
{
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	//c++ 변수들 형변환을 위한 4가지 형변환 연산자들 : http://egloos.zum.com/sweeper/v/1907485

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
	//else //버튼 이미지가 프레임렌더 이용 이미지가 아닌 경우
	//{
		//_rc = RectMakeCenter(x, y, _image->getWidth(), _image->getHeight());
	//}

	return S_OK;
}

HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunction)
{
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	//c++ 변수들 형변환을 위한 4가지 형변환 연산자들 : http://egloos.zum.com/sweeper/v/1907485

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
	//else //버튼 이미지가 프레임렌더 이용 이미지가 아닌 경우
	//{
	//_rc = RectMakeCenter(x, y, _image->getWidth(), _image->getHeight());
	//}

	return S_OK;
}

HRESULT button::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION2 cbFunction2)
{
	_callbackFunction2 = static_cast<CALLBACK_FUNCTION2>(cbFunction2);
	//c++ 변수들 형변환을 위한 4가지 형변환 연산자들 : http://egloos.zum.com/sweeper/v/1907485

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
	//else //버튼 이미지가 프레임렌더 이용 이미지가 아닌 경우
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
	if (PtInRect(&_rc, _ptMouse)) //버튼 영역 안에 마우스가 들어왔는가?
	{
		if (KEYMANAGER ->isOnceKeyDown(VK_LBUTTON)) //VK_LBUTTON 마우스 왼쪽키
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction(); //콜백함수는 버튼이 눌린 순간이 아니라 눌리고 나서 때어진 순간에 실행
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
	if (PtInRect(&_rc, _ptMouse)) //버튼 영역 안에 마우스가 들어왔는가?
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) //VK_LBUTTON 마우스 왼쪽키
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			//string temp(_imageName);
			_callbackFunction2(_image); //콜백함수는 버튼이 눌린 순간이 아니라 눌리고 나서 때어진 순간에 실행
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

