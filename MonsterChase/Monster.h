#pragma 
#include "SingleLinkedList.h"
#include "Vector2.h"
#ifndef MONSTERH
#define MONSTERH
class Monster {
public:
	static void printlist(GStar::SingleLinkedListNode<char>* temp);
	static int count;
	static int speed;
	static int lifespan;
	GStar::SingleLinkedList<char>* MonsterName;
	int mynumber;
	GStar::Vector2 m_position;
	int lifetime;
	Monster();
	~Monster();
	Monster(int lifetime);
	void Update(GStar::Vector2 position, int time);
	void MoveTo(GStar::Vector2 position);
	bool CheckLife(int time);
	void Print();
	void GetName();
};
#endif
