#pragma once
//image ����� stdafx�� �ƴ϶� gameNode���� ������
class image
{
public:
	enum IMAGE_LOAD_KIND //���� ������
	{
		LOAD_RESOURCE,     //���ҽ��κ��� �ε�
		LOAD_FILE,         //���Ϸκ���
		LOAD_EMPTY,        //Make Empty BMP file
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		//DWORD�� ȣȯ�� �ƿ� �Ұ����ϴ� 4Byte �� �� �̻� �� ���ϵ� �ƴ�
		//Long�� 32��Ʈ������ ȣȯ�� ������ 4Byte��
		//int�� 64��Ʈ���� ȣȯ�� ������ 4Byte��
		//�翬�ϰ����� ȣȯ�� �����ϴٸ� �Ҿ��ϱ� ������ ��ǻ�ʹ�
		//ȣȯ�� ���� �ʴ� DWORD�� �����Ѵ�

		DWORD		resID;				//�� ����ü�� �ν��Ͻ� �̸��� ���� DWORD?
		HDC			hMemDC;				//�� image Ŭ������ �׸�����
		HBITMAP		hBit;				//�̹��� ���� �ȿ� ��Ʈ�� ��ȭ���� ������
		HBITMAP		hOBit;				//�̹��� ���� �ȿ� ��Ʈ�� ��ȭ���� ������
		float x;						//BackDC�� ����ɶ� ����� x��ǥ
		float y;						//BackDC�� ����ɶ� ����� y��ǥ
		int			width;				//hBit�� ���α��� �� ����
		int			height;				//hBit�� ���α��� �� ����
		int			currentFrameX;		//������ �̹��� ��ȣ(����) (���� ���� ����)
		int			currentFrameY;		//������ �̹��� ��ȣ(����) (�࿡ ���� ����)
		int			maxFrameX;			//������ �ִ� ����(����)
		int			maxFrameY;			//������ �ִ� ����(����)
		int			frameWidth;			//������ �̹��� ���� ����ũ��
		int			frameHeight;		//������ �̹��� ���� ����ũ��
		BYTE		loadType;

		//�� ��Ʈ��Ʈ�� ������
		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		} 
		//*LPIMAGE_INFO�� �س��� ������ �̹����� ���� ���� �Ҵ��� ���ְ�
		//�ϱ� ����(���ٿ���)
	}IMAGE_INFO, *LPIMAGE_INFO; //*�� �پ LPIMAGE_INFO�� tagImageInfo ��Ʈ��Ʈ�� ����Ű�� �����Ͱ� ��

private:
	LPIMAGE_INFO    _imageInfo;		// �̹������� ����ü�� ������ tagImageinfo == *LPIMAGE_INFO
	CHAR*		    _fileName;		//�����̸� _fileName = new CHAR[len+1];�� ��Ÿ�ӿ� array ������ ������
	BOOL			_trans;			//Ư�� ���� ���� �� �������� ����
	COLORREF		_transColor;	//Ư�� �� ���۷���

	BLENDFUNCTION	_blendFunc;		//���ĺ��� �Լ� �󸶳� ���������� ������ ���� ���� ���� �� ���⿡ ��
	LPIMAGE_INFO	_blendImage;	//���ĺ��� �̹���, ���ĺ��� �ÿ� ���� �̹����� ȥ���� ���ο� memDC�� ������

public: 
	image();
	~image();

	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);
	//���� ��Ʈ�� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);
	//�Լ� ����� ��, 4��° 5��° �μ��� ���� �ʾƵ� �⺻�� FALSE�� ��
	//�ٸ� ���� ����ϰ� �������� ��������� ����־��ָ� ��
	
	//�̹��� DC�� �׸� ���� ��ǥ (x,y) �������� init�Լ� 
	//(�������� �̹��� DC�� ��ǥ�� �ٲ��� �ʰ� imageinfo ���� x,y ���� �ٲ��) %%���߿� setX,setY�� ���ص� ��
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	//������ ���� imageinfo (x,y) ��ǥ������
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);
	//������ ���� �⺻�� imageinfo (x,y) = (0,0)
	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	//�̹��� ����
	void release(void);

	//������ Ư�� �� ���� ����
	void setTransColor(BOOL trans, COLORREF transColor);

	void render(HDC hdc, int destX, int destY);
	//����               �ѷ��� ��X �ѷ��� ��Y   ������ ��X ������ ��Y  sourX,Y�κ��� ũ��(����, ����)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	//����               �ѷ��� ��X �ѷ��� ��Y  destX,Y�κ��� ���μ���       ������ ��X ������ ��Y  sourX,Y�κ��� ũ��(����, ����)
	void render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);
	//������ ���� �⺻�� (imageinfo currentFrame������ �������� �ʰ� �״�� ���)
	void frameRender(HDC hdc, int destX, int destY);
	//������ ���� imageinfo currentFrame ������
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	//������ ���� imageinfo x,y ������ destX,destY ��ü
	void frameRender(HDC hdc);
	//��� ����
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	//���� ����
	//alpha �� 1 byte = 8 bits => 2^8 = 256 => 0~255 ���� �� 0:����, 255:����������
	void alphaRender(HDC hdc, BYTE alpha); //�⺻ ���ĺ���
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha); //������ ����
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha); //������, ���� �� ��ǥ ����


	//DC(�׸���������)�� �������ִ� �Լ�
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; };
	//LPIMAGE_INFO    _imageInfo�� tagImageInfo�� �������̹Ƿ� ->�� ����ؾ���

	//========================================================
	// �̹��� ������ �����ϰ� ���� ����,������
	//========================================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (_imageInfo->maxFrameX < frameX) _imageInfo->maxFrameX = frameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (_imageInfo->maxFrameY < frameY) _imageInfo->maxFrameY = frameY;
	}

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

};