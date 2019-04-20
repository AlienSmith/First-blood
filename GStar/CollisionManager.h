#pragma once
#include <vector>
namespace GStar {
	class CollisionComponent;
	class PhysicComponent;
	class Vector3;
	class CollisionManager {
	public:
		static CollisionComponent* AddCollision(PhysicComponent* my_physic, const Vector3& offset);
		static CollisionManager* Instance() {
			if (!instance) {
				instance = new CollisionManager();
			}
			return instance;
		}
		static void Terminate() {
			if (instance) {
				delete instance;
			}
		}
		void Update();
		void UpdatePhysic(float deltatime);
		//This function is put here instead of right after axies seperation therom cause 
		//we do not need every collision point, only the most recent one.
		void GetCollisionPoint(CollisionComponent* A, CollisionComponent* B, const Vector3& normal,Vector3& RA,Vector3& RB,Vector3& Point,float deltatime) const;
		int ContactInfo(CollisionComponent* A, const Vector3& normal,Vector3& offset, std::vector<Vector3>& o_Vector) const;
		void ApplyCollisionResults(CollisionComponent* A, CollisionComponent* B, const GStar::Vector3& NormalForA);
	private:
		static CollisionManager* instance;
		std::vector<CollisionComponent*> CollisionComponents;
		CollisionManager(){}
	};
}