#include "Object.h"
#include "UpdateObject.h"
bool Object::Update(float deltatime)
{
	Component* temp;
	my_components.Resetcurrent();
	while (my_components.HasNext()) {
		temp = my_components.GetNextNode()->GetData();
		temp->Update(deltatime);
		my_components.Move();
	}
	UpdateObject::OUT_Instance->Update(deltatime);
	UpdateObject::Swamp();
	return true;
}

bool Object::ComponentUpdate(Component * temp) const
{
	
	return false;
}

