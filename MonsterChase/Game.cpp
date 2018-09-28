#include "Game.h"
#include <stdio.h>
#include <iostream>
#include "Debug.h"
#include "ConsolePrint.h"
char Game::info1[] = "Use \"wasd\" keys to move player, Use \"Q\" for quite,Use \"R\" for add a monster";
char Game::info2[] = "Please enter players name end with \".\"";
char Game::info3[] = "Enter the number of monsters";
char Game::info4[] = "No Monster Left";
int Game::monsterlifetime = 10;
int Game::time = 0;
int Game::playersx = 1;
int Game::playersy = 15;
int Game::playerspeed = 2;
Game::Game() {
	this->Playerposition = GStar::Vector2(Game::playersx, Game::playersy);
	this->PlayerName = new GStar::SingleLinkedList<char>();
	this->MonsterList = new GStar::SingleLinkedList<Monster*>();
	this->flag = true;
}
Game::~Game()
{
	delete PlayerName;
	delete MonsterList;
}
void Game::Addmonster(int numbers)
{
	for (int i = 0; i < numbers; i++) {
		this->AddNewmonster();
	}
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log,  " %d monsters created",numbers);
}

void Game::AddNewmonster()
{
	this->MonsterList->Push(new Monster(Monster::lifespan+Game::time));
}

void Game::Update()
{
	printf("%s\n", Game::info1);
	Game::time++;
	this->PlayerInput();
	GStar::SingleLinkedListNode<Monster*>* temp = this->MonsterList->GetHead();
	GStar::SingleLinkedListNode<Monster*>* temp1 = temp->GetNext();

	while (temp1 != nullptr) {
		if (!(temp1->GetData()->CheckLife(Game::time))) {
			temp1->Delete(temp,this->MonsterList);
			temp1 = temp->GetNext();
		}
		else {
			temp = temp1;
			temp1 = temp->GetNext();
		}
		
	}

}


void Game::Draw()
{
	GStar::SingleLinkedListNode<char>* temp =  this->PlayerName->GetHead();
	temp = temp->GetNext();
	while (temp != nullptr) {
		printf("%c", temp->GetData());
		temp = temp->GetNext();
	}

	printf(" is at (%f,%f)\n", this->Playerposition.x(), this->Playerposition.y());
	GStar::SingleLinkedListNode<Monster*>* tempmonster = this->MonsterList->GetHead();
	tempmonster = tempmonster->GetNext();
	while (tempmonster != nullptr) {
		tempmonster->GetData()->Print();
		tempmonster = tempmonster->GetNext();
	}
}

void Game::GetPlayerName()
{
	printf("%s\n", Game::info1);
	printf("%s\n", Game::info2);
	char next='1';
	std::cin >> next;
	while (next != '.') {
		this->PlayerName->Push(next);
		std::cin >> next;
	}
	this->PlayerName->Push('\0');
}

void Game::Initialize()
{
	this->GetPlayerName();
	this->InitializeMonsters();
}

void Game::InitializeMonsters()
{
	printf("%s\n", Game::info3);
	int temp;
	std::cin >> temp;
	this->Addmonster(temp);
}

void Game::PlayerInput()
{
	char temp;
	std::cin >> temp;
	if (temp == 'w') {
		this->Playerposition += GStar::Vector2(0,Game::playerspeed);
	}
	else if (temp == 's') {
		this->Playerposition -= GStar::Vector2(0, Game::playerspeed);
	}
	else if (temp == 'a') {
		this->Playerposition -= GStar::Vector2(Game::playerspeed, 0);
	}
	else if (temp == 'd') {
		this->Playerposition += GStar::Vector2(Game::playerspeed, 0);
	}
	else if (temp == 'r') {
		this->AddNewmonster();
	}
	else if (temp == 'q') {
		this->flag = false;
	}
}
