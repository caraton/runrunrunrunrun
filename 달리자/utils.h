#pragma once
//��ȣ������ ���ϱ� ���� cpp���Ͽ� stdafx.h ����

#define PI 3.141592654f
#define PI2 PI * 2


class gameNode;

//�������� ����� �̰��� �����̿���
namespace THETA_UTIL
{
	typedef struct ST_ImageAndRect //�ȼ� �浹�� ����� ��Ʈ����
	{
		image* _image;
		void* _node; //IR�� �����ϴ� ������Ʈ�� ����ų ������ (2018/03/28)
		//���ÿ��� �´� ������ �� ��ȯ�� �����Ͽ� ����Ұ�
		char* _type; //������ ������ ����ȯ�� �Ҷ� �о�� Ÿ�� �̸� ���� (2018/03/28)
		//ex) IR._type = "gameNode";
		RECT _rc;

		ST_ImageAndRect() 
		{
			_node = NULL;
			_type = NULL;
		};

		~ST_ImageAndRect()
		{
		};
	} IR;

	typedef struct tagFloatPOINT
	{
		float  x;
		float  y;

		//������ +,-�� �������̵��ؼ� 2x1 ������ component wise ���� ����
		tagFloatPOINT operator+(tagFloatPOINT fp)
		{
			tagFloatPOINT result;
			result.x = this->x + fp.x;
			result.y = this->y + fp.y;

			return result;
		}
		tagFloatPOINT operator-(tagFloatPOINT fp)
		{
			tagFloatPOINT result;
			result.x = this->x - fp.x;
			result.y = this->y - fp.y;

			return result;
		}
		tagFloatPOINT operator*(float fp) //������ overide�� ��Į�� �� ����
		{
			tagFloatPOINT result;
			result.x = this->x * fp;
			result.y = this->y * fp;

			return result;
		}
	} fPoint;

	float getDistance(float startX, float startY, float endX, float endY);

	float getAngle(float x1, float y1, float x2, float y2);

	bool pixelCol(ST_ImageAndRect* ir1, ST_ImageAndRect* ir2);
	bool pixelCol(ST_ImageAndRect* ir1,int framex1, int framey1, ST_ImageAndRect* ir2, int framex2, int framey2);

	void linearInterpol(const IN POINT* p1, OUT POINT* p2, float weight);
	fPoint linearInterpol(const IN fPoint* p1, const IN fPoint * p2, float weight);
}