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

	//세이브
	void txtSave(const char* saveFileName, vector<string> vStr); //vStr의 정보를 파일에 담아주는 함수
	char* vectorArrayCombine(vector<string> vArray);			 //vStr의 정보를 한줄의 문자열로 만들어주는 함수

	void txtSaveExt(const char* saveFileName, vector<string> vStr, int size); //vStr의 정보를 파일에 담아주는 함수 크기 증가
	char* vectorArrayCombineExt(vector<string> vArray, int size);			 //vStr의 정보를 한줄의 문자열로 만들어주는 함수 크기 증가

	//로드
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);
	vector<string> txtLoadExt(const char* loadFileName, int size, OUT bool* check);
	vector<string> charArraySeparationExt(char charArray[], int size);

	txtData();
	~txtData();
};