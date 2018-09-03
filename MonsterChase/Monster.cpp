#include "Monster.h"
#include <stdio.h>
int Monster::count = 0;
int Monster::speed = 1;

Monster::Monster()
{
}

Monster::Monster(int lifetime)
{
	previous = nullptr;
	after = nullptr;
	count++;
	this->lifetime = lifetime;
	this->postionx = count%10 + count%3;
	this->positiony = count%10 + count % 14;
	this->mynumber = Monster::count;
}

void Monster::Update(int x, int y, int time)
{
	this->CheckLife(time);
	this->MoveTo(x, y);
}

void Monster::MoveTo(int x, int y)
{
	if (x > this->postionx) {
		this->postionx += speed;
	}
	else if (x < this->postionx) {
		this->postionx -= speed;
	}
	if (y > this->positiony) {
		this->positiony += speed;
	}
	else if (y < this->positiony) {
		this->positiony -= speed;
	}
}

void Monster::CheckLife(int time)
{
	if (time > this->lifetime) {
		(*previous).after = this->after;
		if (after != nullptr) {
			(*after).previous = this->previous;
		}
	}
}

void Monster::Print()
{
	printf("%s%i is at (%i,%i)\n", this->monstername, this->mynumber,this->postionx, this->positiony);
}
