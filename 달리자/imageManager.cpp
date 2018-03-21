#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
}

//�� ��Ʈ�� �̹���
image * imageManager::addImage(string strKey, int width, int height)
{
	image* img = findImage(strKey); //���� strKey�� key���� ���� image�� �����ϴ��� Ȯ�� (_mImageList) ����

	if (img) //���� img�� null�� �ƴϸ� == _mImageList�� �̹� �����ϸ�
	{
		return img;
	}

	//img �� null�̸�
	img = new image;

	if (FAILED(img->init(width, height))) //img �ʱ�ȭ
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//map���� insert�Ҷ� 1)make_pair(first, second) <--- �˾Ƽ� ���� ã�Ƽ� �߰�
	//					 2)pair(�ڷ���, �ڷ���)<first, second> <-- �� �����ϰ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//���� �̹��� 1
image * imageManager::addImage(string strKey, const char * fileName, int width, int height, BOOL trans, COLORREF transColor, BOOL reset)
{
	image* img = findImage(strKey);

	if (img) //���� img�� null�� �ƴϸ� == _mImageList�� �̹� �����ϸ�
	{
		if (reset)
		{
			deleteImage(strKey);
		}
		else
		{
			return img;
		}
	}


	//img �� null�̸�
	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor))) //img �ʱ�ȭ
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//map���� insert�Ҷ� 1)make_pair(first, second) <--- �˾Ƽ� ���� ã�Ƽ� �߰�
	//					 2)pair(�ڷ���, �ڷ���)<first, second> <-- �� �����ϰ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//���� �̹��� 2
image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	if (img) //���� img�� null�� �ƴϸ� == _mImageList�� �̹� �����ϸ�
	{
		return img;
	}

	//img �� null�̸�
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor))) //img �ʱ�ȭ
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//map���� insert�Ҷ� 1)make_pair(first, second) <--- �˾Ƽ� ���� ã�Ƽ� �߰�
	//					 2)pair(�ڷ���, �ڷ���)<first, second> <-- �� �����ϰ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::newAddImage(string strKey, const char * fileName, int width, int height, BOOL trans, COLORREF transColor, BOOL reset)
{
	image* img = findImage(strKey);

	if (img) //���� img�� null�� �ƴϸ� == _mImageList�� �̹� �����ϸ�
	{
		if (reset)
		{
			deleteImage(strKey);
		}
		else
		{
			return img;
		}
	}


	//img �� null�̸�
	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor))) //img �ʱ�ȭ
	{
		SAFE_DELETE(img);

		return NULL;
	}

	COLORREF color;
	int r;
	int g;
	int b;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			color = GetPixel(img->getMemDC(), i, j);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r > 230 && g < 25 && b > 230)
			{
				SetPixel(img->getMemDC(), i, j, RGB(255, 0, 255));
			}
		}
	}

	//map���� insert�Ҷ� 1)make_pair(first, second) <--- �˾Ƽ� ���� ã�Ƽ� �߰�
	//					 2)pair(�ڷ���, �ڷ���)<first, second> <-- �� �����ϰ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//������ �̹��� 1
image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	if (img) //���� img�� null�� �ƴϸ� == _mImageList�� �̹� �����ϸ�
	{
		return img;
	}

	//img �� null�̸�
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor))) //img �ʱ�ȭ
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//map���� insert�Ҷ� 1)make_pair(first, second) <--- �˾Ƽ� ���� ã�Ƽ� �߰�
	//					 2)pair(�ڷ���, �ڷ���)<first, second> <-- �� �����ϰ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//������ �̹��� 2
image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	if (img) //���� img�� null�� �ƴϸ� == _mImageList�� �̹� �����ϸ�
	{
		return img;
	}

	//img �� null�̸�
	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor))) //img �ʱ�ȭ
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//map���� insert�Ҷ� 1)make_pair(first, second) <--- �˾Ƽ� ���� ã�Ƽ� �߰�
	//					 2)pair(�ڷ���, �ڷ���)<first, second> <-- �� �����ϰ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::findImage(string strKey)
{
	mapImageIter iter = _mImageList.find(strKey); //find �޼ҵ�� key������ map�� ��ȸ�ϴ� �Լ�

	//key�� ���� ���� �ƴ϶�� == Ű ���� ã������ (end()�� �׻� ������ĭ ������ ��ĭ�� ����Ŵ)
	if (iter != _mImageList.end())
	{
		return iter->second; //map�� iterator���� ->first�� ->second�� key�� value���� ���� �����ϴ�
	}

	return NULL;
}

BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter iter = _mImageList.find(strKey);

	if (iter != _mImageList.end())
	{
		iter->second->release(); //imageŬ������ release�Լ� ����
		SAFE_DELETE(iter->second);
		_mImageList.erase(iter);

		return true;
	}

	return false;
}

BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (/*���� iter�� �ʱ�ȭ��*/; iter != _mImageList.end(); /*for loop�ȿ��� iter�� ������ ������ ����*/)
	{
		if (iter->second != NULL)
		{
			iter->second->release(); //���� ����ó�� �̺κ��� �־���� �ϴ°�?
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter); 
			//iter �κ��� �����ϹǷ� iter++�� �����ʴ´�.
			//��ſ� erase(iter)�� return��(������ ���� �ٷ� ����)�� iter�� �Ҵ�
			//map::erase�� ��ǲ iterator �ּҰ� ��ġ�� �����ϰ� ���� �ּҸ� ���� iterator�� return�Ѵ�

			//Q: container ������ �����Ͱ� ������Ƿ� iterator�� ���̴� �� �ƴѰ�?
			//A: A nice property of a C++ Standard Template Library (STL) map, multimap, set or multiset is that you can insert or erase elements without invalidating existing iterators.
			//����: http://llg.cubic.org/docs/stlerase.html
		}
		else
		{
			++iter; 
		}
	}

	_mImageList.clear();

	return true;
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img)
	{
		img->render(hdc, destX, destY);
	}
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img)
	{
		img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
	}
}

imageManager::imageManager()
{
}

imageManager::~imageManager()
{
}
