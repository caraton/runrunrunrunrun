#pragma once
//��ȣ������ ���ϱ� ���� cpp���Ͽ� stdafx.h ����

#define PI 3.141592654f
#define PI2 PI * 2


class gameNode;

//�������� ����� �̰��� �����̿���
namespace THETA_UTIL
{
	struct ST_ImageAndRect //�ȼ� �浹�� ����� ��Ʈ����
	{
		image* _image;
		RECT _rc;
	};

	float getDistance(float startX, float startY, float endX, float endY);

	float getAngle(float x1, float y1, float x2, float y2);

	bool pixelCol(ST_ImageAndRect* ir1, ST_ImageAndRect* ir2);
}