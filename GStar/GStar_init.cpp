#include "GStar_init.h"
#include "Matrix4.h"
#include "Coordinate.h"
#include <stdio.h>
bool GStar::Initialize()
{
	world = new Coordinate(Coordinate::TYPE::WORLD);
	camera = new Coordinate(Coordinate::TYPE::CAMERA);
	object = new Coordinate(Coordinate::TYPE::OBJECT);
	printf("Initialized");
	return true;
}
bool GStar::Terminate()
{
	GStar::CleanPool();
	printf("Terminated");
	return true;
}