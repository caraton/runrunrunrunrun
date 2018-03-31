#pragma once
#include "singletonBase.h"
#include "gameNode.h"
#include <vector>
#include <list>

class player;

class CollisionManager : public gameNode
{
private:
	vector<list<IR*>*> _hashTable; //y���� 10������ �ɰ��� ������ ���̺�
	//h(y��ǥ) = y��ǥ + _mapLengthMinusWINSIZEY / 10�� ������ �ؽ��Լ� ��� (0~9 -> 0, 10~19-> 1, ..., 420~429->42, ....)
	//_hashTable[y��ǥ + _mapLengthMinusWINSIZEY /10]���� �����ϰ� ���ο� ���ٰ���
	vector<list<IR*>*>::iterator _vecIter; //���̺��� �� ���ͷ�����
	list<IR*> _irList; //��� ir�� ��Ƽ� �� ������Ʈ ���� �����Ҷ� ���
	list<IR*>::iterator _iter; //���̺��� �� �پ��� ����Ʈ�� ��ȸ�ϱ� ���� ���ͷ�����

	player* _player;

	SYNTHESIZE(int, _mapLength, MapLength);
	int _mapLengthMinusWINSIZEY; //y��ǥ�� �޾Ƽ� �̰��� ���� �Ŀ� /10�� �ϸ� �ؽ����� ���´�

	//bool _gameover;
	SYNTHESIZE(bool, _gameover, Gameover);

	IR* internalAddIR(IR* ir); //���ο����� ����� ir�߰��Լ�

public:
	virtual HRESULT init(int maplength);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	IR* addIR(IR* ir); //IR���� �޾Ƽ� �ؽ� ���̺� ����
	void deleteIR(IR* ir); //IR�� ã�Ƽ� �ؽ����̺��� ����

	bool findIRNear(IR* ir, OUT vector<IR*>* IRList); //�ؽ� ���̺��� ir�� �ֺ� ��ü�� �ִ��� ã�Ƽ� IRList�� ����
	bool checkCollision(IR* ir, OUT vector<IR*>* colList); //�ؽ� ���̺��� ir�� �ֺ� ��ü�� �ִ��� ã�Ƽ� �ȼ��浹�� üũ�� �� colList�� ����

	void linkPlayer(player* player) { _player = player; }

	CollisionManager();
	~CollisionManager();
};