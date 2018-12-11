#include "Component.h"
#include "UpdateObject.h"
bool Component::Update()
{
	if (!UpdateObject::OUT_Instance && !UpdateObject::IN_Instance) {
		UpdateObject::Initialize();
	}
	if (this->type == MESH_WORD) {
		UpdateObject::IN_Instance->SetMesh(static_cast<GStar::MeshComponent*> (this));
	}
	else if (this->type == SHADER_WORD) {
		UpdateObject::IN_Instance->SetShader(static_cast<GStar::ShaderComponent*> (this));
	}
	else if (this->type == TEXTURE_WORD) {
		UpdateObject::IN_Instance->SetTexture(static_cast<GStar::TextureComponent*> (this));
	}
	else if (this->type == TRANSFORM_WORD) {
		UpdateObject::IN_Instance->SetTransform(static_cast<GStar::TransformComponent*>(this));
	}
	else if (this->type == INTERFACE_WORD) {
		//Use reinterpret_cast here will lead to error infomation lost
		//GStar::InterfaceComponent* TEMP = static_cast<GStar::InterfaceComponent*>(this);
		UpdateObject::IN_Instance->SetInterface(static_cast<GStar::InterfaceComponent*>(this));
	}
	return false;
}
