#include "GStar_init.h"
#include "Matrix4.h"
#include <stdio.h>
bool GStar::Initialize()
{
	printf("Initialized");
	return true;
}
bool GStar::Terminate()
{
	//GStar::CleanPool();
	printf("Terminated");
	return true;
}