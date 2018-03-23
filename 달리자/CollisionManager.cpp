#include "stdafx.h"
#include "CollisionManager.h"
#include "player.h"

HRESULT CollisionManager::init(void)
{
	//�ؽ����̺� �� ��Ʈ���� ����Ʈ�� �����Ҵ��Ͽ� �ּҸ� ����
	for (int i = 0; i < (WINSIZEY / 10); ++i) //(WINSIZEY/10)�� �۷ι� �� Y���̷� �����ϱ�
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
	//_player�� �ؽ����̺� ���� ������Ʈ�� ���� �浹Ȯ��
	vector<IR*>* temp = new vector<IR*>;
	if (checkCollision(&(_player->GetIR()),temp))
	{
		//�÷��̾ �浹����
		_gameover = true;
	}

	//�پ� temp ����
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
	////ir�� RECT���� ������
	//if (ir->_rc == 0)??
	//{
	//	return NULL;
	//}

	//ir�� top�� bottom�� h()�� �ֱ�
	int temp1 = ir->_rc.top / 10;
	int temp2 = ir->_rc.bottom / 10;

	//top�� bottom ���̿� �ش��ϴ� ��� �ؽ����̺� ��Ʈ���� ����Ʈ�� ir ����
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
	//ir�� top, bottom �׸��� ������ h()�� ����
	int temp1 = (ir->_rc.top / 10) - 3;
	int temp2 = (ir->_rc.bottom / 10) + 3;


	RECT irRC30 = { ir->_rc.left - 30, ir->_rc.top - 30, ir->_rc.right + 30, ir->_rc.bottom + 30 };
	RECT tempRECT;

	//%%temp1~temp2���� �ؽ����̺� �����Ͽ� �� ���� ����Ʈ���� ��ȸ
	for (int i = temp1; i <= temp2; ++i)
	{
		for (_iter = _hashTable[i]->begin(); _iter != _hashTable[i]->end(); ++_iter)
		{
			if (i != temp1 && ((*_iter)->_rc.top / 10) <= i-1) 
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
	//ir�� top, bottom �׸��� ������ h()�� ����
	int temp1 = ir->_rc.top / 10;
	int temp2 = ir->_rc.bottom / 10; 

	//%%temp1~temp3���� �ؽ����̺� �����Ͽ� �� ���� ����Ʈ���� ��ȸ
	for (int i = temp1; i <= temp2; ++i)
	{
		for (_iter = _hashTable[i]->begin(); _iter != _hashTable[i]->end(); ++_iter)
		{
			if (i != temp1 && ((*_iter)->_rc.top / 10) <= i - 1)
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
