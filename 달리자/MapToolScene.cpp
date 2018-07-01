#include "stdafx.h"
#include "MapToolScene.h"

char MapToolScene::backgroundChoiceStr[128] = " ";
HWND MapToolScene::_hMapTool = NULL;
string MapToolScene::_currentImageName;
image* MapToolScene::_currentImage = NULL;
bool MapToolScene::_isCurrentOn = false;
bool MapToolScene::_isItemnow = false;
bool MapToolScene::_savefbool = false;
bool MapToolScene::_loadfbool = false;
bool MapToolScene::_clearfbool = false;
bool MapToolScene::_erasefbool = false;

MapToolScene::MapToolScene()
{
}


MapToolScene::~MapToolScene()
{
	ReleaseDC(_hMapTool, _hdcMapTool);
}

HRESULT MapToolScene::init(void)
{
	_hdcMapTool = GetDC(_hMapTool);

	//%%맵툴용
	IMAGEMANAGER->addFrameImage("bg_jail_mini_02", "Image/bg_jail_mini_02.bmp", 180, 80, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bg_city_mini_02", "Image/bg_city_mini_02.bmp", 180, 80, 3, 1, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addImage("object_box", "Image/Obstacles/object_box.bmp", 50, 50, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("object_can", "Image/Obstacles/object_can.bmp", 50, 50, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("object_greeen", "Image/Obstacles/object_greeen.bmp", 50, 50, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("object_yellow", "Image/Obstacles/object_yellow.bmp", 50, 50, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("테스트장애물", "Image/Obstacles/enemy.bmp", 40, 40, true, RGB(255, 0, 255));

	_mapToolOn = 0;
	_jailB = new button;
	_jailB->init("bg_jail_mini_02", 280, 140, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), &jailButton);
	_cityB = new button;
	_cityB->init("bg_city_mini_02", 350, 140, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), &cityButton);

	mint = 0;

	//for (int i = 0; i < _totalObjectCount; ++i)
	//{
	//	button* temp = new button;
	//	temp->init
	//}

	//button* temp = new button;
	//temp->init("object_box", 700, 50, )

	//_loopY = 0;
	//_scrollY = 0;

	return S_OK;
}

HRESULT MapToolScene::init2(void)
{
	_hdcMapTool = GetDC(_hMapTool);

	//%%맵툴용

	//IMAGEMANAGER->addFrameImage("테스트장애물맵툴", "Image/Obstacles/enemy_icon.bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	//button* btemp = new button;
	//btemp->init("테스트장애물맵툴", 675, 45, PointMake(1, 0), PointMake(0, 0), &obButton);
	//_bList.push_back(btemp);
	bool check;
	_obList = TXTDATA->txtLoadExt("장애물 목록.txt", 1024, &check);

	int i = 0;
	for (_oliter = _obList.begin(); _oliter != _obList.end()-1; )
	{
		char temp[128];
		char temp2[128];
		strcpy_s(temp2, (*_oliter).c_str());
		sprintf_s(temp, "Image/Obstacles/%s.bmp", temp2);
		IMAGEMANAGER->addFrameImage(*_oliter, temp, stoi(*(_oliter+1)), stoi(*(_oliter+2)), 2, 1, true, RGB(255, 0, 255));
		button btemp;
		btemp.init(temp2, 675, 45+ i*100, PointMake(1,0), PointMake(0, 0), &obButton);
		_bList.push_back(btemp);
		i++;
		++_oliter;
		++_oliter;
		++_oliter;
	}

	_itemList = TXTDATA->txtLoadExt("아이템 목록.txt", 1024, &check);

	int j = i;
	for (_oliter = _itemList.begin(); _oliter != _itemList.end() - 1; )
	{
		char temp[128];
		char temp2[128];
		strcpy_s(temp2, (*_oliter).c_str());
		sprintf_s(temp, "Image/Items/%s.bmp", temp2);
		IMAGEMANAGER->addFrameImage(*_oliter, temp, stoi(*(_oliter + 1)), stoi(*(_oliter + 2)), 2, 1, true, RGB(255, 0, 255));
		button btemp;
		btemp.init(temp2, 675, 45 + j * 100, PointMake(1, 0), PointMake(0, 0), &itemButton);
		_itembList.push_back(btemp);
		j++;
		++_oliter;
		++_oliter;
		++_oliter;
	}

	//IMAGEMANAGER->addImage("object_box", "Image/Obstacles/object_box.bmp", 50, 50, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("object_can", "Image/Obstacles/object_can.bmp", 50, 50, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("object_greeen", "Image/Obstacles/object_greeen.bmp", 50, 50, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("object_yellow", "Image/Obstacles/object_yellow.bmp", 50, 50, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("SAVE", "Image/button_save.bmp", 200, 30, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LOAD", "Image/button_load.bmp", 200, 30, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CLEAR", "Image/button_clear.bmp", 200, 30, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ERASE", "Image/button_erase.bmp", 200, 30, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("지우개", "Image/eraser.bmp", 60, 30, 2, 1, true, RGB(255, 0, 255));

	_saveB = new button;
	_saveB->init("SAVE", WINSIZEX+ 300, WINSIZEY -70, PointMake(1, 0), PointMake(0, 0), &saveButton);
	_loadB = new button;
	_loadB->init("LOAD", WINSIZEX + 300, WINSIZEY - 30, PointMake(1, 0), PointMake(0, 0), &loadButton);

	_clearB = new button;
	_clearB->init("CLEAR", WINSIZEX + 300, WINSIZEY - 110, PointMake(1, 0), PointMake(0, 0), &clearButton);

	_eraseB = new button;
	_eraseB->init("ERASE", WINSIZEX + 300, WINSIZEY - 150, PointMake(1, 0), PointMake(0, 0), &eraseButton);

	_mapArea = RectMake(0, 0, WINSIZEX, WINSIZEY);

	_loopY = 0;
	_scrollY = 0;

	_frameCount = 0;

	return S_OK;
}

void MapToolScene::release(void)
{
	ReleaseDC(_hMapTool, _hdcMapTool);
	_hMapTool = NULL;
	_hInput = NULL;
	_hInput2 = NULL;

	SAFE_DELETE(_saveB);
	SAFE_DELETE(_loadB);
	SAFE_DELETE(_clearB);
	SAFE_DELETE(_eraseB);

	_obList.clear();

	_bList.clear();

	_itemList.clear();
	_itembList.clear();

	_currentImage = NULL;

	for (_4tupleiter = _4tuplesList.begin(); _4tupleiter != _4tuplesList.end(); ++_4tupleiter)
	{
		SAFE_DELETE(*_4tupleiter);
	}
	_4tuplesList.clear();
	for (_4tupleiter = _rearrangedList.begin(); _4tupleiter != _rearrangedList.end(); ++_4tupleiter)
	{
		SAFE_DELETE(*_4tupleiter);
	}
	_rearrangedList.clear();

	*mstr = '\0';//'\0'은 문자열에서 데이터가 들어있는 마지막칸 바로 다음의 칸에 들어있는 값
								//따라서 첫번째칸에 이 값을 넣어주면 비어있는 문자열이 된다.
								//memset(mstr, 0, sizeof(mstr)); 이방식도 가능
	*mstr2 = '\0';
	*nstr = '\0';

	_frameCount = 0;
}

void MapToolScene::release2(void)
{
	ReleaseDC(_hMapTool, _hdcMapTool);
	_hMapTool = NULL;
	_hInput = NULL;
	_hInput2 = NULL;

	SAFE_DELETE(_cityB);
	SAFE_DELETE(_jailB);
}

void MapToolScene::update(void)
{
	if (_mapToolOn == 1)
	{
		_jailB->update();
		_cityB->update();
	}
	else if (_mapToolOn == 2)
	{
		++_frameCount;
		//데이터 로드는 계속 실행되는 업데이트가 아니라 _mapToolOn가 2가되는 순간 한번만 실행되도록 바꾸기
		//vector<string> toLoad;

		//toLoad = TXTDATA->txtLoad("맵툴 실험.txt");

		//*(mstr) = '\0'; //'\0'은 문자열에서 데이터가 들어있는 마지막칸 바로 다음의 칸에 들어있는 값
		//				//따라서 첫번째칸에 이 값을 넣어주면 비어있는 문자열이 된다.
		//				//memset(mstr, 0, sizeof(mstr)); 이방식도 가능

		//_buttonCount = 0;

		//////기존의 mstr로 TextOut 그려진 부분을 지워준다
		////RECT clearbox = RectMake(0, 0, WINSIZEX, WINSIZEY);
		////InvalidateRect(_hMapTool, &clearbox, true);

		//strcpy_s(mstr, (*toLoad.begin()).c_str());
		//_buttonCount = stoi((*(toLoad.begin() + 1)));

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_loopY >= -mint)
			{
				_loopY -= 5;
			}
			else
			{
				_loopY = -mint;
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_loopY <= 0)
			{
				_loopY += 5;
			}
			else
			{
				_loopY = 0;
			}
		}

		_saveB->update();
		_loadB->update();
		_clearB->update();
		_eraseB->update();

		int i = 0;
		for (_bliter = _bList.begin(); _bliter != _bList.end(); ++_bliter)
		{
			(*_bliter).changeRECTCoordinate(675, 45 + i * 100 + _scrollY * 10);
			(*_bliter).update2();
			i++;
		}

		int j = i;
		for (_bliter = _itembList.begin(); _bliter != _itembList.end(); ++_bliter)
		{
			(*_bliter).changeRECTCoordinate(675, 45 + j * 100 + _scrollY * 10);
			(*_bliter).update3();
			j++;
		}

		if (_isCurrentOn && PtInRect(&_mapArea, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				newObjectData* temp = new newObjectData;
				temp->_imageName = _currentImageName;
				temp->_image = _currentImage;
				temp->_xycoordinate.x = _ptMouse.x;
				temp->_xycoordinate.y = _ptMouse.y +_loopY;
				temp->_isItem = _isItemnow;
				_4tuplesList.push_back(temp);
			}
		}


		if (_erasefbool && PtInRect(&_mapArea, _ptMouse))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_isErasing = true;

				RECT eraserR = RectMakeCenter(_ptMouse.x, _ptMouse.y + _loopY, 50, 50);
				
				for (_4tupleiter = _4tuplesList.begin(); _4tupleiter != _4tuplesList.end();)
				{
					if (PtInRect(&eraserR, (*_4tupleiter)->_xycoordinate))
					{
						newObjectData* toErase = (*_4tupleiter);
						_4tupleiter = _4tuplesList.erase(_4tupleiter); 
						//%% erase에 iterator(여기선 _4tupleiter)를 대입해 지우면 그 iterator 위치의 값도 지우지만
						//%% _4tupleiter의 iterator 값도 의미가 없어진다. 
						//%%%% 그러나 erase가 그 다음 iterator 값을 리턴하므로 
						//%%%% _4tupleiter에 그 리턴값을 대입해주면 된다.
						SAFE_DELETE(toErase);
					}
					else
					{
						++_4tupleiter;
					}
				}
			}
			else
			{
				_isErasing = false;
			}
		}

		if (_savefbool)
		{
			mapSave();
			_savefbool = false;
		}

		if (_loadfbool)
		{
			mtLoadMap();
			_loadfbool = false;
		}

		if (_clearfbool)
		{
			for (_4tupleiter = _4tuplesList.begin(); _4tupleiter != _4tuplesList.end(); ++_4tupleiter)
			{
				SAFE_DELETE(*_4tupleiter);
			}
			_4tuplesList.clear();
			_clearfbool = false;
		}
	}
}

void MapToolScene::render(void)
{

	if (_mapToolOn == 1)
	{
		//PatBlt(getMemDCMapTool(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		////==============================================================================================================
		char teststr[128] = "맵길이 :";
		sprintf_s(teststr, "맵길이 : %s", mstr);

		TextOut(_hdcMapTool, 30, 150, teststr, strlen(teststr));
		//TextOut(_hdcMapTool, 90, 150, mstr, strlen(mstr));

		char testtest[128];
		sprintf_s(testtest, "카운트 : %d", _buttonCount);

		TextOut(_hdcMapTool, 30, 200, testtest, strlen(testtest));

		//IMAGEMANAGER->findImage("background_jail")->render(_hdcMapTool, 250, 100, 60, 80, 0, 0, 600, 800);
		//IMAGEMANAGER->findImage("background")->render(_hdcMapTool, 320, 100, 60, 80, 0, 0, 600, 800);
		_jailB->render(_hdcMapTool);
		_cityB->render(_hdcMapTool);

		char backgroundChoiceStr2[128] = "배경 : ";
		sprintf_s(backgroundChoiceStr2, "배경 : %s", backgroundChoiceStr);

		TextOut(_hdcMapTool, 250, 200, backgroundChoiceStr2, strlen(backgroundChoiceStr2));

		char mapname[128] = "맵이름 입력";
		TextOut(_hdcMapTool, 30, 440, mapname, strlen(mapname));

		//char teststr[128] = "맵길이 :";
		//sprintf_s(teststr, "맵길이 : %s", mstr);

		//TextOut(_hdcMapTool, 30, 150, teststr, strlen(teststr));

		//
		//if (_buttonCount == 10)
		//{
		//	PostMessage(_hMapTool, WM_COMMAND, 999, 0); //_hMapTool의 WM_COMMAND 메시지 포스트 wParam에 999저장
		//}

		//IMAGEMANAGER->findImage("background_jail")->render()

		//==============================================================================================================
		//최종적으로 BackBuffer에서 hdc의 비트맵 도화지로 복사

		//this->getBackBufferMapTool()->render(_hdcMapTool, 0, 0); //백버퍼에서 hdc로 복사
	}
	else if (_mapToolOn == 2)
	{
		PatBlt(_backBufferMapTool->getMemDC(), 0, 0, WINSIZEX + 400, WINSIZEY, WHITENESS);
		//==============================================================================================================
		if (!strcmp(backgroundChoiceStr, "bg_jail_mini_02"))
		{
			IMAGEMANAGER->findImage("background_jail")->loopRender(_backBufferMapTool->getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _loopY);
		}
		else if (!strcmp(backgroundChoiceStr, "bg_city_mini_02"))
		{
			IMAGEMANAGER->findImage("background")->loopRender(_backBufferMapTool->getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _loopY);
		}
		//IMAGEMANAGER->findImage("object_box")->render(_backBufferMapTool->getMemDC(), 650, 20 + _scrollY*10);
		//IMAGEMANAGER->findImage("object_can")->render(_backBufferMapTool->getMemDC(), 650, 120 + _scrollY*10);
		//IMAGEMANAGER->findImage("object_greeen")->render(_backBufferMapTool->getMemDC(), 650, 220 + _scrollY*10);
		//IMAGEMANAGER->findImage("object_yellow")->render(_backBufferMapTool->getMemDC(), 650, 320 + _scrollY*10);
		//IMAGEMANAGER->findImage("테스트장애물")->render(_backBufferMapTool->getMemDC(), 650, 20 + _scrollY * 10);

		for (_4tupleiter = _4tuplesList.begin(); _4tupleiter != _4tuplesList.end(); ++_4tupleiter)
		{
			if (!((*_4tupleiter)->_isItem))
			{
				(*_4tupleiter)->_image->frameRender(_backBufferMapTool->getMemDC(), (*_4tupleiter)->_xycoordinate.x - ((*_4tupleiter)->_image->getFrameWidth() / 2), (*_4tupleiter)->_xycoordinate.y - ((*_4tupleiter)->_image->getFrameHeight() / 2) - _loopY, 0, 0);
			}
			else
			{
				(*_4tupleiter)->_image->frameRender(_backBufferMapTool->getMemDC(), (*_4tupleiter)->_xycoordinate.x - ((*_4tupleiter)->_image->getFrameWidth() / 2), (*_4tupleiter)->_xycoordinate.y - ((*_4tupleiter)->_image->getFrameHeight() / 2) - _loopY, ((_frameCount % 40) < 20) ? 0 : 1, 0);
			}
		}

		for (_bliter = _bList.begin(); _bliter != _bList.end(); ++_bliter)
		{
			(*_bliter).render(_backBufferMapTool->getMemDC());
		}

		for (_bliter = _itembList.begin(); _bliter != _itembList.end(); ++_bliter)
		{
			(*_bliter).render(_backBufferMapTool->getMemDC());
		}


		if (_isCurrentOn && _ptMouse.x <= WINSIZEX)
		{
			_currentImage->frameRender(_backBufferMapTool->getMemDC(), _ptMouse.x - (_currentImage->getFrameWidth() / 2), _ptMouse.y - (_currentImage->getFrameHeight() / 2), 0, 0);
		}

		if (_erasefbool && _ptMouse.x <= WINSIZEX)
		{
			if (_isErasing)
			{
				_currentImage->frameRender(_backBufferMapTool->getMemDC(), _ptMouse.x, _ptMouse.y, ((TIMEMANAGER->getFrameCount() % 10) < 5) ? 0 : 1, 0);
			}
			else
			{
				_currentImage->frameRender(_backBufferMapTool->getMemDC(), _ptMouse.x, _ptMouse.y, 0, 0);
			}
		}

		_saveB->render(_backBufferMapTool->getMemDC());
		_loadB->render(_backBufferMapTool->getMemDC());
		_clearB->render(_backBufferMapTool->getMemDC());
		_eraseB->render(_backBufferMapTool->getMemDC());

		//==============================================================================================================
		_backBufferMapTool->render(_hdcMapTool, 0, 0);
	}
}

void MapToolScene::loadMap(vector<string> data)
{
	_mapData = data;
	strcpy_s(backgroundChoiceStr, data[0].c_str());
	mint = stoi(data[1]);

	for (_4tupleiter = _4tuplesList.begin(); _4tupleiter != _4tuplesList.end(); ++_4tupleiter)
	{
		SAFE_DELETE(*_4tupleiter);
	}
	_4tuplesList.clear();

	for (int i = 2; i < data.size() - 1;)
	{
		newObjectData* temp = new newObjectData;
		temp->_isItem = stoi(data[i + 1]);
		if (temp->_isItem)
		{
			temp->_imageName = _itemList[stoi(data[i]) * 3];
		}
		else
		{
			temp->_imageName = _obList[stoi(data[i]) * 3];
		}		
		temp->_image = IMAGEMANAGER->findImage(temp->_imageName);
		temp->_xycoordinate.x = stoi(data[i + 2]);
		temp->_xycoordinate.y = stoi(data[i + 3]);
		

		_4tuplesList.push_back(temp);

		i = i + 4;
	}
}

void MapToolScene::mtLoadMap()
{
	strcpy_s(backgroundChoiceStr, _mapData[0].c_str());
	mint = stoi(_mapData[1]);

	for (_4tupleiter = _4tuplesList.begin(); _4tupleiter != _4tuplesList.end(); ++_4tupleiter)
	{
		SAFE_DELETE(*_4tupleiter);
	}
	_4tuplesList.clear();

	for (int i = 2; i < _mapData.size() - 1;)
	{
		newObjectData* temp = new newObjectData;

		temp->_isItem = stoi(_mapData[i + 1]);

		if (temp->_isItem)
		{
			temp->_imageName = _itemList[stoi(_mapData[i]) * 3];
		}
		else
		{
			temp->_imageName = _obList[stoi(_mapData[i]) * 3];
		}
		
		temp->_image = IMAGEMANAGER->findImage(temp->_imageName);

		temp->_xycoordinate.x = stoi(_mapData[i + 2]);
		temp->_xycoordinate.y = stoi(_mapData[i + 3]);
		

		_4tuplesList.push_back(temp);

		i = i + 4;
	}
}

void MapToolScene::cityButton(void)
{
	RECT clearbox = RectMake(250, 200, 500, 100);
	InvalidateRect(_hMapTool, &clearbox, true);
	strcpy_s(backgroundChoiceStr, "bg_city_mini_02");
}

void MapToolScene::jailButton(void)
{
	RECT clearbox = RectMake(250, 200, 500, 100);
	InvalidateRect(_hMapTool, &clearbox, true);
	strcpy_s(backgroundChoiceStr, "bg_jail_mini_02");
}

void MapToolScene::obButton(int imageNumber)
{
	bool check;
	vector<string> temp = TXTDATA->txtLoadExt("장애물 목록.txt", 1024, &check);
	_currentImageName = temp[imageNumber];
	_currentImage = IMAGEMANAGER->findImage(_currentImageName);
	_isCurrentOn = true;
	_isItemnow = false;
	_erasefbool = false;
}

void MapToolScene::itemButton(int imageNumber)
{
	bool check;
	vector<string> temp = TXTDATA->txtLoadExt("아이템 목록.txt", 1024, &check);
	_currentImageName = temp[imageNumber];
	_currentImage = IMAGEMANAGER->findImage(_currentImageName);
	_isCurrentOn = true;
	_isItemnow = true;
	_erasefbool = false;
}

void MapToolScene::saveButton(void)
{
	_savefbool = true;
}

void MapToolScene::loadButton(void)
{
	_loadfbool = true;
}

void MapToolScene::clearButton(void)
{
	_clearfbool = true;
}

void MapToolScene::eraseButton(void)
{
	_currentImage = IMAGEMANAGER->findImage("지우개");
	_isCurrentOn = false;
	_erasefbool = true;
}

void MapToolScene::mapSave()
{
	//y좌표 크기순으로 정렬하는거 만들기
	//임시
	for (_4tupleiter = _rearrangedList.begin(); _4tupleiter != _rearrangedList.end(); ++_4tupleiter)
	{
		SAFE_DELETE(*_4tupleiter);
	}
	_rearrangedList.clear();
	for (_4tupleiter = _4tuplesList.begin(); _4tupleiter != _4tuplesList.end(); ++_4tupleiter)
	{
		newObjectData* temp = new newObjectData;

		temp->_isItem = (*_4tupleiter)->_isItem;

		if (temp->_isItem)
		{
			for (int i = 0; i < _itemList.size() - 1;)
			{
				if (_itemList[i].compare((*_4tupleiter)->_imageName) == 0)
				{
					temp->_imageName = to_string(i / 3);
					break;
				}
				++i;
				++i;
				++i;
			}
		}
		else
		{
			for (int i = 0; i < _obList.size() - 1;)
			{
				if (_obList[i].compare((*_4tupleiter)->_imageName) == 0)
				{
					temp->_imageName = to_string(i / 3);
					break;
				}
				++i;
				++i;
				++i;
			}
		}

		temp->_image = (*_4tupleiter)->_image;
		temp->_xycoordinate.x = (*_4tupleiter)->_xycoordinate.x;
		temp->_xycoordinate.y = (*_4tupleiter)->_xycoordinate.y;
		
		_rearrangedList.push_back(temp);
	}

	vector<string> toSave;

	//배경
	string bg = backgroundChoiceStr;
	toSave.push_back(bg);
	//맵길이
	toSave.push_back(to_string(mint));

	//오브젝트 저장
	for (_4tupleiter = _rearrangedList.begin(); _4tupleiter != _rearrangedList.end(); ++_4tupleiter)
	{
		toSave.push_back((*_4tupleiter)->_imageName);
		toSave.push_back(to_string(((*_4tupleiter)->_isItem) ? 1 : 0));
		toSave.push_back(to_string((*_4tupleiter)->_xycoordinate.x));
		toSave.push_back(to_string((*_4tupleiter)->_xycoordinate.y));	
	}

	toSave.push_back("더미"); //txtLoad가 마지막칸 에러를 일으키므로 더미 데이터 하나 넣어주기

	string nametemp = _mapname + ".txt";
	
	_mapData = toSave;

	TXTDATA->txtSaveExt(nametemp.c_str(), toSave, TXTSIZE);
}