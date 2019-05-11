#include "PongBallController.h"
GStar::PongBallController::PongBallController(GStar::PhysicComponent * component, float max_speed, float enhance_Scale)
	:InterfaceComponent(component->GetTransformComponent()),
	maxspeed(max_speed),
	enhancement(enhance_Scale)
{
}

void GStar::PongBallController::Initialize()
{
	Vector3 temp = Vector3(1,0,0);
	my_component->SetSpeed(temp);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Initialized with speed (%f,%f,%f)",temp[0],temp[1],temp[2]);
	return;
}

void GStar::PongBallController::OnCollision(CollisionComponent * other_collider, const Vector3 & Collision_Point)
{
	Vector3 temp = my_component->GetSpeed();
	if (temp.Length()*(1 + enhancement) < maxspeed) {
		temp *= (1 + enhancement);
		my_component->SetSpeed(temp);
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Ball Accelerated to speed (%f,%f,%f)", temp[0], temp[1], temp[2]);
	}
	return;
}
