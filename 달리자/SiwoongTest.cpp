#include "stdafx.h"
#include "SiwoongTest.h"
#include "player.h"
#include "CollisionCheckManager.h"
#include "Items.h"
#include "prisoner.h"
#include "star.h"
#include "smokeBomb.h"
#include "Obstacles.h"
#include "box.h"
#include "can.h"
#include "guards.h"

HRESULT SiwoongTest::init(void)
{
	_updateP = &SiwoongTest::selectUpdate; //this->_updateP 도 가능
	_renderP = &SiwoongTest::selectRender;

	//%%이미지 추가하는부분들 로딩신으로 넘기기?
	bool check;
	_obList = TXTDATA->txtLoadExt("장애물 목록.txt",2048, &check);
	_itemList = TXTDATA->txtLoadExt("아이템 목록.txt", 2048, &check);

	for (_oliter = _obList.begin(); _oliter != _obList.end() - 1; )
	{
		char temp[128];
		char temp2[128];
		strcpy_s(temp2, (*_oliter).c_str());
		sprintf_s(temp, "Image/Obstacles/%s.bmp", temp2);
		IMAGEMANAGER->addFrameImage(*_oliter, temp, stoi(*(_oliter + 2)), stoi(*(_oliter + 3)), stoi(*(_oliter + 1)), 1, true, RGB(255, 0, 255));

		++_oliter;
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
		IMAGEMANAGER->addFrameImage(*_oliter, temp, stoi(*(_oliter + 2)), stoi(*(_oliter + 3)), stoi(*(_oliter + 1)), 1, true, RGB(255, 0, 255));

		++_oliter;
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

	for (_itemCIter = _itemCList.begin(); _itemCIter != _itemCList.end(); ++_itemCIter)
	{
		SAFE_DELETE(*_itemCIter);
	}

	_itemCList.clear();

	for (_obCIter = _obCList.begin(); _obCIter != _obCList.end(); ++_obCIter)
	{
		SAFE_DELETE(*_obCIter);
	}

	_obCList.clear();

	for (_guardIter = _guardList.begin(); _guardIter != _guardList.end(); ++_guardIter)
	{
		SAFE_DELETE(*_guardIter);
	}

	_guardList.clear();
}

void SiwoongTest::update(void)
{
	(this->*_updateP)(); //this->_updateP() 와 *(this->_updateP)(); 또 (*_updateP)(), _updateP()는 에러남
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

	//%%&&  select 창 구현하고나서는 코드들 이동하기
	vector<string> toLoad;

	//%% select 창에서 맵파일 이름 받았다면 그 값을 사용
	char temp[128] = "맵맵맵"; 
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
		MessageBox(_hWnd, "입력한 이름에 해당하는 맵이 없어", "파일이름 좀 잘 써라", MB_OK | MB_ICONINFORMATION);
		return E_NOTIMPL;
	}
	//%%&&

	_colManager = new CollisionCheckManager;
	_colManager->init(stoi(toLoad[1])); //맵 총 길이를 넣어줄것 

	_player = new player;
	_player->init();

	_colManager->linkPlayer(_player);
	_player->linkColManager(_colManager);

	for (int i = 0; i < (int)(WINSIZEX / 50); i++)
	{
		guards* gTemp = new guards;
		gTemp->init();
		gTemp->SetPos({ (float)i * 50 , (float)WINSIZEY - 50 });
		_guardList.push_back(gTemp);
		_colManager->addIR(gTemp->GetIR());
	}

	for (int i = 0; i < (int)(WINSIZEX / 50) + 1; i++)
	{
		guards* gTemp = new guards;
		gTemp->init();
		gTemp->SetPos({ (float)i * 50 - 25 , (float)WINSIZEY - 70 });
		_guardList.push_back(gTemp);
		_colManager->addIR(gTemp->GetIR());
	}

	//여기에 loadMap 함수 넣기
	loadMap(toLoad, _colManager);

	_cameraY = 0;

	_frameCount = 0;

	return S_OK;
}

void SiwoongTest::gameUpdate(void)
{
	//민석씬 이동
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("민석씬");
		return; //changeScene을 하면 이 SiwoongTest의 release 함수가 실행되지만
				//changeScene이 실행된 update는 한번끝까지 실행되버린다 
				//release에서 _colManager를 지우고 밑에서 _colManager->GetGameover()를 하므로 터짐
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("영휘씬");
		return;
	}

	if (_colManager->GetGameover())
	{
		return;
	}

	//_cameraY -= 5;

	++_frameCount;

	_player->update();
	_cameraY = _player->GetCamY();

	for (_itemCIter = _itemCList.begin(); _itemCIter != _itemCList.end(); ++_itemCIter)
	{
		(*_itemCIter)->update();
	}

	for (_obCIter = _obCList.begin(); _obCIter != _obCList.end(); ++_obCIter)
	{
		(*_obCIter)->update();
	}

	for (int i = 0; i < _guardList.size(); i++)
	{
		_guardList[i]->update();
	}

	_colManager->update();
}

void SiwoongTest::gameRender(void)
{	
	//배경 종류 맵데이터에서 받아서 하는걸로 수정하기

	IMAGEMANAGER->findImage("background_jail")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _cameraY);

	//오브젝트들의 rc에는 글로벌 좌표를 저장하고
	//렌더할때 _cameraY값을 이용해 플레이어 기준 로컬 좌표로 변환

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
			(*_obIRIter)->_image->frameRender(getMemDC(), (*_obIRIter)->_rc.left, (*_obIRIter)->_rc.top - _cameraY, ((_frameCount % 40) < 20) ? 0 : 1, 0);
		}
	}

	for (_itemCIter = _itemCList.begin(); _itemCIter != _itemCList.end(); ++_itemCIter)
	{
		if ((*_itemCIter)->GetIR()->_rc.top - _cameraY > 0 && (*_itemCIter)->GetIR()->_rc.top - _cameraY <= WINSIZEY)
		{
			(*_itemCIter)->render(_cameraY);
		}
	}

	for (_obCIter = _obCList.begin(); _obCIter != _obCList.end(); ++_obCIter)
	{
		if ((*_obCIter)->GetIR()->_rc.top - _cameraY > 0 && (*_obCIter)->GetIR()->_rc.top - _cameraY <= WINSIZEY)
		{
			(*_obCIter)->render(_cameraY);
		}
	}

	for (int i = 0; i < _guardList.size(); i++)
	{
		_guardList[i]->render(_cameraY);
	}

	//_colManager->render();

	_player->render(_colManager->GetGameover());
}

void SiwoongTest::loadMap(vector<string> data, CollisionCheckManager* _colM)
{
	//data 첫칸은 배경 이미지 이름, 두번째칸은 맵길이

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

	for (_itemCIter = _itemCList.begin(); _itemCIter != _itemCList.end(); ++_itemCIter)
	{
		SAFE_DELETE(*_itemCIter);
	}

	_itemCList.clear();

	for (_obCIter = _obCList.begin(); _obCIter != _obCList.end(); ++_obCIter)
	{
		SAFE_DELETE(*_obCIter);
	}

	_obCList.clear();

	for (int i = 2; i < data.size() - 1;)
	{
	
		string tString;

		if (stoi(data[i+1]) == 1)
		{
			tString = _itemList[stoi(data[i]) * 4];

			if (tString.substr(0, 4).compare("star") == 0)
			{
				star* tStar = new star;
				tStar->init();
				RECT tR = RectMakeCenter(stoi(data[i + 2]), stoi(data[i + 3]), tStar->GetIR()->_image->getFrameWidth(), tStar->GetIR()->_image->getFrameHeight());
				tStar->SetPos({ (float)tR.left, (float)tR.top });
				_itemCList.push_back(tStar);
				_colM->addIR(tStar->GetIR());
			}
			else if (tString.substr(0, 8).compare("prisoner") == 0)
			{
				prisoner* tPrisoner = new prisoner;
				tPrisoner->init();
				RECT tR = RectMakeCenter(stoi(data[i + 2]), stoi(data[i + 3]), tPrisoner->GetIR()->_image->getFrameWidth(), tPrisoner->GetIR()->_image->getFrameHeight());
				tPrisoner->SetPos({ (float)tR.left, (float)tR.top });
				_itemCList.push_back(tPrisoner);
				tPrisoner->linkColManager(_colManager);
				_colM->addIR(tPrisoner->GetIR());
			}
			else if (tString.compare("bubble_smoke") == 0)
			{
				smokeBomb* tSmokeBomb = new smokeBomb;
				tSmokeBomb->init();
				RECT tR = RectMakeCenter(stoi(data[i + 2]), stoi(data[i + 3]), tSmokeBomb->GetIR()->_image->getFrameWidth(), tSmokeBomb->GetIR()->_image->getFrameHeight());
				tSmokeBomb->SetPos({ (float)tR.left, (float)tR.top });
				_itemCList.push_back(tSmokeBomb);
				tSmokeBomb->linkColManager(_colManager);
				tSmokeBomb->linkGuards(_guardList);
				_colM->addIR(tSmokeBomb->GetIR());
			}
			else
			{
				IR* temp = new IR;

				temp->_image = IMAGEMANAGER->findImage(tString);
				temp->_rc = RectMakeCenter(stoi(data[i + 2]), stoi(data[i + 3]), temp->_image->getFrameWidth(), temp->_image->getFrameHeight());
				//temp->_type = (char*) tString.c_str(); 
				temp->_type = (char *)tString.c_str();

				_itemIRList.push_back(temp);

				_colM->addIR(temp);
			}
		}
		else if (stoi(data[i + 1]) == 0)
		{
			tString = _obList[stoi(data[i]) * 4];

			if (tString.substr(0, 10).compare("object_box") == 0)
			{ 
				box* tbox = new box;
				tbox->init();
				RECT tR = RectMakeCenter(stoi(data[i + 2]), stoi(data[i + 3]), tbox->GetIR()->_image->getFrameWidth(), tbox->GetIR()->_image->getFrameHeight());
				tbox->SetPos({ (float)tR.left, (float)tR.top });
				_obCList.push_back(tbox);
				_colM->addIR(tbox->GetIR());
			}
			else if (tString.substr(0, 10).compare("object_can") == 0)
			{ 
				can* tcan = new can;
				tcan->init();
				RECT tR = RectMakeCenter(stoi(data[i + 2]), stoi(data[i + 3]), tcan->GetIR()->_image->getFrameWidth(), tcan->GetIR()->_image->getFrameHeight());
				tcan->SetPos({ (float)tR.left, (float)tR.top });
				_obCList.push_back(tcan);
				_colM->addIR(tcan->GetIR());
			}
			else
			{
				IR* temp = new IR;
				temp->_image = IMAGEMANAGER->findImage(tString);
				temp->_rc = RectMakeCenter(stoi(data[i + 2]), stoi(data[i + 3]), temp->_image->getFrameWidth(), temp->_image->getFrameHeight());
				//temp->_type = (char*) tString.c_str(); 
				//temp->_type = (char *)tString.c_str();
				temp->_type = "can";
				_obIRList.push_back(temp);

				_colM->addIR(temp);
			}
		}

	
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