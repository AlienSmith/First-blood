#pragma once
#include "SingleLinkedList.h"
#include "TransformComponent.h"
#include "MyString.h"
#include "LightComponent.h"
class Shader;
namespace GStar {
	//TODO use the light Component
	class LightManager
	{
	public:
		void LoadShader(const Shader* const shader);
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
		~LightManager() {
			Lights.DeleteContent();
		}
		inline LightComponent* GenerateLight(GStar::TransformComponent* component, Lighttype type) {
			LightComponent* temp = new LightComponent(type, component);
			Lights.Push(temp);
			return temp;
		}
		inline LightComponent* GetLight(const GStar::MyString& string) {
			unsigned int id = GStar::MyString::hash_str(string.GetString());
			Lights.Resetcurrent();
			while (Lights.HasNext()) {
				if (Lights.GetNext()->Getlightinfo().my_transform->GetName() == id) {
					return Lights.GetNext();
				}
				Lights.Move();
			}
			return nullptr;
		}
		//remove the pointer from the least will not delete the pointer
		inline bool removeLight(GStar::TransformComponent* component) {
			bool result = false;
			Lights.Resetcurrent();
			while (Lights.HasNext()) {
				if (Lights.GetNext()->Getlightinfo().my_transform == component) {
					delete Lights.GetNext();
					Lights.DeleteNext();
					component->SetLayer(GStar::Layer::DEFAULT);
					result = true;
					break;
				}
				Lights.Move();
			}
			return result;
		}
		inline Vector3 GetLightPosition() {
			Lights.Resetcurrent();
			return Lights.GetNext()->Getlightinfo().my_transform->GetTransform(); }
		inline Vector3 GetambientLight() { 
			Lights.Resetcurrent();
			return Lights.GetNext()->Getlightinfo().ambient;}
		inline LightInfo GetLightInfo() { 
			Lights.Resetcurrent();
			return Lights.GetNext()->Getlightinfo();}
	private:
		static LightManager* instance;
		SingleLinkedList<LightComponent*> Lights;
	};

}