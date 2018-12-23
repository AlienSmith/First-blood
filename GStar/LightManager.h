#pragma once
#include "Vector3.h"
#include "SingleLinkedList.h"
class Object;
namespace GStar {
	//TODO use the light Component
	class LightManager
	{
	public:
		static LightManager* Instance() {
			if (!instance) {
				instance = new LightManager();
			}
			return instance;
		}
		Vector3 GetLight();
		static void Terminate() {
			if (instance) {
				delete instance;
			}
		}
		void Register(Object* lightsource);
		static const float AmbientStrength;
	private:
		static LightManager* instance;
		SingleLinkedList<Object*> LightList;
	};

}