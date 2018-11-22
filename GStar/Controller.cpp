#include "Scene.h"
#include "Controller.h"
//For look into other direction
void Controller::mouse_callBack(GLFWwindow * window, double xpos, double ypos)
{
	xoffset = (xpos - lastX)*sensitivity;
	yoffset = (lastY - ypos)*sensitivity;
	lastX = xpos;
	lastY = ypos;
	my_camera.setroll(my_camera.getroll() - yoffset);
	my_camera.setpitch(my_camera.getpitch() - xoffset);
	my_camera.RotateUpdate();
}

void Controller::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	//For move around
	my_camera.processInput(window, my_Scene->Deltatime());
}

void Controller::framebuffer_size_callback(GLFWwindow * windwo, int width, int height)
{
	glViewport(0, 0, width, height);// Viewport and window are different.
}

void Controller::Update()
{
	processInput(my_Scene->Window());
	my_camera.Update();
	my_Scene->SetView(my_camera.view);
}
