#include "stdafx.h" //stdafx���� ��۹�� ���ư��� ��ȣ���� ������ ȸ���ϱ� ���� cpp�� �ֱ�
#include "keyManager.h" //(stdafx ��������� keyManager ����� include��) ��ȣ����: http://jrabbit.tistory.com/35, http://enginius.tistory.com/6

HRESULT keyManager::init(void)
{
	//ó������ : ��� Ű�� ������ ��������
	for (int i = 0; i < KEYMAX; i++)
	{
		this->setKeyUp(i, false); //keyManager�� �����Ҵ��� �ϴ� singletonBase�� �ڽ��̹Ƿ� this. �� �ƴ϶� this-> ���
		this->setKeyDown(i, false);
	}
	return S_OK; //S_OK : ������ Boolean TRUE ��(0X0)���� S_FALSE�� �Բ� ���Ǹ� �Լ��� �����Ͽ����� �ǹ��Ѵ�.
}

void keyManager::release(void)
{
	//���� keyManager�� release�� ����� �ʿ���� 
}

bool keyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) //& 0x8000�� ������ ������ Ű�� �������� ���� Ű�� ������ ���� 0x0001 (�� 1)�� ���� �Ǿ� �����Ƿ� 0x0001�� �����ϱ� ���� 0x8000�� ������ ����. ����:http://blog.eairship.kr/156
	{	//getKeyDown�� ��ǲ���� _keyDown�� �������� �Լ� ==> getKeyDown()[key] == _keyDown[key]
		if (!this->getKeyDown()[key]) //�̺κ��� ������ ��� Ű�� ������ �ִ� ��Ȳ������ true�� return�ǹǷ� once�� ������ �ٸ���
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else
	{
		this->setKeyDown(key, false);
	}

	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) //������ �ʴٰ� �� �Լ��� ����Ǵ� ������ key ��ư�� ������� ��
	{
		this->setKeyUp(key, true); //key�� ���� ������ isOnceKeyDown �Լ����� setKeyDown(key, true)�� ����Ǹ鼭
								   //setKeyUp(key, true)�� ����� <== �ѹ� ������ �������� �ٽ� �ö� ���̹Ƿ� ���⼭ keyup�� true��
	}
	else //key ��ư�� ������ �������� ����
	{
		if (this->getKeyUp()[key]) // �̰��� true��� ������ �ѹ� ���ȴٴ� ��
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}

	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) //0x0001: ������ Ű�� �������� ���� Ű�� ������ ����
	{
		return true;
	}

	return false;
}

keyManager::keyManager()
{
}

keyManager::~keyManager()
{
}
