#include "UpdateObject.h"
UpdateObject* UpdateObject::IN_Instance = nullptr;
UpdateObject* UpdateObject::OUT_Instance = nullptr;
void UpdateObject::Update()
{
	if (my_interface != nullptr) {
		my_interface->Update();
		ASSERT(glGetError() == GL_NO_ERROR, "Opengl Error");
	}
	if (my_texture != nullptr) {
		my_texture->Update();
		ASSERT(glGetError() == GL_NO_ERROR, "Opengl Error");
	}
	if (my_mesh != nullptr) {
		my_mesh->Update();
		ASSERT(glGetError() == GL_NO_ERROR, "Opengl Error");
	}
	if (my_shader != nullptr) {
		my_shader->Update();
		ASSERT(glGetError() == GL_NO_ERROR, "Opengl Error");
	}
	if (my_transform != nullptr) {
		my_transform->Update();
		ASSERT(glGetError() == GL_NO_ERROR, "Opengl Error");
	}
	reset();
}
