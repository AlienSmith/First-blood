#pragma once
#ifndef GAMEH
#define GAMEH
#include "Monster.h"
#include <stdio.h>
#include <iostream>
class Game {
public:
	static char info1[];
	static char info2[];
	static char info3[];
	static char info4[];
	static int monsterlifetime;
	static int time;
	static int playersx;
	static int playersy;
	static int playerspeed;
	char PlayerName[10];
	Monster* start;
	int playerx;
	int palyery;
	Game();
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
