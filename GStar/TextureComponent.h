#pragma once
#include"Component.h"
#include"SingleLinkedList.h"
class Texture;
namespace GStar {
	class TextureParameters;
	class TextureComponent :public Component {
	public:
		const static char TypeWord() {
			return 't';
		}
		bool Initialize(const TextureParameters& parameters);
		//Mesh do not have these functions
		inline bool Update() {} 
		inline bool Terminate() {}
		TextureComponent() :my_textures(SingleLinkedList<Texture*>()) {}
	private:
		SingleLinkedList<Texture*> my_textures;
	};
}