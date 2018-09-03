#pragma 
#ifndef MONSTERH
#define MONSTERH
class Monster {
public:
	static int count;
	static int speed;
	Monster* previous;
	Monster* after;
	char monstername[10] = "monster";
	int mynumber;
	int postionx;
	int positiony;
	int lifetime;
	Monster();
	Monster(int lifetime);
	void Update(int x, int y, int time);
	void MoveTo(int x, int y);
	void CheckLife(int time);
	void Print();
};
#endif
