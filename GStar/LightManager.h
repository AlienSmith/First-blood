#pragma once
#include "Vector3.h"
#include "SingleLinkedList.h"
#include"TransformComponent.h"
#include"MyString.h"
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
		static void Terminate() {
			if (instance) {
				delete instance;
			}
		}
		inline void addLight(GStar::TransformComponent* component) {
			if (!hasThisLight(component)) {
				LightList.Push(component);
				component->SetLayer(GStar::Layer::LIGHT);
			}
			else {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "try to add light already exists");
			}
		}
		inline bool hasThisLight(GStar::TransformComponent* component) {
			LightList.Resetcurrent();
			while (LightList.HasNext()) {
				if (LightList.GetNext() == component) {
					return true;
				}
				LightList.Move();
			}
			return false;
		}
		//remove the pointer from the least will not delete the pointer
		inline bool removeLight(GStar::TransformComponent* component) {
			bool result = false;
			LightList.Resetcurrent();
			while (LightList.HasNext()) {
				if (LightList.GetNext() == component) {
					LightList.DeleteNext();
					component->SetLayer(GStar::Layer::DEFAULT);
					result = true;
					break;
				}
				LightList.Move();
			}
			return result;
		}
		inline void SetCurrentLight(GStar::TransformComponent* component) {
			CurrentLight = component;
			addLight(component);
		}
		inline bool SetCurrentLight(int index) {
			int count = 0;
			LightList.Resetcurrent();
			while (count < index, LightList.HasNext()) {
				LightList.Move();
				count++;
			}
			if (count == index) {
				CurrentLight = LightList.GetNext();
				return true;
			}
			return false;
		}inline bool SetCurrentLight(const GStar::MyString& string) {
			unsigned int id = GStar::MyString::hash_str(string.GetString());
			LightList.Resetcurrent();
			while (LightList.HasNext()) {
				if (LightList.GetNext()->GetName() == id) {
					CurrentLight = LightList.GetNext();
					return true;
				}
				LightList.Move();
			}
			return false;
		}
		inline Vector3 GetLight() { return CurrentLight->GetTransform(); }
		inline Vector3 GetambientLight() { return Vector3(AmbientStrength, AmbientStrength, AmbientStrength); }
		void Register(Object* lightsource);
		static const float AmbientStrength;
	private:
		static LightManager* instance;
		SingleLinkedList<TransformComponent*> LightList;
		TransformComponent* CurrentLight;
	};

}