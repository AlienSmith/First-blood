#include "MainEntrance.h"
#include "PongWall.h"
GStar::PongWall::PongWall(GStar::TransformComponent* component) :InterfaceComponent(component) {}

void GStar::PongWall::OnCollision(CollisionComponent *, const Vector3 &)
{
	MainEntrance::EndGame();
}
