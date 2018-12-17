#include "Shader.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include"ConsolePrint.h"
#include "Matrix4.h"
#include "HeapManager.h"
#include "Data.h"
//This will return nullptr as fail, dynamically allocated remember to delete it.
Shader * Shader::Create(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	Shader* result = new Shader();
	bool successful = true;
	if (result->CreateShader(result->ReadShader(vertexPath, fragmentPath, successful), successful)) {
		return result;
	}
	return nullptr;
}


void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const GStar::MyString & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.GetString()), (int)value);
}

void Shader::setInt(const GStar::MyString & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.GetString()), (int)value);
}

void Shader::setFloat(const GStar::MyString & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.GetString()), value);
}

void Shader::setMat4(const GStar::MyString &name, const GStar::Matrix4& value, unsigned int Flip) const
{
	float temparray[16];
	unsigned int transformloc = glGetUniformLocation(this->ID, name.GetString());
	GStar::Matrix4::value_ptr(value, temparray);
	glUniformMatrix4fv(transformloc, 1, Flip, temparray);
}


unsigned int Shader::CompileShader(GStar::MyString & source, unsigned int type,bool& successful)
{
	const char* ShaderCode = source.GetString();
	unsigned int result;
	int success;
	char infoLog[256];
	
	result = glCreateShader(type);
	glShaderSource(result, 1, &ShaderCode, NULL); // Load the vertex shader 2 is numbers of strings, 4 NULL means null terminated
	glCompileShader(result);
	glGetShaderiv(result, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(result, 256, NULL, infoLog);
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "%s failed %s\n", (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"),infoLog);
		successful = false;
	}
	return result;
}

Shader::ShaderSource Shader::ReadShader(const GLchar * vertexPath, const GLchar * fragmentPath, bool& successful)
{
	// retrieve the vertex/fragment source code from filepath
	GStar::MyString vertexCode;
	GStar::MyString fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exception:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//open file
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//read file's buffer conetents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//Close file handles
		vShaderFile.close();
		fShaderFile.close();
		//convert stream into string
		vertexCode = vShaderStream.str().c_str();
		fragmentCode = fShaderStream.str().c_str();

	}
	catch (std::ifstream::failure e) {
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "SHADER::FILE_NOT_SUCCESFULLY_READ\n");
		successful = false;
	}
	//Convert to char* string
	return { vertexCode,fragmentCode };
}

bool Shader::CreateShader(Shader::ShaderSource && source, bool& successful)
{
	this->uniqueid = GStar::MyString::hash_str(source.FragmentSource.GetString());
	char infoLog[256];
	int success;
	unsigned int vertex = CompileShader(source.VertexSource, GL_VERTEX_SHADER, successful);
	unsigned int fragment = CompileShader(source.FragmentSource, GL_FRAGMENT_SHADER, successful);
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//chech link error
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 256, NULL, infoLog);
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "%s\n", infoLog);
		successful = false;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return successful;
}
