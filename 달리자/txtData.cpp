#include "stdafx.h"
#include "txtData.h"

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{
}

void txtData::txtSave(const char * saveFileName, vector<string> vStr)
{
	HANDLE file; //���� �ؽ�Ʈ ������ �ּҸ� ������ ���̵� ������

	char str[128];
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vStr), 126); //str�� vStr�� ����ֱ�
					//vectorArrayCombine�� vStr�� ��� 4���� �����͸� �Ѱ��� ���ڿ��� �ٲ���
	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); //CreateFile�� �ؽ�Ʈ���� bmp�� �پ��� ���� ���� ������
	//�ι�° ���ڴ� file�� ����� �ּҸ� �̿��� �������� ���� �˷��ִ� �κ�								 //������ ����(CREATE_ALWAYS) �ּҸ� file�� ����, ������ �������� �ּҸ� ����.

	WriteFile(file, str, 128, &write, NULL); //str�� ������ file�� ���� �̹� ������ ������ ��������

	CloseHandle(file); //�ڵ� �޸� ����
}

char * txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];

	ZeroMemory(str, sizeof(str)); //ZeorMemory�� memset �Լ��� ������ �ּ�, ������ ���̸� �޾� �� ���̸�ŭ�� �ʱ�ȭ����

	for (int i = 0; i < vArray.size(); ++i) //i++?
	{
		strncat_s(str, 128, vArray[i].c_str(), 126); //strncpy_s�� ��ü�� ������, strncat_s�� ���� �����Ϳ� �̾ �Է�
		
		if (i + 1 < vArray.size()) //i+1�� vArray.size()�̸� ������ ������ĭ => ������ĭ�� ������ ����
		{
			strcat_s(str, ","); //������ĭ �ƴϸ� , �߰� //strcat���� C4996���� ���ͼ� �ӽ÷� _s�߰�
		}
	}

	return str;
}

void txtData::txtSaveExt(const char * saveFileName, vector<string> vStr, int size)
{
	HANDLE file; //���� �ؽ�Ʈ ������ �ּҸ� ������ ���̵� ������

	char* str = new char[size];
	DWORD write;

	strncpy_s(str, size, vectorArrayCombineExt(vStr,size), size-2); //str�� vStr�� ����ֱ�
														//vectorArrayCombine�� vStr�� ��� 4���� �����͸� �Ѱ��� ���ڿ��� �ٲ���
	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); //CreateFile�� �ؽ�Ʈ���� bmp�� �پ��� ���� ���� ������
																										 //�ι�° ���ڴ� file�� ����� �ּҸ� �̿��� �������� ���� �˷��ִ� �κ�								 //������ ����(CREATE_ALWAYS) �ּҸ� file�� ����, ������ �������� �ּҸ� ����.

	WriteFile(file, str, size, &write, NULL); //str�� ������ file�� ���� �̹� ������ ������ ��������

	CloseHandle(file); //�ڵ� �޸� ����
}

char * txtData::vectorArrayCombineExt(vector<string> vArray, int size)
{
	char* str = new char[size];

	ZeroMemory(str, sizeof(str)); //ZeorMemory�� memset �Լ��� ������ �ּ�, ������ ���̸� �޾� �� ���̸�ŭ�� �ʱ�ȭ����

	for (int i = 0; i < vArray.size(); ++i) //i++?
	{
		strncat_s(str, size, vArray[i].c_str(), size-2); //strncpy_s�� ��ü�� ������, strncat_s�� ���� �����Ϳ� �̾ �Է�

		if (i + 1 < vArray.size()) //i+1�� vArray.size()�̸� ������ ������ĭ => ������ĭ�� ������ ����
		{
			strcat_s(str,size, ","); //������ĭ �ƴϸ� , �߰� //strcat���� C4996���� ���ͼ� �ӽ÷� _s�߰�
		}
	}

	return str;
}

vector<string> txtData::txtLoad(const char * loadFileName)
{
	HANDLE file;

	char str[128];
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
								//save���ʹ� �ٸ��� READ�� �ָ������� �˸���
	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file); //�ڵ� �޸� ����

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray; //���ڿ��� �ɰ��� ������ ����

	char* separator = ",";
	char* token;

	//%% strtok C4996 ���� => strtok_s�� ����
	//%% strtok_s�� strtok�� �� ���ڿ� ���� �߸��κ��� ������ �����̳� �ּҸ� ���ڷ� �޴´�.
	char* temp = NULL; //�����Ұ�

	token = strtok_s(charArray, separator, &temp);	//strtok�� separator ������������ ���ڿ��� �������� �Լ��� ����
	vArray.push_back(token);						//�ѹ� ����Ǹ� separator �ڸ� strtok ���ο�? ���� (=> �̹� ���� �κ��� �߶��ش�)
													//-> �ѹ� ���� �Ŀ��� strtok�� ù��° ���ڿ��� NULL�� �־��ָ� �ȴ�

	while (NULL != (token = strtok_s(NULL, separator, &temp))) //������ ������ strtok�� NULL�� ��ȯ
	{
		vArray.push_back(token);
	}

	return vArray;
}

vector<string> txtData::txtLoadExt(const char * loadFileName, int size, OUT bool* check)
{
	HANDLE file;

	char* str = new char[size];
	DWORD read;

	char filecheck[128];

	sprintf_s(filecheck, "D:\\����\\C++\\�޸���\\�޸���\\%s", loadFileName);

	if (PathFileExists(TEXT(filecheck)))
	{ 
		file = CreateFile(loadFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		//save���ʹ� �ٸ��� READ�� �ָ������� �˸���
		ReadFile(file, str, size, &read, NULL);
		*check = true;
	}
	else
	{
		*check = false;
		return vector<string>(); //����ִ� vector<string> ��������
	}


	CloseHandle(file); //�ڵ� �޸� ����

	return charArraySeparationExt(str, size);
}

vector<string> txtData::charArraySeparationExt(char charArray[], int size)
{
	vector<string> vArray; //���ڿ��� �ɰ��� ������ ����

	char* separator = ",";
	char* token;

	//%% strtok C4996 ���� => strtok_s�� ����
	//%% strtok_s�� strtok�� �� ���ڿ� ���� �߸��κ��� ������ �����̳� �ּҸ� ���ڷ� �޴´�.
	char* temp = NULL; //�����Ұ�

	token = strtok_s(charArray, separator, &temp);	//strtok�� separator ������������ ���ڿ��� �������� �Լ��� ����
	vArray.push_back(token);						//�ѹ� ����Ǹ� separator �ڸ� strtok ���ο�? ���� (=> �̹� ���� �κ��� �߶��ش�)
													//-> �ѹ� ���� �Ŀ��� strtok�� ù��° ���ڿ��� NULL�� �־��ָ� �ȴ�

	while (NULL != (token = strtok_s(NULL, separator, &temp))) //������ ������ strtok�� NULL�� ��ȯ
	{
		vArray.push_back(token);
	}

	return vArray;
}

txtData::txtData()
{
}

txtData::~txtData()
{
}
