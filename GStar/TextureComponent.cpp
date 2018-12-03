#include "TextureComponent.h"
#include "TextureManager.h"
#include "Texture.h"
bool GStar::TextureComponent::Initialize(const TextureParameters & parameters)
{
	my_textures.Push(GStar::TextureManager::Instance()->GetTexture(parameters));
	return true;
}
