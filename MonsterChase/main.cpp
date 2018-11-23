#include "Game.h"
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#include "ConsolePrint.h"
//#include <stdio.h>
#include <iostream>
#include "Debug.h"
#include "HeapManager_UnitTest.cpp"
#include "MainRenderLoop.cpp"
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
	{
		HeapManager_UnitTest();
		MainEntrance();
		int a = 0;
		std::cin >> a;
		return a;
	}