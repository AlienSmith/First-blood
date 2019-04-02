#include "CollisionComponent.h"
#include "PhysicComponent.h"
GStar::CollisionComponent::CollisionComponent(PhysicComponent * trans):my_physic(trans){}

GStar::CollisionComponent::CollisionComponent(PhysicComponent * trans, const Vector3 & offset): my_physic(trans),offsets(offset){}

GStar::PhysicComponent * GStar::CollisionComponent::getPhysic()
{
	return nullptr;
}

GStar::Vector3 GStar::CollisionComponent::getOffset()
{
	return Vector3();
}


bool GStar::Collided(const CollisionComponent & ColliderA, const CollisionComponent & ColliderB, Vector3 & o_point, Vector3 & o_normal,float deltatime)
{
	GStar::Vector3 Vector_A[4];
	GStar::Vector3 Vectro_B[4];
	return false;
}
