#pragma once
#include "SingleLinkedList.h"
namespace GStar {
	class CollisionComponent;
	class CollisionManager {
	public:
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
		SingleLinkedList<CollisionComponent*> CollisionComponentlist;
		CollisionManager(){}
	};
}