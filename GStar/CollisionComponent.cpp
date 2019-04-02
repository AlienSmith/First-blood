#include "CollisionComponent.h"
#include "PhysicComponent.h"
GStar::CollisionComponent::CollisionComponent(PhysicComponent * trans):my_physic(trans){}

GStar::CollisionComponent::CollisionComponent(PhysicComponent * trans, const Vector3 & offset): my_physic(trans),offsets(offset){}

const GStar::PhysicComponent * const GStar::CollisionComponent::getPhysic() const{

	return my_physic;
}

GStar::Vector3 GStar::CollisionComponent::getOffset() const
{
	return offsets;
}


bool GStar::Collided(const CollisionComponent& ColliderA, const CollisionComponent& ColliderB, Vector3& o_point, Vector3& o_normal, float deltatime)
{
	//X Y Z Tr
	//Assume the speed does not change during this frame
	GStar::Vector3 Vector_A[4];
	GStar::Vector3 Vector_B[4];
	GStar::Vector3 SpeedAtoB = ColliderA.getPhysic()->GetSpeed() -ColliderB.getPhysic()->GetSpeed();
	Vector_A[0] = ColliderA.getPhysic()->GetTransformComponent()->X();
	Vector_A[1] = ColliderA.getPhysic()->GetTransformComponent()->Y();
	Vector_A[2] = ColliderA.getPhysic()->GetTransformComponent()->Z();
	Vector_A[3] = ColliderA.getPhysic()->GetTransformComponent()->T();
 	Vector_B[0] = ColliderB.getPhysic()->GetTransformComponent()->X();
	Vector_B[1] = ColliderB.getPhysic()->GetTransformComponent()->Y();
	Vector_B[2] = ColliderB.getPhysic()->GetTransformComponent()->Z();
	Vector_B[3] = ColliderB.getPhysic()->GetTransformComponent()->T();
	//Transfer Center to the world space

	return false;
}
