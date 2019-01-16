#pragma once
#include "SingleLinkedList.h"
#include "Component.h"
class Object {
public:
	bool Update();
	bool Terminate() {}
	template<class T>
	T* GetComponent() {
			char word = T::TypeWord();
			my_components.Resetcurrent();
			while (my_components.HasNext) {
				if (my_components.GetNext()->GetType() == word) {
					return my_components.GetNext();
				}
			}
		return nullptr;
	}
	Component* GetComponent(char type) {
		my_components.Resetcurrent();
		while (my_components.HasNext()) {
			if (my_components.GetNext()->GetType() == type) {
				return my_components.GetNext();
			}
			my_components.Move();
		}
		return nullptr;
	}
	void AddComponent(Component* component) {
		my_components.Push(component);
	}
	Object() {}
	Object(const Object& instance) = delete;
	const Object& operator = (const Object& instance) = delete;
	~Object() {
		my_components.DeleteContent();
	}
private:
	GStar::SingleLinkedList<Component*> my_components;
};