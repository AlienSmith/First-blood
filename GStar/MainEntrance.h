#pragma once
#include"Scene.h"
#include"View.h"
#include"Controller.h"
#include"EventManager.h"
class MainEntrance {
public:
	static void SetUpAndRun();
private:
	MainEntrance() :
		myScene(Scene::Create()),
		myController(new Controller(myScene)),
		KeyBoardInput(GStar::EventManager::Instance()->RegisterEvent("KeyBoardInput")){}
	void Run();
	static MainEntrance* instance;
	Scene* myScene;
	Controller* myController;
	GStar::EventUnite& KeyBoardInput;
	static void mouse_call(GLFWwindow* window, double xpos, double ypos);
	static void framebuffer_size_call(GLFWwindow* window, int width, int height);
	static void keyboard_call(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void CleanScreen();
};