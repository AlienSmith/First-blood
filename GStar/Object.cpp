#include "Object.h"
#include "UpdateObject.h"
bool Object::Update()
{
	Component* temp;
	my_components.Resetcurrent();
	while (my_components.HasNext()) {
		temp = my_components.GetNextNode()->GetData();
		temp->Update();
		my_components.Move();
	}
	UpdateObject::OUT_Instance->Update();
	UpdateObject::Swamp();
	return true;
}
