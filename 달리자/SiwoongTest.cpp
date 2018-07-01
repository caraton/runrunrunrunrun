#include "stdafx.h"
#include "SiwoongTest.h"
#include "player.h"
#include "CollisionCheckManager.h"

HRESULT SiwoongTest::init(void)
{
	_updateP = &SiwoongTest::selectUpdate; //this->_updateP �� ����
	_renderP = &SiwoongTest::selectRender;

	//%%�̹��� �߰��ϴºκе� �ε������� �ѱ��?
	_obList = TXTDATA->txtLoad("��ֹ� ���.txt");
	_itemList = TXTDATA->txtLoad("������ ���.txt");

	for (_oliter = _obList.begin(); _oliter != _obList.end() - 1; )
	{
		char temp[128];
		char temp2[128];
		strcpy_s(temp2, (*_oliter).c_str());
		sprintf_s(temp, "Image/Obstacles/%s.bmp", temp2);
		IMAGEMANAGER->addFrameImage(*_oliter, temp, stoi(*(_oliter + 1)), stoi(*(_oliter + 2)), 2, 1, true, RGB(255, 0, 255));

		++_oliter;
		++_oliter;
		++_oliter;
	}

	for (_oliter = _itemList.begin(); _oliter != _itemList.end() - 1; )
	{
		char temp[128];
		char temp2[128];
		strcpy_s(temp2, (*_oliter).c_str());
		sprintf_s(temp, "Image/Items/%s.bmp", temp2);
		IMAGEMANAGER->addFrameImage(*_oliter, temp, stoi(*(_oliter + 1)), stoi(*(_oliter + 2)), 2, 1, true, RGB(255, 0, 255));

		++_oliter;
		++_oliter;
		++_oliter;
	}

	_updateP = &SiwoongTest::gameUpdate; 
	_renderP = &SiwoongTest::gameRender;

	gameInit();


	return S_OK;
}

void SiwoongTest::release(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_colManager);
}

void SiwoongTest::update(void)
{
	(this->*_updateP)(); //this->_updateP() �� *(this->_updateP)(); �� (*_updateP)(), _updateP()�� ������
}

void SiwoongTest::render(void)
{
	(this->*_renderP)();
}

void SiwoongTest::selectUpdate(void)
{

}

void SiwoongTest::selectRender(void)
{

}

HRESULT SiwoongTest::gameInit(void)
{
	IMAGEMANAGER->addImage("background_jail", "Image/background_jail.bmp", 600, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background", "Image/background.bmp", 600, 800, true, RGB(255, 0, 255));

	//%%&&  select â �����ϰ����� �ڵ�� �̵��ϱ�
	vector<string> toLoad;

	//%% select â���� ������ �̸� �޾Ҵٸ� �� ���� ���
	char temp[128] = "�ʸʸ�"; 
	//%%

	char map[128];
	sprintf_s(map, "%s.txt", temp);

	bool check = false;

	toLoad = TXTDATA->txtLoadExt(map, TXTSIZE, &check);

	if (check)
	{

	}
	else
	{
		MessageBox(_hWnd, "�Է��� �̸��� �ش��ϴ� ���� ����", "�����̸� �� �� ���", MB_OK | MB_ICONINFORMATION);
		return E_NOTIMPL;
	}
	//%%&&

	_colManager = new CollisionCheckManager;
	_colManager->init(stoi(toLoad[1])); //�� �� ���̸� �־��ٰ� 

	_player = new player;
	_player->init();

	_colManager->linkPlayer(_player);
	_player->linkColManager(_colManager);

	//���⿡ loadMap �Լ� �ֱ�
	loadMap(toLoad, _colManager);

	//_testIR._image = IMAGEMANAGER->addImage("�׽�Ʈ��ֹ�", "Image/Obstacles/enemy.bmp", 40, 40, true, RGB(255, 0, 255));
	//_testIR._rc = RectMakeCenter(100, -40, 40, 40);
	//_testIR._type = "devil";
	//_testIRy = -40;

	//for (int i = 0; i < _colManager->GetMapLength() / 100; ++i)
	//{
	//	IR temp;
	//	temp._image = IMAGEMANAGER->addImage("�׽�Ʈ��ֹ�2", "Image/Obstacles/object_can.bmp", 50, 50, true, RGB(255, 0, 255));
	//	temp._rc = RectMakeCenter(WINSIZEX / 2 - 100, 25 + i * 100 - _colManager->GetMapLength() + WINSIZEY, 50, 50);
	//	temp._type = "can";
	//	_trashcans.push_back(temp);
	//}

	//_colManager->addIR(&_testIR); //�浹ó���� IR���� colManager�� �����ֱ�
	//for (_tcIter = _trashcans.begin(); _tcIter != _trashcans.end(); ++_tcIter)
	//{
	//	_colManager->addIR(&*_tcIter);
	//}
	//_colManager->addIR(&_player->GetIR());

	_cameraY = 0;

	return S_OK;
}

void SiwoongTest::gameUpdate(void)
{
	//�μ��� �̵�
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("�μ���");
		return; //changeScene�� �ϸ� �� SiwoongTest�� release �Լ��� ���������
				//changeScene�� ����� update�� �ѹ������� ����ǹ����� 
				//release���� _colManager�� ����� �ؿ��� _colManager->GetGameover()�� �ϹǷ� ����
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("���־�");
		return;
	}

	if (_colManager->GetGameover())
	{
		return;
	}

	//_cameraY -= 5;

	_player->update();

	//if (_testIRy > -2 * WINSIZEY + 1)
	//{
	//	_testIRy -= 1;
	//}

	//_testIR._rc = RectMakeCenter(100, _testIRy, 40, 40);

	_colManager->update();
}

void SiwoongTest::gameRender(void)
{
	_cameraY = _player->GetCamY();

	//��� ���� �ʵ����Ϳ��� �޾Ƽ� �ϴ°ɷ� �����ϱ�

	IMAGEMANAGER->findImage("background_jail")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _cameraY);

	//������Ʈ���� rc���� �۷ι� ��ǥ�� �����ϰ�
	//�����Ҷ� _cameraY���� �̿��� �÷��̾� ���� ���� ��ǥ�� ��ȯ
	//if (_testIR._rc.top - _cameraY > 0 && _testIR._rc.top - _cameraY <= WINSIZEY)
	//{
	//	_testIR._image->render(getMemDC(), _testIR._rc.left, _testIR._rc.top - _cameraY);
	//}

	//for (_tcIter = _trashcans.begin(); _tcIter != _trashcans.end(); ++_tcIter)
	//{
	//	if ((*_tcIter)._rc.top - _cameraY > 0 && (*_tcIter)._rc.top - _cameraY <= WINSIZEY)
	//	{
	//		(*_tcIter)._image->render(getMemDC(), (*_tcIter)._rc.left, (*_tcIter)._rc.top - _cameraY);
	//	}
	//}

	for (_obIRIter = _obIRList.begin(); _obIRIter != _obIRList.end(); ++_obIRIter)
	{
		if ((*_obIRIter)->_rc.top - _cameraY > 0 && (*_obIRIter)->_rc.top - _cameraY <= WINSIZEY)
		{
			(*_obIRIter)->_image->frameRender(getMemDC(), (*_obIRIter)->_rc.left, (*_obIRIter)->_rc.top - _cameraY, 0, 0);
		}
	}

	for (_obIRIter = _itemIRList.begin(); _obIRIter != _itemIRList.end(); ++_obIRIter)
	{
		if ((*_obIRIter)->_rc.top - _cameraY > 0 && (*_obIRIter)->_rc.top - _cameraY <= WINSIZEY)
		{
			(*_obIRIter)->_image->frameRender(getMemDC(), (*_obIRIter)->_rc.left, (*_obIRIter)->_rc.top - _cameraY, ((TIMEMANAGER->getFrameCount() % 10) < 5) ? 0 : 1, 0);
		}
	}

	//_colManager->render();

	_player->render(_colManager->GetGameover());
}

void SiwoongTest::loadMap(vector<string> data, CollisionCheckManager* _colM)
{
	//data ùĭ�� ��� �̹��� �̸�, �ι�°ĭ�� �ʱ���

	for (_obIRIter = _obIRList.begin(); _obIRIter != _obIRList.end(); ++_obIRIter)
	{
		SAFE_DELETE(*_obIRIter);
	}

	_obIRList.clear();

	for (_obIRIter = _itemIRList.begin(); _obIRIter != _itemIRList.end(); ++_obIRIter)
	{
		SAFE_DELETE(*_obIRIter);
	}

	_itemIRList.clear();

	for (int i = 2; i < data.size() - 1;)
	{
		IR* temp = new IR;
		
		string tString;

		if (stoi(data[i+1]) == 1)
		{
			tString = _itemList[stoi(data[i]) * 3];
			temp->_image = IMAGEMANAGER->findImage(tString);
			temp->_rc = RectMakeCenter(stoi(data[i + 2]), stoi(data[i + 3]), temp->_image->getFrameWidth(), temp->_image->getFrameHeight());
			//temp->_type = (char*) tString.c_str(); 
			temp->_type = (char *)tString.c_str();
			_itemIRList.push_back(temp);
		}
		else if (stoi(data[i + 1]) == 0)
		{
			tString = _obList[stoi(data[i]) * 3];
			temp->_image = IMAGEMANAGER->findImage(tString);
			temp->_rc = RectMakeCenter(stoi(data[i + 2]), stoi(data[i + 3]), temp->_image->getFrameWidth(), temp->_image->getFrameHeight());
			//temp->_type = (char*) tString.c_str(); 
			temp->_type = (char *)tString.c_str();
			_obIRList.push_back(temp);
		}

		_colM->addIR(temp);

		++i;
		++i;
		++i;
		++i;
	}
}

SiwoongTest::SiwoongTest()
{
	_player = NULL;
}

SiwoongTest::~SiwoongTest()
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_colManager);
}