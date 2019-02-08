#include "Component.h"
#include "UpdateRObject.h"
bool Component::Update()
{
	if (this->type == MESH_WORD) {
		UpdateRObject::IN_Instance->SetMesh(static_cast<GStar::MeshComponent*> (this));
	}
	else if (this->type == SHADER_WORD) {
		UpdateRObject::IN_Instance->SetShader(static_cast<GStar::ShaderComponent*> (this));
	}
	else if (this->type == TEXTURE_WORD) {
		UpdateRObject::IN_Instance->SetTexture(static_cast<GStar::TextureComponent*> (this));
	}
	return false;
}
