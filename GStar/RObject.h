#pragma once
#include "SingleLinkedList.h"
#include "Component.h"
class RObject {
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
	RObject() {}
	RObject(const RObject& instance) = delete;
	const RObject& operator = (const RObject& instance) = delete;
	~RObject() {
		my_components.DeleteContent();
	}
private:
	GStar::SingleLinkedList<Component*> my_components;
};