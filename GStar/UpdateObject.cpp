#include "UpdateObject.h"

UpdateObject* OUT_Instance = nullptr;
UpdateObject* IN_Instance = nullptr;
void UpdateObject::Update()
{
	if (my_texture) {
		my_texture->Update();
	}
	if (my_mesh) {
		my_mesh->Update();
	}
	if (my_shader) {
		my_shader->Update();
	}
	if (my_transform) {
		my_transform->Update();
	}
}
