#include "SimpleForce.h"
#include "PhysicComponent.h"
#include "math.h"
#include "GSTime.h"
void GStar::SimpleForce::Update()
{
	my_component->AddForce(GStar::Vector3(_force*(float)sin(GStar::GSTime::Instance().GetTotalTime()),0.0f,0.0f));
}
