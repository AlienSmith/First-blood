#include "UpdateObject.h"

void UpdateObject::Update()
{
	if (my_mesh) {
		my_mesh->Update();
	}
	if (my_shader) {
		my_shader->Update();
	}
	if (my_texture) {
		my_texture->Update();
	}
}
