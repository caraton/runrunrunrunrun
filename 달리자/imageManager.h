#pragma once
//��ȣ���� ������ ���ϱ� ���� stdafx.h�� imageManager.cpp ���� include�Ѵ�.
#include "singletonBase.h"
#include "image.h"
//#include <string>
#include <map> //STL map container �����

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList; //�Ź� template Ŭ���� map�� key�� value�� Ÿ���� �����ֱ�
											  //�������Ƿ� typedef�� �̿�
	typedef map<string, image*>::iterator mapImageIter; //���� ����
private:
	mapImageList _mImageList; //mapImageList�� key Ÿ���� string�̰� valueŸ���� image*�� map

public:
	HRESULT init(); //����� return S_OK; �ܿ� �ƹ� ���뵵 ����
	void release(); //����� �ƹ� ���� ����

	//�� ��Ʈ�� �̹���
	image* addImage(string strKey, int width, int height);
	image* addImageMapTool(string strKey, int width, int height);
	
	//���� �̹���
	image* addImage(string strKey, const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE , BOOL reset = FALSE);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);

	image* newAddImage(string strKey, const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL reset = FALSE);

	//������ �̹���
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);

	image* findImage(string strKey); //_mImageList(map)���� strKey�� key������ ������ image*�� �ִ��� �˻�

	BOOL deleteImage(string strKey); //_mImageList(map)���� strKey�� key������ ������ image* ����

	BOOL deleteAll(void); //_mImageList(map)���� ��� �� ����

	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	imageManager();
	~imageManager();
};