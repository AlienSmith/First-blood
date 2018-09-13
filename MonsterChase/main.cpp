#include <stdio.h>
#include <iostream>
#include "Game.h"
#include <GStar_init.h>
int main() {
	GStar::Initialize();
	GStar::Vector2 v1(1,0);
	GStar::Vector2 v2(0,1);
	printf("%f\n", (v1+v2).Length());
	printf("%f\n", (v1 * v2).Length());
	printf("%f\n", v1.Dot(v2));
	printf("%f\n", GStar::Vector2::ProjAtoB(v1,v2).Length());
	
	Game* mygame = new Game();
	mygame->Initialize();
	/*
	mygame->Draw();
	while (true) {
		mygame->Update();
		mygame->Draw();
	}
	delete mygame;
	mygame = nullptr;
	return 0;
	*/
}