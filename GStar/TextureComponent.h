#pragma once
#include"Component.h"
#include"SingleLinkedList.h"
#include "Texture.h"
#include "Scene.h"
const struct TextureParameters;
namespace GStar {
	class TextureComponent :public Component {
	public:
		const static char TypeWord() {
			return TEXTURE_WORD;
		}
		bool Initialize(const TextureParameters& parameters);
		//Mesh do not have these functions
		inline bool Update() ;
		inline bool Terminate() { return true; }
		TextureComponent() :Component(TEXTURE_WORD),my_textures(SingleLinkedList<GStar::Texture>()) {}
	private:
		SingleLinkedList<GStar::Texture> my_textures;
	};
}