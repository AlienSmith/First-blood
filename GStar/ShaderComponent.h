#pragma once
#include"Component.h"
class Shader;
const struct ShaderParameters;
namespace GStar {
	class ShaderComponent:public Component {
	public:
		const static char TypeWord() {
			return SHADER_WORD;
		}
		bool Initialize(const ShaderParameters& parameters);
		//Mesh do not have these functions
		bool Update() const;
		inline bool Terminate() { return true; }
		ShaderComponent():Component(SHADER_WORD),my_shader(nullptr) {}
		ShaderComponent(const ShaderParameters& parameters) :Component(SHADER_WORD), my_shader(nullptr) {
		
		}
	private:
		Shader* my_shader;
	};
}