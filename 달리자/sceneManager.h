#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode; //gameNode�� stdafx�� ���� sceneManager�� �����ϹǷ� ��ȣ������ ���ϱ� ���� ���漱��

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList; //gameNode�� ���漱�� �� �����̹Ƿ� 4byte�� �����͸� ������� ������ �����Ϸ��� �޸� �Ҵ��� ��� �ؾ� ���� ���� ���� �߻�
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	//�� 3 �������� static�̹Ƿ� ���� ���⼭ �ϰ� ����(�޸� �Ҵ�)�� �ܺο��� �Ѵ� (sceneManager.cpp�� {} �ٱ�)
	//%%static ������ ����,�ʱ�ȭ�� �ǵ����̸� cpp���� ���ٰ� (������� �� ��� ���� ���� ����?)
	static gameNode* _currentScene; //���� ���Ǵ� ���� ����ų ������
	//�Ʒ� �ΰ��� ��Ƽ�����带 ���� �߰��س������� ���� Ŀ��ŧ������ �� �Ⱦ�
	static gameNode* _loadingScene;
	static gameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�� �߰��ϴ� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);
	
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);
	//���� ��ü�ϸ鼭 �߰��� �ε����� �ִ°��
	HRESULT changeScene(string sceneName, string loadingSceneName);

	friend DWORD CALLBACK loadingThread(LPVOID prc);

	sceneManager();
	~sceneManager();
};