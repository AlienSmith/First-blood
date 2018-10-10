#include "Shader.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include"ConsolePrint.h"
Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	CreateShader(ReadShader(vertexPath, fragmentPath));
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

unsigned int Shader::CompileShader(std::string & source, unsigned int type)
{
	const char* ShaderCode = source.c_str();
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
	}
	return result;
}

Shader::ShaderSource Shader::ReadShader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	// retrieve the vertex/fragment source code from filepath
	std::string vertexCode;
	std::string fragmentCode;
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
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e) {
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "SHADER::FILE_NOT_SUCCESFULLY_READ\n");
	}
	//Convert to char* string
	return { vertexCode,fragmentCode };
}

void Shader::CreateShader(Shader::ShaderSource && source)
{
	char infoLog[256];
	int success;
	unsigned int vertex = CompileShader(source.VertexSource, GL_VERTEX_SHADER);
	unsigned int fragment = CompileShader(source.FragmentSource, GL_FRAGMENT_SHADER);
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//chech link error
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 256, NULL, infoLog);
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Error, "%s\n", infoLog);
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
