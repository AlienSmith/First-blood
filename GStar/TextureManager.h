#pragma once
#include "SingleLinkedList.h"
#include "Texture.h"
const struct TextureParameters;
namespace GStar {
	class Texture;
	class TextureManager {
	public:
		static TextureManager* Instance() {
			if (instance == nullptr) {
				GStar::TextureManager::instance = new GStar::TextureManager();
			}
			return instance;
		}
		static unsigned int TextureGetId(const TextureParameters& parameters);
		Texture GetTexture(const TextureParameters& parameters);
		TextureManager() :TextureSource(GStar::SingleLinkedList<GStar::Texture>()), size(0) {}
	private:
		unsigned int LoadTexture(const TextureParameters& parameters);
		static TextureManager* instance;
		GStar::SingleLinkedList<GStar::Texture> TextureSource;
		int size;
	};
}