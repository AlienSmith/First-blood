#include <stdio.h>
#include <iostream>
#include "Game.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "GStar_init.h"
//void test();
//void test1();
//void Game1();
int main() {
	GStar::Initialize();

	float da[4][4] = { 
		{1,2,0,0},
	{2, 0, 0, 0},
	{ 0,0,0,0 },
	{ 0,0,0,0 }, };
	GStar::Matrix4 matrix1 = GStar::Matrix4(da);
	GStar::Matrix4 matrix2 = GStar::Matrix4(da);
	GStar::Matrix4 matrix3 = (matrix1.Dot(matrix2).Dot(matrix1));

	int a;
	std::cin >> a;
	return 0;
}
//void test() {
//	GStar::Matrix4 matrix1 = GStar::Matrix4(da);
//	GStar::Matrix4 matrix2 = GStar::Matrix4(da);
//
//	GStar::Matrix4 matrix3 = matrix1 + matrix2;
//	matrix3 = (matrix1 + matrix2 + matrix3);
//
//
//	float a = 0;
//
//	return;
//}
//
//void test1() {
//
//	GStar::Initialize();
//	GStar::Vector3 v1(1, 0, 0);
//	GStar::Vector3 v2(0, 0, 1);
//	printf("%f\n", (v1 + v2).Length());
//	printf("%f\n", (v1 * v2).Length());
//	printf("%f\n", v1.Dot(v2));
//	printf("%f\n", GStar::Vector3::ProjAtoB(v1, v2).Length());
//}
//
//void Game1() {
//	Game* mygame = new Game();
//	mygame->Initialize();
//	mygame->Draw();
//	while (true) {
//		mygame->Update();
//		mygame->Draw();
//	}
//	delete mygame;
//	mygame = nullptr;
//}