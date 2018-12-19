#pragma once
#include "TransformComponent.h"
#include "SingleLinkedList.h"
namespace GStar {
	class LightManager {
	public:
		static LightManager* Instance() {
			if (!instance) {
				LightManager::instance = new LightManager();
			}
		}
		static void Terminate() {
			if (instance) {
				delete instance;
			}
		}
	private:
		static LightManager* instance;

	};
}