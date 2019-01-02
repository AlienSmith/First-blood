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
		lastX(400), lastY(300),
		myScene(Scene::Create()),
		myController(new Controller(myScene)),
		KeyBoardInput(GStar::EventManager::Instance()->RegisterEvent("KeyBoardInput")),
		MouseInput(GStar::EventManager::Instance()->RegisterEvent("MouseInput")){}
	void Run();
	static MainEntrance* instance;
	const static float MouseSensitivity;
	double lastX;
	double lastY;
	Scene* myScene;
	Controller* myController;
	GStar::EventUnite& KeyBoardInput;
	GStar::EventUnite& MouseInput;
	static void mouse_call(GLFWwindow* window, double xpos, double ypos);
	static void framebuffer_size_call(GLFWwindow* window, int width, int height);
	static void keyboard_call(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void CleanScreen();
};