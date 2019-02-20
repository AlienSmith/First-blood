#pragma once
#include"Component.h"
#include"SingleLinkedList.h"
#include "Texture.h"
#include "Scene.h"
const struct TextureParameters;
namespace GStar {
	struct texturedata;
	class TextureComponent :public Component {
	public:
		const static char TypeWord() {
			return TEXTURE_WORD;
		}
		bool Initialize(const TextureParameters& parameters);
		bool Initialize(const texturedata& parameters);
		//Mesh do not have these functions
		bool Update() ;
		bool Terminate() { return true; }
		TextureComponent() :Component(TEXTURE_WORD),my_textures(SingleLinkedList<GStar::Texture>()) {}
	private:
		SingleLinkedList<GStar::Texture> my_textures;
	};
}