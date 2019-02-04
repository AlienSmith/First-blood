#include "Component.h"
#include "UpdateRObject.h"
bool Component::Update()
{
	if (!UpdateRObject::OUT_Instance && !UpdateRObject::IN_Instance) {
		UpdateRObject::Initialize();
	}
	if (this->type == MESH_WORD) {
		UpdateRObject::IN_Instance->SetMesh(static_cast<GStar::MeshComponent*> (this));
	}
	else if (this->type == SHADER_WORD) {
		UpdateRObject::IN_Instance->SetShader(static_cast<GStar::ShaderComponent*> (this));
	}
	else if (this->type == TEXTURE_WORD) {
		UpdateRObject::IN_Instance->SetTexture(static_cast<GStar::TextureComponent*> (this));
	}
	else if (this->type == TRANSFORM_WORD) {
		UpdateRObject::IN_Instance->SetTransform(static_cast<GStar::TransformComponent*>(this));
	}
	else if (this->type == INTERFACE_WORD) {
		//Use reinterpret_cast here will lead to error infomation lost
		//GStar::InterfaceComponent* TEMP = static_cast<GStar::InterfaceComponent*>(this);
		UpdateRObject::IN_Instance->SetInterface(static_cast<GStar::InterfaceComponent*>(this));
	}
	return false;
}
