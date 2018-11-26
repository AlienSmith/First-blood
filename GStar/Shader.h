#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include "MyString.h"
//TODO use MyString Instead of std::string
//TODO change ID to private
//For release Use pointer to string and delete it after success compile
namespace GStar { class Matrix4; };
class Shader {
public:
	static void* ShadersHeap;
	static void InitalizeHeap();
	static Shader* Create(const GLchar * vertexPath, const GLchar * fragmentPath);
	static void Terminate();
	// This program ID
	unsigned int ID;
	//constructor reads and builds the shader
	//use activate the shader
	void use();
	//utility uniform functions
	void setBool(const GStar::MyString &name, bool value) const;
	void setInt(const GStar::MyString &name, int value) const;
	void setFloat(const GStar::MyString &name, float value) const;
	void setMat4(const GStar::MyString &name, const GStar::Matrix4& value, unsigned int Flip) const;
	void* operator new (size_t i_size);
	void operator delete(void* i_ptr);
	//TODO after the demeo can run put the other ID into private section and write geters and seters.
	inline unsigned int GetUnId() const { return uniqueid; }
	void SetUnId(const unsigned int ID) { uniqueid = ID; }
private:
	//The uniqueid is generated by the hashcode of the vertextstring.
	unsigned int uniqueid;
	Shader(){}
	struct ShaderSource {
		GStar::MyString VertexSource;
		GStar::MyString FragmentSource;
	};
	unsigned int CompileShader(GStar::MyString& source, unsigned int type, bool& successful);
	ShaderSource ReadShader(const GLchar * vertexPath, const GLchar * fragmentPath, bool& successful);
	bool CreateShader(Shader::ShaderSource&& source, bool& successful);
};
#endif