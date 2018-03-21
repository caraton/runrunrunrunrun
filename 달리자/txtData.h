#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>

class txtData : public singletonBase<txtData>
{
public:
	HRESULT init();
	void release();

	//���̺�
	void txtSave(const char* saveFileName, vector<string> vStr); //vStr�� ������ ���Ͽ� ����ִ� �Լ�
	char* vectorArrayCombine(vector<string> vArray);			 //vStr�� ������ ������ ���ڿ��� ������ִ� �Լ�

	//�ε�
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);

	txtData();
	~txtData();
};