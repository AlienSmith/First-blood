#include "ShaderManger.h"
#include "Data.h"
#include "MyString.h"
#include "Shader.h"
GStar::ShaderManager* GStar::ShaderManager::instance = nullptr;
Shader * GStar::ShaderManager::GetShader(const ShaderParameters & parameters)
{
	unsigned int currentId = GStar::MyString::hash_str(parameters.vs);
	ShaderSource.Resetcurrent();
	Shader* current;
	while (ShaderSource.HasNext()) {
		current = ShaderSource.GetNextNode()->GetData();
		if (currentId == current->GetUnId()) {
			return current;
		}
		ShaderSource.Move();
	}
	current = CreateShader(parameters);
	return current;
}

Shader * GStar::ShaderManager::CreateShader(const ShaderParameters & parameters)
{
	Shader* temp = Shader::Create(parameters.vs, parameters.fs);
	ShaderSource.Push(temp);
	return temp;
}
