#pragma once
namespace GStar {
	class Mesh {
	public:
		Mesh() :uniqueId(0), my_VAO(0) {}
		inline void	SetID(unsigned int Id) { uniqueId = Id; }
		inline void SetVAO(unsigned int VAO) { my_VAO = VAO; }
		inline unsigned int myId() const { return uniqueId; }
		inline unsigned int myVAO() const { return my_VAO; }
	private:
		unsigned int uniqueId;
		unsigned int my_VAO;
	};
}