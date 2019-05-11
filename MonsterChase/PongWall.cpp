#include "MainEntrance.h"
#include "PongWall.h"
GStar::PongWall::PongWall(GStar::TransformComponent* component) :InterfaceComponent(component) {}

void GStar::PongWall::OnCollision(CollisionComponent * other_collider, const Vector3 & Collision_Point)
{
	MainEntrance::EndGame();
}
