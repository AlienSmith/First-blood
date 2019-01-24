#include "SimpleForce.h"
#include "PhysicComponent.h"
void GStar::SimpleForce::Update()
{
	my_transform->AddFource(GStar::Vector3(2.0f,0.0f,0.0f));
}
