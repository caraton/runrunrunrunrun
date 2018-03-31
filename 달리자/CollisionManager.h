#pragma once
#include "singletonBase.h"
#include "gameNode.h"
#include <vector>
#include <list>

class player;

class CollisionManager : public gameNode
{
private:
	vector<list<IR*>*> _hashTable; //y축을 10단위로 쪼개서 저장할 테이블
	//h(y좌표) = y좌표 + _mapLengthMinusWINSIZEY / 10인 간단한 해쉬함수 사용 (0~9 -> 0, 10~19-> 1, ..., 420~429->42, ....)
	//_hashTable[y좌표 + _mapLengthMinusWINSIZEY /10]으로 간단하게 내부에 접근가능
	vector<list<IR*>*>::iterator _vecIter; //테이블을 돌 이터레이터
	list<IR*> _irList; //모든 ir을 모아서 매 업데이트 마다 수정할때 사용
	list<IR*>::iterator _iter; //테이블의 한 줄안의 리스트를 순회하기 위한 이터레이터

	player* _player;

	SYNTHESIZE(int, _mapLength, MapLength);
	int _mapLengthMinusWINSIZEY; //y좌표를 받아서 이값을 더한 후에 /10을 하면 해쉬값이 나온다

	//bool _gameover;
	SYNTHESIZE(bool, _gameover, Gameover);

	IR* internalAddIR(IR* ir); //내부에서만 사용할 ir추가함수

public:
	virtual HRESULT init(int maplength);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	IR* addIR(IR* ir); //IR들을 받아서 해쉬 테이블에 저장
	void deleteIR(IR* ir); //IR을 찾아서 해쉬테이블에서 삭제

	bool findIRNear(IR* ir, OUT vector<IR*>* IRList); //해쉬 테이블에서 ir의 주변 물체가 있는지 찾아서 IRList에 저장
	bool checkCollision(IR* ir, OUT vector<IR*>* colList); //해쉬 테이블에서 ir의 주변 물체가 있는지 찾아서 픽셀충돌을 체크한 후 colList에 저장

	void linkPlayer(player* player) { _player = player; }

	CollisionManager();
	~CollisionManager();
};