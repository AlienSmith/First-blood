#pragma once
#include"Component.h"
#include"Mesh.h"
struct MeshParameters;
namespace GStar {
	class MeshComponent : public Component {
	public:
		const static char TypeWord() {
			return MESH_WORD;
		}
		bool Initialize(const MeshParameters& parameters);
		//Mesh do not have these functions
		bool Update() const;
		bool Terminate() { return true; }
		MeshComponent():Component(MESH_WORD) {}
		MeshComponent(const MeshParameters& parameters) :Component(MESH_WORD) {
			this->Initialize(parameters);
		}
		inline GStar::Mesh GetMeshInfo() { return my_mesh; }
	private:
		GStar::Mesh my_mesh;
	};
}