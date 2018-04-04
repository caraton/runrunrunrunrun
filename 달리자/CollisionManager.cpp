#include "stdafx.h"
#include "CollisionManager.h"
#include "player.h"

HRESULT CollisionManager::init(int maplength)
{
	if (_hashTable.size() != 0)
	{
		//�����Ҵ� ����
		for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
		{
			SAFE_DELETE(*_vecIter);
		}

		_hashTable.clear();
	}

	_mapLength = maplength;
	_mapLengthMinusWINSIZEY = maplength - WINSIZEY;
	//�ؽ����̺� �� ��Ʈ���� ����Ʈ�� �����Ҵ��Ͽ� �ּҸ� ����
	for (int i = 0; i < (_mapLength / 10); ++i) //(WINSIZEY/10)�� �۷ι� �� Y���̷� �����ϱ�
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
	//�ؽ����̺� ���� ����Ʈ�� �ʱ�ȭ
	for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
	{
		(*_vecIter)->clear();
	}

	//irList�� ir���� �ٽ� �ؽ����̺� ����
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
	////ir�� RECT���� ������
	//if (ir->_rc == 0)??
	//{
	//	return NULL;
	//}

	//ir�� top�� bottom�� h()�� �ֱ�
	int temp1 = (ir->_rc.top + _mapLengthMinusWINSIZEY) / 10;
	int temp2 = (ir->_rc.bottom + _mapLengthMinusWINSIZEY) / 10;

	//top�� bottom ���̿� �ش��ϴ� ��� �ؽ����̺� ��Ʈ���� ����Ʈ�� ir ����
	for (int i = temp1; i <= temp2; ++i)
	{
		_hashTable[i]->push_back(ir);
	}

	return ir;
}

IR * CollisionManager::addIR(IR * ir)
{
	internalAddIR(ir);

	_irList.push_back(ir); //irList���� �����صξ��ٰ� update���� �ʱ�ȭ�� �ٽ� ��������� ���

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
		//} list ��ü �����Լ� remove ����ϱ�

		_hashTable[i]->remove(ir);
	}

	_irList.remove(ir);
}

//void CollisionManager::clearTable()
//{
//	//�ؽ����̺� ���� ����Ʈ�� �ʱ�ȭ
//	for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
//	{
//		(*_vecIter)->clear();
//	}
//
//	//irList�� ir���� �ٽ� �ؽ����̺� ����
//	for (_iter = _irList.begin(); _iter != _irList.end(); ++_iter)
//	{
//		internalAddIR(*_iter);
//	}
//}

bool CollisionManager::findIRNear(IR* ir, OUT vector<IR*>* IRList)
{
	//ir�� top, bottom �� h()�� ����
	int temp1 = ((ir->_rc.top + _mapLengthMinusWINSIZEY) / 10) - 3;
	int temp2 = ((ir->_rc.bottom + _mapLengthMinusWINSIZEY) / 10) + 3;


	RECT irRC30 = { ir->_rc.left - 30, ir->_rc.top - 30, ir->_rc.right + 30, ir->_rc.bottom + 30 };
	RECT tempRECT;

	//%%temp1~temp2���� �ؽ����̺� �����Ͽ� �� ���� ����Ʈ���� ��ȸ
	for (int i = temp1; i <= temp2; ++i)
	{
		for (_iter = _hashTable[i]->begin(); _iter != _hashTable[i]->end(); ++_iter)
		{
			if (ir == (*_iter)) //�ڱ��ڽ��̸� �н�
			{
				continue;
			}
			if (i != temp1 && (((*_iter)->_rc.top + _mapLengthMinusWINSIZEY) / 10) <= i-1)
			{//�̹� ���� i-1���� �߰��Ǿ��� ��� ����Ʈ�� �ߺ��ؼ� ���� �ʰ� continue
				continue;
			}
			if (IntersectRect(&tempRECT, &irRC30, &((*_iter)->_rc))) //RECT �浹
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
	//ir�� top, bottom �� h()�� ����
	int temp1 = (ir->_rc.top + _mapLengthMinusWINSIZEY) / 10;
	int temp2 = (ir->_rc.bottom + _mapLengthMinusWINSIZEY) / 10;

	//%%temp1~temp2���� �ؽ����̺� �����Ͽ� �� ���� ����Ʈ���� ��ȸ
	for (int i = temp1; i <= temp2; ++i)
	{
		for (_iter = _hashTable[i]->begin(); _iter != _hashTable[i]->end(); ++_iter)
		{
			if (ir == (*_iter)) //�ڱ��ڽ��̸� �н�
			{
				continue;
			}
			if (i != temp1 && (((*_iter)->_rc.top + _mapLengthMinusWINSIZEY) / 10) <= i - 1)
			{//�̹� ���� i-1���� �߰��Ǿ��� ��� ����Ʈ�� �ߺ��ؼ� ���� �ʰ� continue
				continue;
			}
			if (pixelCol(ir, *_iter)) //�ȼ��浹üũ
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
	//�����Ҵ� ����
	for (_vecIter = _hashTable.begin(); _vecIter != _hashTable.end(); ++_vecIter)
	{
		SAFE_DELETE(*_vecIter);
	}

	_hashTable.clear();
}
