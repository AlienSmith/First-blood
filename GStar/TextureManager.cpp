#include "TextureManager.h"
#include "Scene.h"
#include "MyString.h"
#include "Data.h"
GStar::TextureManager* GStar::TextureManager::instance = nullptr;
unsigned int GStar::TextureManager::TextureGetId(const TextureParameters & parameters)
{
	return GStar::MyString::hash_str(parameters.textureroute);
}

GStar::Texture GStar::TextureManager::GetTexture(const TextureParameters & parameters)
{
	unsigned int CurrentID = GStar::TextureManager::TextureGetId(parameters);
	TextureSource.Resetcurrent();
	GStar::Texture current;
	while (TextureSource.HasNext()) {
		current = TextureSource.GetNextNode()->GetData();
		if (CurrentID == current.myunId()) {
			return current;
		}
		TextureSource.Move();
	}
	current.SetunID(LoadTexture(parameters));
	current.SetTextureID(CurrentID);
	TextureSource.Push(current);
	return current;
}

unsigned int GStar::TextureManager::LoadTexture(const TextureParameters & parameters)
{
	return 0;
}
