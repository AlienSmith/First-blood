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
	private:
		static CollisionManager* instance;
		std::vector<CollisionComponent*> CollisionComponents;
		CollisionManager(){}
	};
}