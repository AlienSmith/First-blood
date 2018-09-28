#pragma once
#ifndef GAMEH
#define GAMEH
#include "Monster.h"
class Game {
public:
	Game();
	~Game();
	static char info1[];
	static char info2[];
	static char info3[];
	static char info4[];
	static int monsterlifetime;
	static int time;
	static int playersy;
	static int playersx;
	bool flag;
	GStar::Vector2 Playerposition;
	static int playerspeed;
	//TODO question why make playername list autoallocate will lead to error?
	GStar::SingleLinkedList<char>* PlayerName;
	GStar::SingleLinkedList<Monster*>* MonsterList;
	void Addmonster(int numbers);
	void AddNewmonster();
	void Update();
	void Draw();
	void GetPlayerName();
	void Initialize();
	void InitializeMonsters();
	void PlayerInput();
};
#endif // GAMEH
