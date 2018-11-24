#pragma once
#include "SingleLinkedList.h"
#include "Mesh.h"
//This class will load the mesh
namespace GStar {
	class MyString;
	class MeshManager {
	public:
		static MeshManager* Instance() {
			if (instance = nullptr) {
				GStar::MeshManager::instance = new GStar::MeshManager();
			}
			return instance;
		}
		GStar::Mesh GetMesh(const GStar::MyString resource);
		MeshManager() :MeshSource(GStar::SingleLinkedList<GStar::Mesh>()), size(0) {}
	private:
		static MeshManager* instance;
		GStar::SingleLinkedList<GStar::Mesh> MeshSource;
		int size;
	};
}