#pragma once
#include "SingleLinkedList.h"
#include "PhysicComponent.h"
//TODO ask whether should I add Layer to specify those things
namespace GStar {
	class PhysicManager
	{
	public:
		~PhysicManager() {}
		static const Vector3 Gravity;
		static PhysicManager* Instance() {
			if (!instance) {
				instance = new PhysicManager();
			}
			return instance;
		}
		static void Terminate() {
			if (instance) {
				delete instance;
			}
		}
		//Call The function To apply physical effects to objects
		void Update(float deltatime) {
			PhysicsList.Resetcurrent();
			while (PhysicsList.HasNext()) {
				PhysicComponent* temp = PhysicsList.GetNext();
				if (temp->useGravity()) {
					temp->AddForce(PhysicManager::Gravity * temp->getMass());
				}
				if (temp->UpdateInPhysics()) {
					temp->Update(deltatime);
				}
				else {
					temp->UpdateAngularSpeed(deltatime);
				}
				PhysicsList.Move();
			}
		}
		inline PhysicComponent* AddPhysic(TransformComponent* const component);
		inline PhysicComponent* AddPhysic(TransformComponent* const component, bool use_gravity, float mass, float roughtness);
		inline PhysicComponent* AddPhysic(TransformComponent* const component, bool use_gravity, float mass, float roughtness,Vector3 _angular_momentum);
		inline PhysicComponent* GetPhysic(const GStar::MyString& string);
		inline PhysicComponent* GetPhysic(const TransformComponent* const Component);
		inline bool removePhysic(const TransformComponent* component);
	private:
		static PhysicManager* instance;
		SingleLinkedList<PhysicComponent*> PhysicsList;
		PhysicManager() {}
	};
	inline PhysicComponent * PhysicManager::AddPhysic(TransformComponent * const component)
	{
		PhysicComponent* temp = new PhysicComponent(component);
		PhysicsList.Push(temp);
		return temp;
	}
	inline PhysicComponent * PhysicManager::AddPhysic(TransformComponent * const component, bool use_gravity, float mass, float roughtness)
	{
		PhysicComponent* temp = new PhysicComponent(component,use_gravity,mass,roughtness);
		PhysicsList.Push(temp);
		return temp;
	}
	inline PhysicComponent * PhysicManager::AddPhysic(TransformComponent * const component, bool use_gravity, float mass, float roughtness, Vector3 _angular_momentum)
	{
		PhysicComponent* temp = new PhysicComponent(component, use_gravity, mass, roughtness,_angular_momentum);
		PhysicsList.Push(temp);
		return temp;
	}
	inline PhysicComponent * PhysicManager::GetPhysic(const GStar::MyString & string)
	{
		unsigned int id = GStar::MyString::hash_str(string.GetString());
		PhysicsList.Resetcurrent();
		while (PhysicsList.HasNext()) {
			if (PhysicsList.GetNext()->GetTransformComponent()->GetName() == id) {
				return PhysicsList.GetNext();
			}
			PhysicsList.Move();
		}
		return nullptr;

	}
	inline PhysicComponent * PhysicManager::GetPhysic(const TransformComponent * const component)
	{
		PhysicsList.Resetcurrent();
		while (PhysicsList.HasNext()) {
			if (PhysicsList.GetNext()->GetTransformComponent() == component) {
				return PhysicsList.GetNext();
			}
			PhysicsList.Move();
		}
		return nullptr;
	}
	inline bool PhysicManager::removePhysic(const TransformComponent * component)
	{
		bool result = false;
		PhysicsList.Resetcurrent();
		while (PhysicsList.HasNext()) {
			if (PhysicsList.GetNext()->GetTransformComponent() == component) {
				delete PhysicsList.GetNext();
				PhysicsList.DeleteNext();
				result = true;
				break;
			}
			PhysicsList.Move();
		}
		return result;
	}
}