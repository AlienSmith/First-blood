#include "Monster.h"
#include <stdio.h>
#include <iostream>
int Monster::count = 0;
int Monster::speed = 1;
int Monster::lifespan = 1;
//take the head pointer of the list.
void Monster::printlist(GStar::SingleLinkedListNode<char>* temper)
{
	GStar::SingleLinkedListNode<char>* temp = temper;
	temp = temp->GetNext();
	while (temp != nullptr) {
		printf("%c", temp->GetData());
		temp = temp->GetNext();
	}
}

Monster::Monster()
{
}

Monster::~Monster()
{
	delete MonsterName;
}

Monster::Monster(int lifetime)
{
	this->MonsterName = new GStar::SingleLinkedList<char>();
	count++;
	this->lifetime = lifetime;
	this->m_position = GStar::Vector2(count % 10 + count % 3, count % 10 + count % 14);
	this->mynumber = Monster::count;
	this->GetName();
}

void Monster::Update(GStar::Vector2 position, int time)
{
	this->CheckLife(time);
	this->MoveTo(position);
}

void Monster::MoveTo(GStar::Vector2 position)
{
	GStar::Vector2 temp = position - this->m_position;
	temp.Normalize();
	this->m_position += (Monster::speed*temp);
}

bool Monster::CheckLife(int time)
{
	if (this->lifetime < time) {
		return false;
	}
	return true;
}

void Monster::Print()
{
	GStar::SingleLinkedListNode<char>* temp = this->MonsterName->GetHead();
	temp = temp->GetNext();
	while (temp != nullptr) {
		printf("%c", temp->GetData());
		temp = temp->GetNext();
	}
	printf(" is at (%f,%f)\n",this->m_position.x(), this->m_position.y());
}

void Monster::GetName()
{
	printf("Please enter name for monster %i end with \".\" \n", this->mynumber );
	char next;
	std::cin >> next;
	while (next != '.') {
		this->MonsterName->Push(next);
		std::cin >> next;
	}
	this->MonsterName->Push('\0');
}
