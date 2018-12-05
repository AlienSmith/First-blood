#pragma once
#include "SingleLinkedList.h"
class Shader;
const struct ShaderParameters;
namespace GStar {
	class ShaderManager {
	public:
		static ShaderManager* Instance() {
			if (instance = nullptr) {
				GStar::ShaderManager::instance = new GStar::ShaderManager();
			}
			return instance;
		}
		Shader* GetShader(const ShaderParameters& parameters);
	private:
		ShaderManager():ShaderSource(GStar::SingleLinkedList<Shader*>()), size(0) {}
		Shader* CreateShader(const ShaderParameters& parameters);
		static ShaderManager* instance;
		GStar::SingleLinkedList<Shader*> ShaderSource;
		int size;
	};
}