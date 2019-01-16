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
		void WriteToShader(const Shader* const shader);
		static void Initialize();
		static LightManager* Instance() {
			if (!instance) {
				instance = new LightManager();
				Initialize();
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
		inline int GetIndex(const LightComponent* const component) {
			Lights.Resetcurrent();
			int count = 0;
			while (Lights.HasNext()) {
				if (component == Lights.GetNext()) {
					return count;
				}
				count++;
				Lights.Move();
			}
			return -1;
		}
		inline LightComponent* GetLight(int index) {
			Lights.Resetcurrent();
			int count = 0;
			while (Lights.HasNext()) {
				if (index == count) {
					return Lights.GetNext();
				}
				count++;
				Lights.Move();
			}
			return nullptr;
		}
		inline bool WriteToShaderFrom(const Shader* const shader, int lightsindex, int count,bool addfirstLight) {
			Lights.Resetcurrent();
			int index = 0;
			bool exists;
			while (Lights.HasNext()) {
				if (index == lightsindex) {
					exists = true;
					break;
				}
				index++;
				Lights.Move();
			}
			if (exists) {
				_writeToShader(shader, Lights.GetNext()->Getlightinfo(), 0);
				for (int i = 1; i < count; i++) {
					Lights.Move();
					if (!Lights.HasNext()) {
						exists = false;
						break;
					}
					_writeToShader(shader, Lights.GetNext()->Getlightinfo(), i);
				}
			}
			if (exists) {
				if (addfirstLight) {
					Lights.Resetcurrent();
					_writeToShader(shader,Lights.GetNext()->Getlightinfo(), count);
					shader->setInt("numlights", count+1);
				}
				else {
					shader->setInt("numlights", count);
				}
			}
			return exists;
		}
		inline bool WriteToShaderFrom(const Shader* const shader, const LightComponent* const component, int count, bool addfirstLight) {
			Lights.Resetcurrent();
			int index = 0;
			bool exists = false;
			while (Lights.HasNext()) {
				if (component == Lights.GetNext()) {
					exists = true;
					break;
				}
				index++;
				Lights.Move();
			}
			if (exists) {
				_writeToShader(shader, Lights.GetNext()->Getlightinfo(), 0);
				for (int i = 1; i < count; i++) {
					Lights.Move();
					if (!Lights.HasNext()) {
						exists = false;
						break;
					}
					_writeToShader(shader, Lights.GetNext()->Getlightinfo(), i);
				}
			}
			if (exists) {
				if (addfirstLight) {
					Lights.Resetcurrent();
					_writeToShader(shader, Lights.GetNext()->Getlightinfo(), count);
					shader->setInt("numlights", count + 1);
				}
				else {
					shader->setInt("numlights", count);
				}
			}
			return exists;
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
		static void _writeToShader(const Shader* const shader, const GStar::LightInfo& info, int index);
		static LightManager* instance;
		SingleLinkedList<LightComponent*> Lights;
		 static MyString afterPhix[12];
		 static MyString prePhix;
	};

}