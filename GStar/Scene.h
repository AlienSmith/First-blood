#pragma once
#include"Camera.h"
#include"Shader.h"
//TODO use heap manager instead of the C++ new
//TODO use Single linked list to store multiple textures and Object;
//TODO add Creat function to Shader class
class GLFWwindow;
class Scene {
public:
	static Scene* Create();
	bool Update();
private:
	bool SetupWindow();
	bool LoadObject();
	unsigned int LoadTexture(const char file[]);
	bool SetPespective();
	Scene();
	GStar::Camera my_camera; //Generate camera Matrix
	GStar::Matrix4 projection;
	GStar::Matrix4 model;
	Shader my_shaders;
	float deltaTime;
	float LastFrame;
	float currentFrame;
	GLFWwindow* window;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texture1;
	unsigned int texture2;
};