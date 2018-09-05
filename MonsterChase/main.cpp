#include <stdio.h>
#include <iostream>
#include "Game.h"
int main() {
	Game* mygame = new Game();
	mygame->Initialize();
	mygame->Draw();
	while (true) {
		mygame->Update();
		mygame->Draw();
	}
	delete mygame;
	mygame = nullptr;
	return 0;
}