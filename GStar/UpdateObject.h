#pragma once
#include"MeshComponent.h"
#include"TextureComponent.h"
#include"ShaderComponent.h"
//Two instance update one present one
class UpdateObject {
public:
	static UpdateObject* OUT_Instance;
	static UpdateObject* IN_Instance;
	void Update();
	inline void SetMesh(const GStar::MeshComponent* mesh) { my_mesh = mesh;}
	inline void SetTexture(const GStar::TextureComponent* textur) { my_texture = textur; }
	inline void SetShader(const GStar::ShaderComponent* shader) { my_shader = shader; }
	inline void reset() { my_mesh = nullptr; my_shader = nullptr; my_texture = nullptr; }
	UpdateObject() :my_mesh(nullptr), my_texture(nullptr), my_shader(nullptr) {}
private:
	const GStar::MeshComponent* my_mesh;
	const GStar::TextureComponent* my_texture;
	const GStar::ShaderComponent* my_shader;
};