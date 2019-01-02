#pragma once
#include "Camera.h"
class Scene;
class GLFWwindow;
//Manange call back event and FPS camera
class Controller {
public:
	void mouse_callBack(GLFWwindow* window, double xpos, double ypos);
	void processInput(GLFWwindow* window);
	void framebuffer_size_callback(GLFWwindow * windwo, int width, int height);
	void Update();
	Controller(Scene* scene)
		:my_Scene(scene),
		xoffset(0),
		yoffset(0),
		lastX(400),
		lastY(300),
		sensitivity(0.05f){}
	Controller(const Controller& other) = delete;
	const Controller& operator = (const Controller& other) = delete;
private:
	GStar::Camera my_camera;
	Scene* my_Scene;
	float xoffset;
	float yoffset;
	float lastX;
	float lastY;
	float sensitivity;
};