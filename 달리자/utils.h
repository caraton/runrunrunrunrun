#pragma once
//상호참조를 피하기 위해 cpp파일에 stdafx.h 참조

#define PI 3.141592654f
#define PI2 PI * 2


class gameNode;

//일주일의 고생은 이것을 위함이여찌
namespace THETA_UTIL
{
	typedef struct ST_ImageAndRect //픽셀 충돌에 사용할 스트럭쳐
	{
		image* _image;
		void* _node; //IR을 포함하는 오브젝트를 가리킬 포인터 (2018/03/28)
		//사용시에는 맞는 포인터 형 변환을 시행하여 사용할것
		char* _type; //위에서 포인터 형변환을 할때 읽어올 타입 이름 저장 (2018/03/28)
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

		//연산자 +,-를 오버라이드해서 2x1 벡터의 component wise 연산 구현
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
		tagFloatPOINT operator*(float fp) //연산자 overide로 스칼라 곱 구현
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