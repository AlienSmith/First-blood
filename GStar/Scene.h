#pragma once
#include"Camera.h"
#include"Shader.h"
class GLFWwindow;
class Scene {
public:
	static Scene* Create();
private:
	bool SetupWindow();
	bool LoadObject();
	Scene();
	GStar::Camera my_camera; //Generate camera Matrix
	GStar::Matrix4 projection;
	GStar::Matrix4 model;
	Shader my_shaders;
	float deltaTime;
	float LastFrame;
	float currentFrame;
	GLFWwindow* window;
};