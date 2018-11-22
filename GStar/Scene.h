#pragma once
#include<glad\glad.h>
#include<GLFW\glfw3.h>
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
	Scene(const Scene& other) = delete;
	Scene& operator = (const Scene& other) = delete;
	inline const Shader& Shaders() const { return my_shaders; }
	inline GLFWwindow* Window() { return window; }
	inline bool UpdateEnd() {
		glfwSwapBuffers(window);// swamp color buffer. and show what drawed in this iteration
		glfwPollEvents();// checks events update functions
		return true;
	}
	inline void TerminateWindow() {
		glfwTerminate();
		return;
	}
	inline void SetView(GStar::Matrix4& other) { view = other; }
	void UpdateTime();
	//Call UpdateTime first and only once 
	inline const float Deltatime()const { return deltaTime; }
private:
	bool SetupWindow();
	bool LoadObject();
	unsigned int LoadTexture(const char file[]);
	bool SetPespective();
	Scene();
	GStar::Matrix4 projection;
	GStar::Matrix4 view;
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