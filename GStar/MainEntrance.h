#pragma once
#include"Scene.h"
#include"View.h"
#include"Controller.h"
class MainEntrance {
public:
	static void SetUpAndRun();
private:
	MainEntrance() :
		myScene(Scene::Create()),
		myController(new Controller(myScene)) {}
	void Run();
	static MainEntrance* instance;
	Scene* myScene;
	Controller* myController;
	static void mouse_call(GLFWwindow* window, double xpos, double ypos);
	static void framebuffer_size_call(GLFWwindow* window, int width, int height);
	static void CleanScreen();
};