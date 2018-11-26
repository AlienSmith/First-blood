#pragma once
#include"Component.h"
#include"Mesh.h"
struct MeshParameters;
namespace GStar {
	class MeshComponent : public Component {
	public:
		const static char TypeWord() {
			return 'm';
		}
		bool Initialize(const MeshParameters& parameters);
		//Mesh do not have these functions
		inline bool Update() {} 
		inline bool Terminate() {}
		MeshComponent() {}
	private:
		GStar::Mesh my_mesh;
	};
}