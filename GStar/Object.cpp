#include "Object.h"
bool Object::Update()
{
	Component* temp;
	my_components.Resetcurrent();
	while (my_components.HasNext()) {
		temp = my_components.GetNextNode()->GetData();
		temp->Update();
	}
	return true;
}

bool Object::ComponentUpdate(Component * temp) const
{
	
	return false;
}

