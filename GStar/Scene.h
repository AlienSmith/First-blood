#pragma once
#include"GLINCLUDE.h"
#include"Camera.h"
#include"Shader.h"
#include"HeapManager.h"
//TODO use heap manager instead of the C++ new
//TODO use Single linked list to store multiple textures and Object;
//TODO add Creat function to Shader class
struct MeshParameters;
struct TextureParameters;
class GLFWwindow;
class Scene {
public:
	static Scene* Create();
	bool Update();
	Scene(const Scene& other) = delete;
	Scene& operator = (const Scene& other) = delete;
	inline const Shader& Shaders() const { return *my_shaders; }
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
	inline void UpdateView(){ my_shaders->setMat4("view", view, GL_FALSE); }
	virtual ~Scene() { delete my_shaders; }
	unsigned int LoadMesh(const MeshParameters& parameters) const;
	unsigned int LoadTexture(const TextureParameters& parameters) const;
	const GStar::Matrix4& getProjection() const { return projection; }
	const GStar::Matrix4& getview() const { return view; }
	// This is wired 
private:
	static Scene* Instance;
	bool SetupWindow();
	bool LoadObject();
	bool SetPespective();
	bool CompileShader();
	Scene();
	GStar::Matrix4 projection;
	GStar::Matrix4 view;
	Shader* my_shaders;
	float deltaTime;
	float LastFrame;
	float currentFrame;
	GLFWwindow* window;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texture1;
	unsigned int texture2;
};