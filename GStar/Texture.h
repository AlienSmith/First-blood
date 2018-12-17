#pragma once
namespace GStar {
	class Texture {
	public:
		//TODO override allocation if data grow

		inline void	SetunID(unsigned int Id) { uniqueId = Id; }
		inline void SetTextureID(unsigned int VAO) { my_TextureID = VAO; }
		inline unsigned int myunId() const { return uniqueId; }
		inline unsigned int myTextureID() const { return my_TextureID; }
	private:
		unsigned int uniqueId;
		unsigned int my_TextureID;
	};
}