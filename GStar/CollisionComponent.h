#pragma once
#include"Vector3.h"
namespace GStar {
	struct CollisionInfo{
		GStar::Vector3 Axies[3];
		GStar::Vector3 Tr;
		GStar::Vector3 Scale;
	};
	class PhysicComponent;
	//cuboid collider
	class CollisionComponent {
	public:
		const static float margin;
		explicit CollisionComponent(PhysicComponent* trans);
		explicit CollisionComponent(PhysicComponent* trans, const Vector3& offset);
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent& operator = (const CollisionComponent& other) = delete;
		PhysicComponent* getPhysic();
		const PhysicComponent* const getPhysic() const;
		Vector3 getOffset() const;
		void GetCollisionInfo();
		void Update();
		GStar::CollisionInfo my_info;
	private:
		PhysicComponent* my_physic;
		Vector3 offsets;
	};
	bool Collided(const CollisionComponent& ColliderA, const CollisionComponent& ColliderB, Vector3& o_point,Vector3& o_normal,float deltatime,float& collisiontime);
	bool OverLapAtoB(const CollisionInfo* A, const CollisionInfo* B, const Vector3& speed,float end_time,float& closeTime, float& opentime,Vector3& o_axies);
	bool OverLapAB(const CollisionInfo* A, const CollisionInfo* B, const Vector3& speed, float end_time, float& closeTime, float& opentime, Vector3& o_axies);
}