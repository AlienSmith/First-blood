#pragma once
#include"Component.h"
class Shader;
namespace GStar {
	class ShaderParameters;
	class ShaderComponent:public Component {
	public:
		const static char TypeWord() {
			return 's';
		}
		bool Initialize(const ShaderParameters& parameters);
		//Mesh do not have these functions
		inline bool Update() {}
		inline bool Terminate() {}
		ShaderComponent():my_shader(nullptr) {}
	private:
		Shader* my_shader;
	};
}