#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h" //���漱���� �� gameNode�� cpp���Ͽ��� ����

//������� ����� static ������ �����ϱ�
gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL) //map�� �ι�° value �� gameNode*�� NULL �� �ƴϸ�
		{
			if (miSceneList->second == _currentScene) //���� ����ϴ� ���� ���
			{
				miSceneList->second->release(); //�� ����߿� �Ҵ�� �޸𸮵��� release
				//%%�������� second�� �ڷ����� gameNode*�̹Ƿ� second�� gameNode�� �ڼ��̰�,
				//�Լ��� �������̵��Ѵ� �ص�(�ڼտ��� release�� ������ �����Ѵ��ص�)
				//�Ϲ����� ���� ������ �ڷ����� �������� ȣ��Ǿ� gameNode�� release�� ���� (�̱������ �� Ǯ�����)
				//�׷��� �Լ� ���� ���� �տ� virtual�� ��־��ָ� ������ �ڷ����� �ƴ϶�
				//�����Ͱ� ����Ű�� Ŭ������ �ڷ����� �������� ȣ�����ش�.
				//http://blog.eairship.kr/175
			}

			SAFE_DELETE(miSceneList->second);

			miSceneList = _mSceneList.erase(miSceneList); //map::erase�� ��ǲ iterator �ּҰ� ��ġ�� �����ϰ� ���� �ּҸ� ���� iterator�� return�Ѵ�
		}
		else
		{
			++miSceneList;
		}

		_mSceneList.clear();
	}
}

void sceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	//�ش� ���� ������ (�����Ͱ� ����ִ� ���̸�)
	if (!scene)
	{
		return NULL;
	}

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene; //��ǲ���� ���� scene�� �״�� �ƿ�ǲ�� �ʿ䰡 �ִ°�?
}

gameNode * sceneManager::addLoadingScene(string loadingSceneName, gameNode * scene)
{
	if (!scene)
	{
		return NULL;
	}

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	//���ͷ����Ϳ� sceneName�� first(string)������ ���� ��带 ã�� �ּ� ����
	mapSceneIter find = _mSceneList.find(sceneName);

	//�ʿ� ���� �������� ������ (end()�� �����Ͱ� ���ִ� ������ĭ ������ �ּ�)
	if (find == _mSceneList.end())
	{
		return E_FAIL;
	}

	//ã�� ���� ���� ���̸�
	if (find->second == _currentScene)
	{
		return S_OK; //��ü�� �ʿ� ���� ���� �޽��� ����
	}

	//ã�� �� ��ü
	if (SUCCEEDED(find->second->init())) //FAILED�� �ݴ뿪���� �ϴ� SUCCEEDED
	{
		if (_currentScene)
		{
			_currentScene->release(); //�ʱ�ȭ
		}

		_currentScene = find->second; //�� ��ü

		return S_OK;

	}

	return E_FAIL;
}

DWORD CALLBACK loadingThread(LPVOID prc)
{
	//���� ��(ü������ �Ͼ ��)�� �����س���
	sceneManager::_readyScene->init();

	// ���� ���� �������ش�
	sceneManager::_currentScene = sceneManager::_readyScene;

	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

//���� ��ü�ϸ鼭 �߰��� �ε����� �ִ°��
HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//�ʿ� ���� �������� ������ (end()�� �����Ͱ� ���ִ� ������ĭ ������ �ּ�)
	if (find == _mSceneList.end())
	{
		return E_FAIL;
	}

	//ã�� ���� ���� ���̸�
	if (find->second == _currentScene)
	{
		return S_OK; //��ü�� �ʿ� ���� ���� �޽��� ����
	}

	//sceneName�� �����ϰ� ��ü�� �ؾ��� ���� Ȯ�� �Ǿ����Ƿ� �ε��� ã��
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if (findLoading == _mLoadingSceneList.end()) 
	{
		return changeScene(loadingSceneName);
	}

	//ã�� �� ��ü
	if (SUCCEEDED(find->second->init())) //FAILED�� �ݴ뿪���� �ϴ� SUCCEEDED
	{
		if (_currentScene)
		{
			_currentScene->release(); //�ʱ�ȭ
		}

		_loadingScene = findLoading->second;

		_readyScene = find->second;

		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadingThreadID));
	}
	
	return E_FAIL;
}

sceneManager::sceneManager()
{
}

sceneManager::~sceneManager()
{
}