#pragma once
//inline�� templateó�� ������Ͽ� �� �� �־�� Ȯ���� �� ���� �ܺ� ���� ������ �Ȼ���
template <typename T> //template�� ����� ��� ������ �ϴ� ������ ������ �ϴ� ������ ��� ������ ������ �־����
class singletonBase   //-> ������Ͽ� ��� ������ ��ų�, ������ �ڵ��� ��� �ҽ����ϵ� include�� �����ؾ��Ѵ�.
{
protected:
	static T* singleton; //1. �� �̱��� ���̽� Ŭ������ �ν��Ͻ� T�ڸ����� singletonBase��� �ڽ� Ŭ������ �̸��� �ٷ�
						 //������ template ��� (�׷��� �ڽ� Ŭ������ ������ �ν��Ͻ��� ������ �� �ν��Ͻ���
						 //Ŭ���� Ÿ���� �θ��� singletonBase�� �ƴ϶� �ڱ� �ڽ��� �ǵ��� �� �� �ִ�.)
						 //2. static �����̹Ƿ� ���� Ŭ���� ���ο��� �ϰ� ����(�޸� �Ҵ�) �� �ʱ�ȭ�� �ܺο��� ����

	singletonBase() {}; //�ܺο��� ���Ƿ� �����ڿ� ������ �� ������ protected���ٰ� ����
	~singletonBase() {};

public:
	static T* getSingleton(void); //�� Ŭ���� �ν��Ͻ�, �� signleton�� ����� �������� �Լ� (������ ó�� �ѹ���)
								  //Ŭ������ static�� ������ �Լ��� Ŭ������ �ν��Ͻ��� �����Ǿ� ���� �ʾƵ� �����
								  //�� �ִ�. �� getSingleton�Լ��� ���ʿ� �ν��Ͻ��� �Ѱ��� ���������� ����Ǿ�
								  //���� ���ǵ� �ν��Ͻ� singleton�� �����ؾ� �ϹǷ� static �Լ��̾���Ѵ�.
								  //�ѹ� singleton�� �����ǰ� ������ singleton�� ������.
								  //%% �ν��Ͻ��� ���� ��쿡�� ����Ǿ� �ϹǷ� static �Լ��� static�������� ����ؾ�
								  //�Ѵ�. ����:http://yhs1981.tistory.com/entry/C-Ŭ��������-���Ǵ�-static-���-����-��-�Լ�

	void releaseSingleton(void); //�̱��� ���� �Լ�
};

template <typename T>
T* singletonBase<T>::singleton = 0; //Ŭ���� �ȿ��� ����� static ������ ����(�޸� �Ҵ�) �� �ʱ�ȭ
									//Ŭ���� �ȿ��� ���� �� �ʱ�ȭ�� ���� �����Ƿ� �ν��Ͻ��� �����ɶ����� 
									//���� �� �ʱ�ȭ�� �ݺ����� �ʴ´�.
template<typename T>
inline T * singletonBase<T>::getSingleton(void)
{
	if (!singleton)
	{
		singleton = new T; //singleton�� T�� ������. new T�� ���� T�� ���� �Ҵ��� ��, �� �ּҰ���
	}					   //singleton�� ������

	return singleton;
}//�� �Լ��� ȣ���ϸ� singleton�� return�ϹǷ� getSingeton() == singleton �̴�.

template<typename T>
inline void singletonBase<T>::releaseSingleton(void)
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}