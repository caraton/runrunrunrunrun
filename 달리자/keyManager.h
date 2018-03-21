#pragma once
//stdafx�� ���⼭ include���� �ʰ� cpp���� include -> ��ȣ���� ȸ��
#include "singletonBase.h"
#include <bitset>  //bitset�� set�� vector�� cross? ����:http://mayple.tistory.com/entry/CSTL-8��-set-multiset-bitset

using namespace std;

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyDown;
	bitset<KEYMAX> _keyUp; //���⼭�� keyUp�� ���ȴٰ� �ٽ� �ö󰡴� �������� ��Ī
						   //���� �ƹ��͵� �ȴ��� �⺻ ���´� false���� �Ѵ�.

public:
	HRESULT init(void); //HRESULT ����:http://skmagic.tistory.com/286
	void release(void);

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	bitset<KEYMAX> getKeyDown(void) { return _keyDown; };
	bitset<KEYMAX> getKeyUp(void) { return _keyUp; };

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); };
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); };

	keyManager();
	~keyManager();
};