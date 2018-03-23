#include "stdafx.h"
#include "CollisionManager.h"
#include "player.h"

HRESULT CollisionManager::init(void)
{
	//해쉬테이블 각 엔트리에 리스트를 동적할당하여 주소를 저장
	for (int i = 0; i < (WINSIZEY / 10); ++i) //(WINSIZEY/10)는 글로벌 총 Y길이로 수정하기
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
	//_player와 해쉬테이블 안의 오브젝트들 간의 충돌확인
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
	//for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
	//{
	//	for (_iter = (*(_vecIter))->begin(); _iter != (*(_vecIter))->end(); ++_iter)
	//	{
	//		(*_iter)->_image->render(getMemDC(), (*_iter)->_rc.left, (*_iter)->_rc.top);
	//	}
	//}
}

IR * CollisionManager::addIR(IR * ir)
{
	////ir의 RECT값이 없으면
	//if (ir->_rc == 0)??
	//{
	//	return NULL;
	//}

	//ir의 top과 bottom을 h()에 넣기
	int temp1 = ir->_rc.top / 10;
	int temp2 = ir->_rc.bottom / 10;

	//top과 bottom 사이에 해당하는 모든 해쉬테이블 엔트리안 리스트에 ir 저장
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
	//ir의 top, bottom 그리고 중점을 h()에 대입
	int temp1 = (ir->_rc.top / 10) - 3;
	int temp2 = (ir->_rc.bottom / 10) + 3;


	RECT irRC30 = { ir->_rc.left - 30, ir->_rc.top - 30, ir->_rc.right + 30, ir->_rc.bottom + 30 };
	RECT tempRECT;

	//%%temp1~temp2으로 해쉬테이블에 접근하여 그 안의 리스트들을 순회
	for (int i = temp1; i <= temp2; ++i)
	{
		for (_iter = _hashTable[i]->begin(); _iter != _hashTable[i]->end(); ++_iter)
		{
			if (i != temp1 && ((*_iter)->_rc.top / 10) <= i-1) 
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
	//ir의 top, bottom 그리고 중점을 h()에 대입
	int temp1 = ir->_rc.top / 10;
	int temp2 = ir->_rc.bottom / 10; 

	//%%temp1~temp3으로 해쉬테이블에 접근하여 그 안의 리스트들을 순회
	for (int i = temp1; i <= temp2; ++i)
	{
		for (_iter = _hashTable[i]->begin(); _iter != _hashTable[i]->end(); ++_iter)
		{
			if (i != temp1 && ((*_iter)->_rc.top / 10) <= i - 1)
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
