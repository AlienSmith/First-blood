#include "Component.h"
#include "UpdateObject.h"
bool Component::Update()
{
	if (!UpdateObject::OUT_Instance && !UpdateObject::IN_Instance) {
		UpdateObject::Initialize();
	}
	if (this->type == MESH_WORD) {
		UpdateObject::IN_Instance->SetMesh(reinterpret_cast<GStar::MeshComponent*> (this));
	}
	else if (this->type == SHADER_WORD) {
		UpdateObject::IN_Instance->SetShader(reinterpret_cast<GStar::ShaderComponent*> (this));
	}
	else if (this->type == TEXTURE_WORD) {
		UpdateObject::IN_Instance->SetTexture(reinterpret_cast<GStar::TextureComponent*> (this));
	}
	else if (this->type == TRANSFORM_WORD) {
		UpdateObject::IN_Instance->SetTransform(reinterpret_cast<GStar::TransformComponent*>(this));
	}
	else if (this->type == INTERFACE_WORD) {
		UpdateObject::IN_Instance->SetInterface(reinterpret_cast<GStar::InterfaceComponent*>(this));
	}
	return false;
}
