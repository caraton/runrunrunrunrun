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

	void txtSaveExt(const char* saveFileName, vector<string> vStr); //vStr�� ������ ���Ͽ� ����ִ� �Լ� ũ�� ����
	char* vectorArrayCombineExt(vector<string> vArray);			 //vStr�� ������ ������ ���ڿ��� ������ִ� �Լ� ũ�� ����

	//�ε�
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);

	txtData();
	~txtData();
};