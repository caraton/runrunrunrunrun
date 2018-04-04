#include "stdafx.h"
#include "CollisionManager.h"
#include "player.h"

HRESULT CollisionManager::init(int maplength)
{
	if (_hashTable.size() != 0)
	{
		//동적할당 해제
		for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
		{
			SAFE_DELETE(*_vecIter);
		}

		_hashTable.clear();
	}

	_mapLength = maplength;
	_mapLengthMinusWINSIZEY = maplength - WINSIZEY;
	//해쉬테이블 각 엔트리에 리스트를 동적할당하여 주소를 저장
	for (int i = 0; i < (_mapLength / 10); ++i) //(WINSIZEY/10)는 글로벌 총 Y길이로 수정하기
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
	//해쉬테이블 안의 리스트들 초기화
	for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
	{
		(*_vecIter)->clear();
	}

	//irList의 ir들을 다시 해쉬테이블에 저장
	for (_iter = _irList.begin(); _iter != _irList.end(); ++_iter)
	{
		internalAddIR(*_iter);
	}
}

void CollisionManager::render()
{
	//for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
	//{
	//	for (_iter = (*(_vecIter))->begin(); _iter != (*(_vecIter))->end(); ++_iter)
	//	{
	//		(*_iter)->_image->render(getMemDC(), (*_iter)->_rc.left, (*_iter)->_rc.top);
	//	}
	//}
}

IR* CollisionManager::internalAddIR(IR* ir)
{
	////ir의 RECT값이 없으면
	//if (ir->_rc == 0)??
	//{
	//	return NULL;
	//}

	//ir의 top과 bottom을 h()에 넣기
	int temp1 = (ir->_rc.top + _mapLengthMinusWINSIZEY) / 10;
	int temp2 = (ir->_rc.bottom + _mapLengthMinusWINSIZEY) / 10;

	//top과 bottom 사이에 해당하는 모든 해쉬테이블 엔트리안 리스트에 ir 저장
	for (int i = temp1; i <= temp2; ++i)
	{
		_hashTable[i]->push_back(ir);
	}

	return ir;
}

IR * CollisionManager::addIR(IR * ir)
{
	internalAddIR(ir);

	_irList.push_back(ir); //irList에도 저장해두었다가 update에서 초기화후 다시 집어넣을때 사용

	return ir;
}

void CollisionManager::deleteIR(IR * ir)
{
	int temp1 = (ir->_rc.top + _mapLengthMinusWINSIZEY) / 10;
	int temp2 = (ir->_rc.bottom + _mapLengthMinusWINSIZEY) / 10;
	for (int i = temp1; i <= temp2; ++i)
	{
		//for (_iter = _hashTable[i]->begin(); _iter != _hashTable[i]->end(); )
		//{
		//	if (*_iter == ir)
		//	{
		//		_hashTable[i]->erase(_iter);
		//		break;
		//	}
		//	else
		//	{
		//		++_iter;
		//	}
		//} list 자체 제공함수 remove 사용하기

		_hashTable[i]->remove(ir);
	}

	_irList.remove(ir);
}

//void CollisionManager::clearTable()
//{
//	//해쉬테이블 안의 리스트들 초기화
//	for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
//	{
//		(*_vecIter)->clear();
//	}
//
//	//irList의 ir들을 다시 해쉬테이블에 저장
//	for (_iter = _irList.begin(); _iter != _irList.end(); ++_iter)
//	{
//		internalAddIR(*_iter);
//	}
//}

bool CollisionManager::findIRNear(IR* ir, OUT vector<IR*>* IRList)
{
	//ir의 top, bottom 을 h()에 대입
	int temp1 = ((ir->_rc.top + _mapLengthMinusWINSIZEY) / 10) - 3;
	int temp2 = ((ir->_rc.bottom + _mapLengthMinusWINSIZEY) / 10) + 3;


	RECT irRC30 = { ir->_rc.left - 30, ir->_rc.top - 30, ir->_rc.right + 30, ir->_rc.bottom + 30 };
	RECT tempRECT;

	//%%temp1~temp2으로 해쉬테이블에 접근하여 그 안의 리스트들을 순회
	for (int i = temp1; i <= temp2; ++i)
	{
		for (_iter = _hashTable[i]->begin(); _iter != _hashTable[i]->end(); ++_iter)
		{
			if (ir == (*_iter)) //자기자신이면 패스
			{
				continue;
			}
			if (i != temp1 && (((*_iter)->_rc.top + _mapLengthMinusWINSIZEY) / 10) <= i-1)
			{//이미 이전 i-1에서 추가되었을 경우 리스트에 중복해서 넣지 않고 continue
				continue;
			}
			if (IntersectRect(&tempRECT, &irRC30, &((*_iter)->_rc))) //RECT 충돌
			{
				IRList->push_back(*_iter);
			}
		}
	}

	if (IRList->size() == 0)
	{
		return false;
	}
	//%%

	return true;
}

bool CollisionManager::checkCollision(IR * ir, OUT vector<IR*>* colList)
{
	//ir의 top, bottom 을 h()에 대입
	int temp1 = (ir->_rc.top + _mapLengthMinusWINSIZEY) / 10;
	int temp2 = (ir->_rc.bottom + _mapLengthMinusWINSIZEY) / 10;

	//%%temp1~temp2으로 해쉬테이블에 접근하여 그 안의 리스트들을 순회
	for (int i = temp1; i <= temp2; ++i)
	{
		for (_iter = _hashTable[i]->begin(); _iter != _hashTable[i]->end(); ++_iter)
		{
			if (ir == (*_iter)) //자기자신이면 패스
			{
				continue;
			}
			if (i != temp1 && (((*_iter)->_rc.top + _mapLengthMinusWINSIZEY) / 10) <= i - 1)
			{//이미 이전 i-1에서 추가되었을 경우 리스트에 중복해서 넣지 않고 continue
				continue;
			}
			if (pixelCol(ir, *_iter)) //픽셀충돌체크
			{
				colList->push_back(*_iter);
			}
		}
	}
	//%%

	if (colList->size() == 0)
	{
		return false;
	}

	return true;
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
