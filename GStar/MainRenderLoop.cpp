#include"Scene.h"
#include"View.h"
#include"Controller.h"
Scene* myScene = Scene::Create();
Controller myController(myScene);
View myView(myScene);
void mouse_call(GLFWwindow * window, double xpos, double ypos);
void framebuffer_size_call(GLFWwindow * windwo, int width, int height);
void MainEntrance() {
	//Set up 
	//Bind CallBack Function
	glfwSetFramebufferSizeCallback(myScene->Window(), framebuffer_size_call);
	glfwSetCursorPosCallback(myScene->Window(), mouse_call);
	//RenderLoop
	while (!glfwWindowShouldClose(myScene->Window())) {
		myScene->UpdateTime();
		myController.processInput(myScene->Window());
		myController.Update();
		myScene->Update();
		myView.Update();
		myScene->UpdateEnd();
	}
	myScene->TerminateWindow();
	delete myScene;
}
void mouse_call(GLFWwindow * window, double xpos, double ypos)
{
	myController.mouse_callBack(window, xpos, ypos);
}
void framebuffer_size_call(GLFWwindow * windwo, int width, int height)
{
	myController.framebuffer_size_callback(windwo, width, height);
}