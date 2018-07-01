#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")


class txtData : public singletonBase<txtData>
{
public:
	HRESULT init();
	void release();

	//���̺�
	void txtSave(const char* saveFileName, vector<string> vStr); //vStr�� ������ ���Ͽ� ����ִ� �Լ�
	char* vectorArrayCombine(vector<string> vArray);			 //vStr�� ������ ������ ���ڿ��� ������ִ� �Լ�

	void txtSaveExt(const char* saveFileName, vector<string> vStr, int size); //vStr�� ������ ���Ͽ� ����ִ� �Լ� ũ�� ����
	char* vectorArrayCombineExt(vector<string> vArray, int size);			 //vStr�� ������ ������ ���ڿ��� ������ִ� �Լ� ũ�� ����

	//�ε�
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);
	vector<string> txtLoadExt(const char* loadFileName, int size, OUT bool* check);
	vector<string> charArraySeparationExt(char charArray[], int size);

	txtData();
	~txtData();
};