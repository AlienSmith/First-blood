#pragma once
namespace GStar {
	class Texture {
	public:
		Texture() :uniqueId(0), my_TextureID(0) {}
		inline void	SetID(unsigned int Id) { uniqueId = Id; }
		inline void SetTextureID(unsigned int VAO) { my_TextureID = VAO; }
		inline unsigned int myId() const { return uniqueId; }
		inline unsigned int myTextureID() const { return my_TextureID; }
	private:
		unsigned int uniqueId;
		unsigned int my_TextureID;
	};
}