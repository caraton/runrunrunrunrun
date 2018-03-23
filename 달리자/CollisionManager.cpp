#include "stdafx.h"
#include "CollisionManager.h"
#include "player.h"

HRESULT CollisionManager::init(void)
{
	for (int i = 0; i < (WINSIZEY / 10); ++i) //(WINSIZEY/100)는 글로벌 총 Y길이로 수정하기
	{
		list<IR*>* templist = new list<IR*>();
		_hashTable.push_back(templist);
	}

	_gameover = false;

	return S_OK;
}

void CollisionManager::release(void)
{
}

void CollisionManager::update(void)
{
	vector<IR*>* temp = new vector<IR*>;
	if (checkCollision(&(_player->GetIR()),temp))
	{
		//플레이어가 충돌했음
		_gameover = true;
	}

	//다쓴 temp 삭제
	SAFE_DELETE(temp);
}

void CollisionManager::render()
{
	for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
	{
		for (_iter = (*(_vecIter))->begin(); _iter != (*(_vecIter))->end(); ++_iter)
		{
			(*_iter)->_image->render(getMemDC(), (*_iter)->_rc.left, (*_iter)->_rc.top);
		}
	}
}

IR * CollisionManager::addIR(IR * ir)
{
	////ir의 RECT값이 없으면
	//if (ir->_rc == 0)??
	//{
	//	return NULL;
	//}
	int temp1 = ir->_rc.top / 10;
	int temp2 = ir->_rc.bottom / 10;

	for (int i = temp1; i <= temp2; ++i)
	{
		_hashTable[i]->push_back(ir);
	}
	return ir;
}

void CollisionManager::deleteIR(IR * ir)
{
	int temp1 = ir->_rc.top / 10;
	int temp2 = ir->_rc.bottom / 10;
	for (int i = temp1; i <= temp2; ++i)
	{
		for (_iter = _hashTable[i]->begin(); _iter != _hashTable[i]->end(); )
		{
			if (*_iter == ir)
			{
				_hashTable[i]->erase(_iter);
				break;
			}
			else
			{
				++_iter;
			}
		}
	}
}

bool CollisionManager::findIRNear(IR* ir, OUT vector<IR*>* IRList)
{
	int temp1 = ir->_rc.top / 10;
	int temp2 = ir->_rc.bottom / 10;
	int temp3 = ((ir->_rc.top + ir->_rc.bottom)/ 2) / 10; //y축으로 얇은 물체 있을 경우 플레이어 중간부분도 체크하기

	//vector<IR*> tempVector;

	for (_iter = _hashTable[temp1]->begin(); _iter != _hashTable[temp1]->end(); ++_iter)
	{
		if (((*_iter)->_rc.left + (*_iter)->_rc.right)/2 >= (ir->_rc.left-30) && ((*_iter)->_rc.left + (*_iter)->_rc.right) / 2 <= (ir->_rc.right + 30)) //x좌표도 확인해서 x,y 좌표 모두 가까우면
		{
			IRList->push_back(*_iter);
		}
	}

	if (temp2 != temp3)
	{
		for (_iter = _hashTable[temp2]->begin(); _iter != _hashTable[temp2]->end(); ++_iter)
		{
			if (((*_iter)->_rc.left + (*_iter)->_rc.right) / 2 >= (ir->_rc.left - 30) && ((*_iter)->_rc.left + (*_iter)->_rc.right) / 2 <= (ir->_rc.right + 30)) //x좌표도 확인해서 x,y 좌표 모두 가까우면
			{
				IRList->push_back(*_iter);
			}
		}
	}

	if (temp3 != temp1)
	{
		for (_iter = _hashTable[temp3]->begin(); _iter != _hashTable[temp3]->end(); ++_iter)
		{
			if (((*_iter)->_rc.left + (*_iter)->_rc.right) / 2 >= (ir->_rc.left - 30) && ((*_iter)->_rc.left + (*_iter)->_rc.right) / 2 <= (ir->_rc.right + 30)) //x좌표도 확인해서 x,y 좌표 모두 가까우면
			{
				IRList->push_back(*_iter);
			}
		}
	}

	if (IRList->size() == 0)
	{
		return false;
	}

	//(*IRList) = tempVector;

	return true;
}

bool CollisionManager::checkCollision(IR * ir, OUT vector<IR*>* colList)
{
	int temp1 = ir->_rc.top / 10;
	int temp2 = ir->_rc.bottom / 10;
	int temp3 = ((ir->_rc.top + ir->_rc.bottom) / 2) / 10; //y축으로 얇은 물체 있을 경우 플레이어 중간부분도 체크하기

	//vector<IR*> tempVector;
	bool tempbool = false;

	for (_iter = _hashTable[temp1]->begin(); _iter != _hashTable[temp1]->end(); ++_iter)
	{
		if (pixelCol(ir, *_iter)) //픽셀충돌체크
		{
			tempbool = true;
			colList->push_back(*_iter);
		}
	}
	if (temp2 != temp3)
	{
		for (_iter = _hashTable[temp2]->begin(); _iter != _hashTable[temp2]->end(); ++_iter)
		{
			if (pixelCol(ir, *_iter)) //픽셀충돌체크
			{
				tempbool = true;
				colList->push_back(*_iter);
			}
		}
	}
	if (temp3 != temp1)
	{
		for (_iter = _hashTable[temp3]->begin(); _iter != _hashTable[temp3]->end(); ++_iter)
		{
			if (pixelCol(ir, *_iter)) //픽셀충돌체크
			{
				tempbool = true;
				colList->push_back(*_iter);
			}
		}
	}

	//*colList = tempVector;

	return tempbool;
}

CollisionManager::CollisionManager()
{
	_player = NULL;
}

CollisionManager::~CollisionManager()
{
	//동적할당 해제
	for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
	{
		SAFE_DELETE(*_vecIter);
	}

	_hashTable.clear();
}
