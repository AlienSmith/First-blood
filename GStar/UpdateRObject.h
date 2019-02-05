#pragma once
#include"MeshComponent.h"
#include"TextureComponent.h"
#include"ShaderComponent.h"
#include"TransformComponent.h"
#include"InterfaceComponent.h"
//Two instance update one present one
class UpdateRObject {
public:
	static UpdateRObject* OUT_Instance;
	static UpdateRObject* IN_Instance;
	static void Initialize() {
		OUT_Instance = new UpdateRObject();
		IN_Instance = new UpdateRObject();
	}
	static void Terminate() {
		delete OUT_Instance;
		delete IN_Instance;
	}
	static void Swamp() {
		UpdateRObject* temp = OUT_Instance;
		OUT_Instance = IN_Instance;
		IN_Instance = temp;
	}
	void Update();
	inline void SetMesh( GStar::MeshComponent* mesh) { my_mesh = mesh;}
	inline void SetTexture( GStar::TextureComponent* textur) { my_texture = textur; }
	inline void SetShader( GStar::ShaderComponent* shader) { my_shader = shader; }
	inline void SetTransform(GStar::TransformComponent* transform) { my_transform = transform; }
	inline void reset() { my_mesh = nullptr; my_shader = nullptr; my_texture = nullptr; my_transform = nullptr; }
	UpdateRObject() :my_mesh(nullptr), my_texture(nullptr), my_shader(nullptr),my_transform(nullptr) {}
	GStar::ShaderComponent* GetShaderComponent() { return this->my_shader; }
	GStar::TransformComponent* GetTransformComponent() { return my_transform; }
	GStar::MeshComponent* GetMeshComponent() { return my_mesh; };
private:
	GStar::MeshComponent* my_mesh;
	GStar::TextureComponent* my_texture;
	GStar::ShaderComponent* my_shader;
	GStar::TransformComponent* my_transform;
};