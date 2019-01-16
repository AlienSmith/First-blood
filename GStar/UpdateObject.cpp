#include "UpdateObject.h"
#include "GLError.h"
UpdateObject* UpdateObject::IN_Instance = nullptr;
UpdateObject* UpdateObject::OUT_Instance = nullptr;
void UpdateObject::Update()
{
	if (my_interface != nullptr) {
		my_interface->Update( );
	}
	if (my_texture != nullptr) {
		my_texture->Update( );
	}
	if (my_mesh != nullptr) {
		my_mesh->Update( );
	}
	if (my_shader != nullptr) {
		my_shader->Update( );
	}
	if (my_transform != nullptr) {
		my_transform->Update( );
	}
	check_gl_error();
	reset();
}
