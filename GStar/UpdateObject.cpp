#include "UpdateObject.h"
#include "GLError.h"
UpdateObject* UpdateObject::IN_Instance = nullptr;
UpdateObject* UpdateObject::OUT_Instance = nullptr;
void UpdateObject::Update(float deltatime)
{
	if (my_interface != nullptr) {
		my_interface->Update( deltatime);
	}
	if (my_texture != nullptr) {
		my_texture->Update( deltatime);
	}
	if (my_mesh != nullptr) {
		my_mesh->Update( deltatime);
	}
	if (my_shader != nullptr) {
		my_shader->Update( deltatime);
	}
	if (my_transform != nullptr) {
		my_transform->Update( deltatime);
	}
	check_gl_error();
	reset();
}
