#include "stdafx.h" //��ȣ������ ���ϱ� ���� cpp���Ͽ� stdafx.h ����
#include "utils.h"
#include "gameNode.h"


//���ӽ����̽��� �����صθ� �������� ���ϰ� �����ִ�
namespace THETA_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf((x * x) + (y * y));

		float angle = acosf(x / distance);

		//Y���� ������ �ʿ��ϴ�
		if (y2 > y1)
		{
			angle = PI * 2 - angle;
			if (angle >= PI * 2) angle -= PI * 2;
		}

		return angle;
	}
	bool pixelCol(ST_ImageAndRect * ir1, ST_ImageAndRect * ir2)
	{
		RECT tempRC; //�浹��
		if (!IntersectRect(&tempRC, &(ir1->_rc), &(ir2->_rc))) //�� �̹����� ���� ��Ʈ ���� �浹�� ���� ���
		{
			return false;
		}
		
		//for ���� �ȿ��� ���� ������
		COLORREF color1;
		COLORREF color2;
		int r1;
		int g1;
		int b1;
		int r2;
		int g2;
		int b2;

		//�⺻ ���̵��
		//��Ʈ�浹�� �浹�� ������ ���ͼ�
		//���� �������� �� �׸��� ���Ͽ� ��� �ȼ����� �浹üũ�� �Ѵ�
		//�� �׸� ��� ����Ÿ�� �ƴ� ������ �մ� �ȼ��� �ϳ��� �����Ѵٸ� true
		for (int i = tempRC.left; i < tempRC.right; i++)
		{
			for (int j = tempRC.top; j < tempRC.bottom; j++)
			{
				color1 = GetPixel(ir1->_image->getMemDC(), i - ir1->_rc.left, j - ir1->_rc.top);
				//_image���� DC���� �׸��� 0,0���� �׷��������Ƿ� (i - ir1->_rc.left, j - ir1->_rc.top) �� �´� ��ǥ 
				color2 = GetPixel(ir2->_image->getMemDC(), i - ir2->_rc.left, j - ir2->_rc.top);

				r1 = GetRValue(color1);
				g1 = GetGValue(color1);
				b1 = GetBValue(color1);

				r2 = GetRValue(color2);
				g2 = GetGValue(color2);
				b2 = GetBValue(color2);

				if (!(r1 == 255 && g1 == 0 && b1 == 255) && !(r2 == 255 && g2 == 0 && b2 == 255))
				{	//ir1, ir2 �� �̹������� (i,j) ������ �� �� ����Ÿ ���� �ƴ� ���  
					return true;
				}
			}
		}

		return false;
	}
}