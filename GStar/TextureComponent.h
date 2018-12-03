#pragma once
#include"Component.h"
#include"SingleLinkedList.h"
namespace GStar {
	class Texture;
	class TextureParameters;
	class TextureComponent :public Component {
	public:
		const static char TypeWord() {
			return TEXTURE_WORD;
		}
		bool Initialize(const TextureParameters& parameters);
		//Mesh do not have these functions
		inline bool Update() const{} 
		inline bool Terminate() {}
		TextureComponent() :Component(TEXTURE_WORD),my_textures(SingleLinkedList<Texture>()) {}
	private:
		SingleLinkedList<Texture> my_textures;
	};
}