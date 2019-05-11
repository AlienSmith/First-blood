#include "PongBallController.h"
#include <math.h>
GStar::PongBallController::PongBallController(GStar::PhysicComponent * component, float max_speed, float enhance_Scale)
	:InterfaceComponent(component->GetTransformComponent()),
	maxspeed(max_speed),
	enhancement(enhance_Scale),
	my_component(component)
{
}

void GStar::PongBallController::Initialize()
{
	float tempvalue =float( ((double)rand() / (RAND_MAX))* 10 + 1);
	Vector3 temp = Vector3( tempvalue/10.0f + 1.0f, tempvalue/10.0f,0.0f);
	temp /= 2 * temp.Length();
	my_component->SetSpeed(temp);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Initialized with speed (%f,%f,%f)",temp[0],temp[1],temp[2]);
	return;
}

void GStar::PongBallController::OnCollision(CollisionComponent *, const Vector3 &)
{
	Vector3 temp = my_component->GetSpeed();
	if (temp.Length()*(1 + enhancement) < maxspeed) {
		temp *= (1 + enhancement);
		my_component->SetSpeed(temp);
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Ball Accelerated to speed (%f,%f,%f)", temp[0], temp[1], temp[2]);
	}
	return;
}
