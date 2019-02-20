#include "TextureComponent.h"
#include "TextureManager.h"
#include "Texture.h"
#include "Scene.h"
bool GStar::TextureComponent::Initialize(const TextureParameters & parameters)
{
	my_textures.Push(GStar::TextureManager::Instance()->GetTexture(parameters));
	return true;
}

bool GStar::TextureComponent::Initialize(const texturedata & parameters)
{
	Texture current;
	current.SetTextureID(Scene::Create()->LoadTexture(parameters));
	my_textures.Push(current);
	return true;
}

bool GStar::TextureComponent::Update()
{
	//need to include everything in the header to use glActivateTexture
	my_textures.Resetcurrent();
	glActiveTexture(GL_TEXTURE0); // activate the texture unit 0
	glBindTexture(GL_TEXTURE_2D, my_textures.GetNext().myTextureID()); // bind name
	my_textures.Move();
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, my_textures.GetNext().myTextureID());
	//????
	return true;
}
