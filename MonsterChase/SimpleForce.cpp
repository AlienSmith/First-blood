#include "SimpleForce.h"
#include "PhysicComponent.h"
#include "math.h"
#include "GSTime.h"
void GStar::SimpleForce::Update()
{
	my_transform->AddFource(GStar::Vector3(_force*sin(GStar::GSTime::Instance().GetTotalTime()),0.0f,0.0f));
}
