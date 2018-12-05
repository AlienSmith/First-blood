#pragma once
#include "SingleLinkedList.h"
#include "Component.h"
class Object {
public:
	bool Update();
	bool Terminate() {}
	void AddComponent(Component* component) {
		my_components.Push(component);
	}
private:
	GStar::SingleLinkedList<Component*> my_components;
	bool ComponentUpdate(Component* temp) const;
};