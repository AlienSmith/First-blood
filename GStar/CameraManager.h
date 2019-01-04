#pragma once
#include"TransformComponent.h"
#include"SingleLinkedList.h"
#include"Matrix4.h"
namespace GStar {
	class CameraManager {
	public:
		static CameraManager* Instance() {
			if (instance == nullptr) {
				GStar::CameraManager::instance = new GStar::CameraManager();
			}
			return instance;
		}
		static void Terminate() {
			if (instance) {
				delete instance;
			}
		}
		inline void addCamera(GStar::TransformComponent* component) {
			if (!hasThisCamera(component)) {
				cameracomponents.Push(component);
				component->SetLayer(GStar::Layer::CAMERA);
			}
			else {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "try to add camera already exists");
			}
		}
		//remove the Camera from the list before delete the Camera Instance
		//return false if the transform does not belong to a camera
		inline bool RemoveCamera(GStar::TransformComponent* component) {
			bool result = false;
			cameracomponents.Resetcurrent();
			while (cameracomponents.HasNext()) {
				if (cameracomponents.GetNext() == component) {
					cameracomponents.DeleteNext();
					component->SetLayer(GStar::Layer::DEFAULT);
					result = true;
					break;
				}
				cameracomponents.Move();
			}
			return result;
		}
		inline bool hasThisCamera(const GStar::TransformComponent* component) {
			cameracomponents.Resetcurrent();
			while (cameracomponents.HasNext()) {
				if (cameracomponents.GetNext() == component) {
					return true;
				}
				cameracomponents.Move();
			}
			return false;
		}
		inline bool SetCurrentCamera(int index) {
			int count = 0;
			cameracomponents.Resetcurrent();
			while (count < index, cameracomponents.HasNext()) {
				cameracomponents.Move();
				count++;
			}
			if (count == index) {
				currentComponent = cameracomponents.GetNext();
				return true;
			}
			return false;
		}
		inline bool SetCurrentCamera(const GStar::MyString& string) {
			unsigned int id = GStar::MyString::hash_str(string.GetString());
			cameracomponents.Resetcurrent();
			while (cameracomponents.HasNext()) {
				if (cameracomponents.GetNext()->GetName() == id) {
					currentComponent = cameracomponents.GetNext();
					return true;
				}
				cameracomponents.Move();
			}
			return false;
		}
		inline void SetCurrentCamera(GStar::TransformComponent* component) {
			currentComponent = component;
			addCamera(component);
		}
		//this function will return the last camera if index out of space
		inline GStar::Matrix4 GetInverseTransform() {
			return currentComponent->getInverseModel();
		}
	private:
		static CameraManager* instance;
		SingleLinkedList<TransformComponent*> cameracomponents;
		TransformComponent* currentComponent;
	};
}