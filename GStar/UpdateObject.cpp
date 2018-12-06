#include "UpdateObject.h"
UpdateObject* UpdateObject::IN_Instance = nullptr;
UpdateObject* UpdateObject::OUT_Instance = nullptr;
void UpdateObject::Update()
{
	if (my_texture) {
		my_texture->Update();
		ASSERT(glGetError() == GL_NO_ERROR, "Opengl Error");
	}
	if (my_mesh) {
		my_mesh->Update();
		ASSERT(glGetError() == GL_NO_ERROR, "Opengl Error");
	}
	if (my_shader) {
		my_shader->Update();
		ASSERT(glGetError() == GL_NO_ERROR, "Opengl Error");
	}
	if (my_transform) {
		my_transform->Update();
		ASSERT(glGetError() == GL_NO_ERROR, "Opengl Error");
	}
}
