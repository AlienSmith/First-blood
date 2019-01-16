#pragma once
#include "SingleLinkedList.h"
#include "Mesh.h"
#include "Data.h"
#define MeshPrimeA 54059 /* a prime */
#define MeshPrimeB 76963 /* another prime */
#define MeshPrimeC 86969 /* yet another prime */
#define MeshFIRSTH 37 /* also prime */
#define MeshOffset 1.0f
//This class will load the mesh
namespace GStar {
	class MyString;
	class MeshManager {
	public:
		static unsigned int MeshGetId(const MeshParameters& parameters) {
			unsigned int h = MeshFIRSTH;
			int count = 0;
			while (count < parameters.numelements) {
				h = (h * MeshPrimeA) + (((unsigned int)parameters.data[0] + MeshOffset) * MeshPrimeB);
				count++;
			}
			return h % MeshPrimeC;
		}
		static MeshManager* Instance() {
			if (instance == nullptr) {
				GStar::MeshManager::instance = new GStar::MeshManager();
			}
			return instance;
		}
		GStar::Mesh GetMesh(const MeshParameters& parameters);
		MeshManager() :MeshSource(GStar::SingleLinkedList<GStar::Mesh>()), size(0) {}
	private:
		unsigned int LoadMesh(const MeshParameters& parameters);
		static MeshManager* instance;
		GStar::SingleLinkedList<GStar::Mesh> MeshSource;
		int size;
	};
}