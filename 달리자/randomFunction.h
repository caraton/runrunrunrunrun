//#pragma once �� ���⿡�� ��ó���⿡ �ѹ��� ������� �˷��� �ʿ䰡 ���°�? ���������� ����ؼ�?

#include "singletonBase.h"
#include <time.h>
#include <stdlib.h> //srand�� rand�� ���� ���
#include <sysinfoapi.h> //GetTickCount�� ���� ���

//�����Լ�

class randomFunction : public singletonBase<randomFunction> //template T�κп� randomFunction�� ����
{															// singleton�� T*���� randomFunciont*�� �ȴ�.
public:
	randomFunction(void) //randomFunction Ŭ������ ������
	{
		srand(GetTickCount());  //GetTickCount�� 32��Ʈ 49.7���� ������ 0���� ���ƿ� GetTickCount64 (vista ���� os) ��
	}							//2135�� ��� ����

	~randomFunction(void) {};

	//0 ~ num-1 ���̿� ���� �����ϰ� �޾ƿ´�
	inline int getInt(int num)
	{
		return rand() % num;
	}
	//���� ������ ������ ���� �̾Ƴ��� �Լ�(ex 50, 100) 50���� 100����
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum; //50~100 ������ ��� ���� ����
	}
};