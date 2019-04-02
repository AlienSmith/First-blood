#include "Game.h"
#define _CRTDBG_MAP_ALLOC  
#include "ConsolePrint.h"
//#include <stdio.h>
#include <iostream>
#include "Debug.h"
#include "HeapManager_UnitTest.cpp"
//#include "MainRenderLoop.cpp"
#include "SingleLinkedDictionary.h"
#include "LightScene.h"
#include "MemorySystem.h"
#include "MainEntrance.h"
#include "MyString.h"
#include "TestScene.h"
#include "MT_MAIN.hpp"
//#include "Matrix4.h"
//#include "Vector2.h"
//#include "Vector3.h"
//#include "GStar_init.cpp"
//#include "Coordinate.h"
//#include "SingleLinkedList.h"
//void test();
//void test1();
//void test2();
//void test3();
int main() 
{{
	bool MT = true;
	InitializeMemorySystem();
	if (MT) {
		Entrance();
	}
	else {
		TestScene scene;
		MainEntrance::SetUpAndRun();
	}
		DestroyMemorySystem();
	};
	_CrtDumpMemoryLeaks();
	int a = 0;
	std::cin >> a;
	return a;
}