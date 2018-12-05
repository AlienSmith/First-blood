#pragma once
namespace GStar {
	class Mesh {
	public:
		//TODO override allocation if data grow
		static void* MeshHeap;
		static void InitializeHeap();
		static void Terminate();

		inline void	SetID(unsigned int Id) { uniqueId = Id; }
		inline void SetVAO(unsigned int VAO) { my_VAO = VAO; }
		inline void SetIndex(unsigned int index) { Index = index; }
		inline unsigned int myId() const { return uniqueId; }
		inline unsigned int myVAO() const { return my_VAO; }
		inline unsigned int TriangleIndex() const { return Index; }
	private:
		unsigned int Index;
		unsigned int uniqueId;
		unsigned int my_VAO;
	};
}