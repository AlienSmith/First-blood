#pragma once
#include"Vector3.h"
namespace GStar {
	class PhysicComponent;
	//cuboid collider
	class CollisionComponent {
	public:
		explicit CollisionComponent(PhysicComponent* trans);
		explicit CollisionComponent(PhysicComponent* trans, const Vector3& offset);
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent& operator = (const CollisionComponent& other) = delete;
		PhysicComponent* getPhysic();
		Vector3 getOffset();
	private:
		PhysicComponent* my_physic;
		Vector3 offsets;
	};
	bool Collided(const CollisionComponent& ColliderA, const CollisionComponent& ColliderB, Vector3& o_point,Vector3& o_normal,float deltatime);
}