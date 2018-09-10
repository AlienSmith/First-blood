#include "Game.h"

char Game::info1[] = "Use \"wasd\" keys to move player, Use \"Q\" for quite,Use \"R\" for add a monster";
char Game::info2[] = "Please enter players name";
char Game::info3[] = "Enter the number of monsters";
char Game::info4[] = "No Monster Left";
int Game::monsterlifetime = 10;
int Game::time = 0;
int Game::playersx = 1;
int Game::playersy = 15;
int Game::playerspeed = 2;
Game::Game() {
	this->playerx = Game::playersx;
	this->palyery = Game::playersy;
}
void Game::Addmonster(int numbers)
{
	this->start = new Monster();
	Monster* currentmonster;
	Monster* privousMonster;
	Monster* successMonster;
	privousMonster = this->start;
	successMonster = nullptr;
	for (int i = 0; i < numbers; i++) {
		currentmonster = new Monster(Game::monsterlifetime);
		(*privousMonster).after = currentmonster;
		(*currentmonster).previous = privousMonster;
		(*currentmonster).after = successMonster;
		privousMonster = currentmonster;
	}
}

void Game::AddNewmonster()
{
	Monster* currentmonster = new Monster(Game::time + Game::monsterlifetime);
	if (this->start->after != nullptr) {
		(*(this->start->after)).previous = currentmonster;
	}
	(*currentmonster).after = this->start->after;
	(*(this->start)).after = currentmonster;
	(*currentmonster).previous = this->start;
}

void Game::Update()
{
	Game::time++;
	this->PlayerInput();
	Monster* temp;
	temp = start;
	Monster* after;
	after = temp->after;
	temp = after;
	while (temp != nullptr) {
		temp->Update(this->playerx, this->playersy, this->time);
		after = temp->after;
		if (temp->lifetime < this->time) {
			delete temp;
		}
		temp = after;
	}
}


void Game::Draw()
{
	printf("%s is at (%i,%i)\n", this->PlayerName, this->playerx, this->palyery);
	Monster* temp;
	temp = start;
	if (temp->after == nullptr) {
		printf("%s \n", this->info4);
		return;
	}

	while (temp->after != nullptr) {
		temp = temp->after;
		temp->Print();
	}
}

void Game::GetPlayerName()
{
	printf("%s\n", Game::info1);
	printf("%s\n", Game::info2);
	std::cin >> this->PlayerName;
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
		this->palyery += playerspeed;
	}
	else if (temp == 's') {
		this->palyery -= playerspeed;
	}
	else if (temp == 'a') {
		this->playerx -= playerspeed;
	}
	else if (temp == 'd') {
		this->playerx += playerspeed;
	}
	else if (temp == 'r') {
		this->AddNewmonster();
	}
	else if (temp == 'q') {
		exit(0);
	}
}
