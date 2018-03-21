#include "stdafx.h" //��ȣ���� ������ �ذ��ϱ� ����
#include "image.h"

#pragma comment(lib, "msimg32.lib") //���̺귯�� �߰� BitBlt ��� TransparentBlt �Լ� ��� ����

image::image()
	: _imageInfo(NULL),          //{} �ȿ��� ���� �ʱ�ȭ�ϴ� �Ͱ� ������ ȿ�� 
	_fileName(NULL),			 //image.h�� private ������ �ʱ�ȭ
	_trans(false),				 //��: p����(�ʱⰪ) �� p���� = �ʱⰪ; �� ����
	_transColor(RGB(0, 0, 0))
{
}

image::~image()
{
}

//�� ��Ʈ�� �ʱ�ȭ (BackDC�� ���� ����� �ʱ�ȭ�� ���)
HRESULT image::init(int width, int height)
{
	//Ȥ�ó� �̹��� ������ �� ������ ����
	if (_imageInfo != NULL)
	{
		release();
	}

	HDC hdc = GetDC(_hWnd); 

	_imageInfo = new IMAGE_INFO; //_imageInfo�� tagImageInfo(== IMAGE_INFO)�� ����Ű�� ������(LPIMAGE_INFO)
	//=> �����Ҵ��ؾ���
	_imageInfo->loadType = LOAD_EMPTY; //�� ��Ʈ�� �ʱ�ȭ
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	//SelectObject�� hMemDC�� hBit�� ����ְ� ���ϰ����� ������ �������� hObit�� ����
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ĺ��� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;
	//

	if (_imageInfo->hBit == NULL) //�ʱ�ȭ�� �ȵǾ�����
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc); //HDC hdc = GetDC(_hWnd); �� ������ ���� �ݵ�� �������־�� �Ѵ�.

	return S_OK;
}

//���� ��Ʈ�� �ʱ�ȭ
HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//�����̸��� ������ ���� return
	if (fileName == NULL)
	{
		return E_FAIL;
	}

	//Ȥ�ó� �̹��� ������ �� ������ ����
	if (_imageInfo != NULL)
	{
		release();
	}

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO; //_imageInfo�� tagImageInfo(== IMAGE_INFO)�� ����Ű�� ������(LPIMAGE_INFO)
								 //=> �����Ҵ��ؾ���
	_imageInfo->loadType = LOAD_FILE; //���� ��Ʈ�� �ʱ�ȭ
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	//�̸��� const char * fileName �� ��Ʈ�� �̹��� ���� �ҷ�����
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	//SelectObject�� hMemDC�� hBit�� ����ְ� ���ϰ����� ������ �������� hObit�� ����
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� ���̸� �˾ƿ��� (���ϰ��)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1]; //CHAR * _fileName�� CHAR�� ������ -> �����Ҵ� //NULL �� �� ������ ��ĭ �ʿ� (+1)
	strcpy_s(_fileName, len + 1, fileName); //_fileName�� �� �Լ� ��ǲ fileName�� ����
	
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;
	//

	//�ʱ�ȭ ����
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc); //HDC hdc = GetDC(_hWnd); �� ������ ���� �ݵ�� �������־�� �Ѵ�.

	return S_OK;
}

//���� ��Ʈ�� �ʱ�ȭ + imageinfo (x,y) �� ����
HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//�����̸� ������ ����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ ���� �ִٸ� �������ش�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� ���̸� �˾ƿ´�(���ϰ��)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;
	//

	//�ʱ�ȭ�� �ȵǾ���
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//������ ���� imageinfo (x,y) ��ǥ������
HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�����̸� ������ ����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ ���� �ִٸ� �������ش�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	//_imageInfo->x = x - (width / 2); //???? �̴���ϸ� �ȵ�
	//_imageInfo->y = y - (height / 2); //????
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->x = x - (_imageInfo->frameWidth / 2);
	_imageInfo->y = y - (_imageInfo->frameHeight / 2);
	_imageInfo->maxFrameX = frameX - 1; //0�������Ӻ��� �����ϹǷ� -1
	_imageInfo->maxFrameY = frameY - 1;

	//���� ���̸� �˾ƿ´�(���ϰ��)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;
	//

	//�ʱ�ȭ�� �ȵǾ���
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//������ ���� �⺻�� imageinfo (x,y) = (0,0)
HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�����̸� ������ ����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ ���� �ִٸ� �������ش�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//���� ���̸� �˾ƿ´�(���ϰ��)
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;
	//

	//�ʱ�ȭ�� �ȵǾ���
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release(void) //�̹��� ���� �Լ�
{
	//�̹��� ������ �ִٸ�
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//_imageInfo�� _fileName �Ѵ� ������ ����
		SAFE_DELETE(_imageInfo); 
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans) //true�� ����������� ������ Ư�� ���� ����
	{
		GdiTransparentBlt(hdc,			//���縦 ���� ������ DC 
			destX,						//�Ǻ��� ������ ������� ��ǥX (left)
			destY,						//�Ǻ��� ������ ������� ��ǥY (top)
			_imageInfo->width,			//����� ũ�� (������ǥX���� ����)
			_imageInfo->height,			//����� ũ�� (������ǥY���� ����)
			_imageInfo->hMemDC,			//������ DC (�̹������� hMemDC)
			0, 0,						//���� ������ ��ǥ
			_imageInfo->width,			//width
			_imageInfo->height,			//height
			_transColor);				//���翡�� ������ ����
	}
	else
	{
		//������ ������ �����Ƿ� ��ü ��� ����
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,		//����� ������ DC		== backDC
			destX,					//����� ��ǥ X(left		== backDC�� ������ ��ǥ
			destY,					//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			sourWidth,				//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			sourHeight,				//����� ũ�� height		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,		//������ DC				== �̹���DC
			sourX, sourY,			//������ X, Y			== �̹���DC�� ��ǥ
			sourWidth,				//������ width			== �̹���DC�� ����ũ��
			sourHeight,				//������ height			== �̹���DC�� ����ũ��
			_transColor);			//���翡�� ������ ����	== �̹���DC���� �ȼ���
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}
//����                     �ѷ��� ��X �ѷ��� ��Y  destX,Y�κ��� ���μ���        ������ ��X ������ ��Y  sourX,Y�κ��� ũ��(����, ����)
void image::render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,		//����� ������ DC		== backDC
			destX,					//����� ��ǥ X(left	== backDC�� ������ ��ǥ
			destY,					//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			destWidth,				//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			destHeight,				//����� ũ�� height	== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,		//������ DC				== �̹���DC
			sourX, sourY,			//������ X, Y			== �̹���DC�� ��ǥ
			sourWidth,				//������ width			== �̹���DC�� ����ũ��
			sourHeight,				//������ height			== �̹���DC�� ����ũ��
			_transColor);			//���翡�� ������ ����	== �̹���DC���� �ȼ���
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		BitBlt(hdc, destX, destY,
			destWidth, destHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

//������ ���� �⺻�� (imageinfo currentFrame������ �������� �ʰ� �״�� ���)
void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,										//����� ������ DC		== backDC
			destX,													//����� ��ǥ X(left	== backDC�� ������ ��ǥ
			destY,													//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			_imageInfo->frameWidth,									//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->frameHeight,								//����� ũ�� height	== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,										//������ DC				== �̹���DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//������ X			    == �̹���DC�� ��ǥ
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//������ Y				== �̹���DC�� ��ǥ
			_imageInfo->frameWidth,									//������ width			== �̹���DC�� ����ũ��
			_imageInfo->frameHeight,								//������ height			== �̹���DC�� ����ũ��
			_transColor);											//���翡�� ������ ����	== �̹���DC���� �ȼ���
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY *_imageInfo->frameHeight, SRCCOPY);
	}
}
//������ ���� imageinfo currentFrame ������
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc,										//����� ������ DC		== backDC
			destX,													//����� ��ǥ X(left	== backDC�� ������ ��ǥ
			destY,													//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			_imageInfo->frameWidth,									//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->frameHeight,								//����� ũ�� height	== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,										//������ DC				== �̹���DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//������ X				== �̹���DC�� ��ǥ
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//������ Y				== �̹���DC�� ��ǥ
			_imageInfo->frameWidth,									//������ width			== �̹���DC�� ����ũ��
			_imageInfo->frameHeight,								//������ height			== �̹���DC�� ����ũ��
			_transColor);											//���翡�� ������ ����	== �̹���DC���� �ȼ���
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY *_imageInfo->frameHeight, SRCCOPY);
	}
}
//������ ���� imageinfo x,y ������ destX,destY ��ü
void image::frameRender(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,										//����� ������ DC		== backDC
			_imageInfo->x,											//����� ��ǥ X(left		== backDC�� ������ ��ǥ
			_imageInfo->y,											//����� ��ǥ Y(top		== backDC�� ������ ��ǥ
			_imageInfo->frameWidth,									//����� ũ�� width		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->frameHeight,								//����� ũ�� height		== backDC�� ������ ��ǥ�κ��� ����ũ��
			_imageInfo->hMemDC,										//������ DC				== �̹���DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//������ X			== �̹���DC�� ��ǥ
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//������ Y			== �̹���DC�� ��ǥ
			_imageInfo->frameWidth,									//������ width			== �̹���DC�� ����ũ��
			_imageInfo->frameHeight,								//������ height			== �̹���DC�� ����ũ��
			_transColor);											//���翡�� ������ ����	== �̹���DC���� �ȼ���
	}
	else
	{
		//����ۿ� �ִ� ���� ������ ��Ӻ��� ���ش�
		BitBlt(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY *_imageInfo->frameHeight, SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//offSetX = cameraX��
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width); 
	//-2 mod 7�� 5 mod 7�� ��ġ
	//�ʺ� 10�� offset�� -2�� 8�� �������ִ� ����
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;

	//�׷��ִ� ������ ����ش�
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//for ���߷����̹Ƿ� ���� �ȿ� �ִ� x������ ����� ������ ������ ��
	//(����� y < drawAreaH�� x < drawAreaW�� ���� �����ǹǷ� ���������� �������� �ʴ´�)
	//(��: ����� apiâ ũ��� ���� ���, offSet��ŭ �߸� ��� 1��, ���ο� ��� 1��)
	//�� ����� �׸��� y������ ����
	//Y�����
	for (int y = 0; y < drawAreaH; y += sourHeight) //
	{
		rcSour.top = (y + offSetY) % _imageInfo->height; //offSet����ŭ �̹����� �߶��ֱ� ���ؼ� 
		rcSour.bottom = _imageInfo->height;				 //top�� bottom �� ����

		sourHeight = rcSour.bottom - rcSour.top; 
		//rcSour.top = rcSour.bottom(==_imageInfo->height) - sourHeight�̹Ƿ�
		//�ι�° �������� y���� sourHeight�� �������鼭 rcSour.top = rcSour.bottom % _imageInfo->height (==rcSour.bottom)
		//�� rcSour.top�� ���� 0�� �ȴ�. => �ι�° �������� sourHeight == _imageInfo->height�� �ȴ�.
		//=> �ι�° �������ʹ� sourHeight == _imageInfo->height �̹Ƿ� y + sourHeight > drawAreaH �� �ƴ���
		//������ ��� 1���� �׷�����

		//�׷����� ������ ���̺��� Y���� ũ��
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�ѷ��ִ� ����
		rcDest.top = y + drawAreaY; //y=0 �϶� ó�� ȭ�� (drawAreaY == 0) �׸���
									//�� �������ʹ� y���� sourHeight��ŭ �������鼭 �׷���
		rcDest.bottom = rcDest.top + sourHeight;

		//X ��
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left,
				rcDest.top,
				rcSour.left,
				rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha; //�����߼� ����ü�� alpha �� �Է�

	if (_trans)
	{	//��ǲ���� ������ hdc�� ���ӳ���� �����DC
		//�����DC�� ���� �����̹��� DC�� �����ϰ� (����� ���� �̹����� �־��ֱ� ������)
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, (int)_imageInfo->x, (int)_imageInfo->y, SRCCOPY);

		//�̹���DC�� ����Ÿ���� ����鼭 �����̹��� DC�� ���� 
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//���ĺ���� ���� DC�� �׸��� ���� �ϴ� �׸��� RGB���� ������ ������
		//���κ��� BitBlt���� ���� ����� �Ȱ��� ������� ���� ��ġ�Ƿ� rgb���� �״�� -> ����� ���������� ����
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha) 
{
	_blendFunc.SourceConstantAlpha = alpha; //�����߼� ����ü�� alpha �� �Է�

	if (_trans)
	{	//��ǲ���� ������ hdc�� ���ӳ���� �����DC
		//�����DC�� ���� �����̹��� DC�� �����ϰ� (����� ���� �̹����� �־��ֱ� ������)
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, destX, destY, SRCCOPY);

		//�̹���DC�� ����Ÿ���� ����鼭 �����̹��� DC�� ���� 
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//���ĺ���� ���� DC�� �׸��� ���� �ϴ� �׸��� RGB���� ������ ������
		//���κ��� BitBlt���� ���� ����� �Ȱ��� ������� ���� ��ġ�Ƿ� rgb���� �״�� -> ����� ���������� ����
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha; //�����߼� ����ü�� alpha �� �Է�

	if (_trans)
	{	//��ǲ���� ������ hdc�� ���ӳ���� �����DC
		//�����DC�� ���� �����̹��� DC�� �����ϰ� (����� ���� �̹����� �־��ֱ� ������)
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, destX, destY, SRCCOPY);

		//�̹���DC�� ����Ÿ���� ����鼭 �����̹��� DC�� ���� 
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		//���ĺ���� ���� DC�� �׸��� ���� �ϴ� �׸��� RGB���� ������ ������
		//���κ��� BitBlt���� ���� ����� �Ȱ��� ������� ���� ��ġ�Ƿ� rgb���� �״�� -> ����� ���������� ����
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
}
