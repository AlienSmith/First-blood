#include "RObject.h"
#include "UpdateRObject.h"
bool RObject::Update()
{
	UpdateRObject::IN_Instance->SetTransform(my_transform);
	Component* temp;
	my_components.Resetcurrent();
	while (my_components.HasNext()) {
		temp = my_components.GetNextNode()->GetData();
		temp->Update();
		my_components.Move();
	}
	UpdateRObject::OUT_Instance->Update();
	UpdateRObject::Swamp();
	return true;
}
