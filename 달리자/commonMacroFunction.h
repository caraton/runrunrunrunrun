#pragma once

inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL); // hdc ��ȭ�� ���� (x1,y1)�� ���������� ���Ѵ�
	LineTo(hdc, x2, y2); //������ ���������� (x2,y2)�� ���� �׾��ش�
}


inline RECT RectMake(int x, int y, int width, int height) //������, �ʺ�, ���̸� �޾Ƽ� ����ü(Ŭ����) RECT�� �������� �Լ�
{
	RECT rc = { x, y, x + width, y + height };


	//RECT rc;
	//rc.left = x;
	//rc.top = y;
	//rc.right = x + width;
	//rc.bottom = y + height; �� ���� �ϳ��ϳ� �����ʰ� ���� ���� ������ �ص� �ȴ�.

	return rc;
}

//RECT rc�� ���ǵ� �Ŀ� Rectangle�� ���鶧���� rc.left������ ������ �ҷ��鿩 ����ϸ� �ȴ�.

// ������ǥ, �ʺ�, ���̸� �ָ� RECT�� �������� �Լ�
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

//�簢���� hdc ��ȭ���� �׸��� �Լ�
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}


inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//���� hdc ��ȭ���� �׸��� �Լ� 
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}