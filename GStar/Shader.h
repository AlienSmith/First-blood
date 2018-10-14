#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include<string>
//TODO use MyString Instead of std::string
namespace GStar { class Matrix4; };
class Shader {
public:
	// This program ID
	unsigned int ID;
	//constructor reads and builds the shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//use activate the shader
	void use();
	//utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, const GStar::Matrix4& value);
private:
	struct ShaderSource {
		std::string VertexSource;
		std::string FragmentSource;
	};
	unsigned int CompileShader(std::string& source, unsigned int type);
	ShaderSource ReadShader(const GLchar * vertexPath, const GLchar * fragmentPath);
	void CreateShader(Shader::ShaderSource&& source);
};
#endif