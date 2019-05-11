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
#include "PongGame.h"
#include "MT_MAIN.hpp"
#include "Matrix4.h"
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
#include<vector>
#include"CollisionTest.hpp"
#include"Vector3.h"
//std::vector<GStar::MyString> strings;
int main() 
{{
	bool MT = false;
	bool CollsionTest = false;
	InitializeMemorySystem();
	//GStar::Vector3 left(1, 2, 3);
	//GStar::Vector3 right(3, 2, 1);
	//float dot = left.Dot(right);
	//float sdot = left.SDot(right);
	//GStar::Vector3 cross = GStar::Vector3::Cross(left, right);
	//GStar::Vector3 scross = left.SCross(right);
	//GStar::Matrix4 lhs(IDENTICAL_MATRIX);
	//GStar::Matrix4 rhs(IDENTICAL_MATRIX);
	//GStar::Matrix4 Dot = lhs.Dot(rhs);
	//GStar::Matrix4 SDot = lhs.SDot(rhs);
	if (MT) {
		Entrance();
	}
	else if (CollsionTest) {
		GStar::CollisionPoolCheck();
	}
	else {
		PongGame scene;
		MainEntrance::SetUpAndRun();
	}
		DestroyMemorySystem();
	};
	_CrtDumpMemoryLeaks();
	//int a = 0;
	//std::cin >> a;
	return 0;
}