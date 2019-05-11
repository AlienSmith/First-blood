#include "Scene.h"
#include "Controller.h"
#include "Camera.h"
#include "GSTime.h"
//For look into other direction
void Controller::mouse_callBack(GLFWwindow * window, double xpos, double ypos)
{
	if (window) {
		xoffset = ((float)xpos - lastX)*sensitivity;
		yoffset = (lastY - (float)ypos)*sensitivity;
		lastX = (float)xpos;
		lastY = (float)ypos;
		my_camera.setroll(my_camera.getroll() - yoffset);
		my_camera.setpitch(my_camera.getpitch() - xoffset);
		my_camera.RotateUpdate();
	}
}

void Controller::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	//For move around
	my_camera.processInput(window,(float)GStar::GSTime::Instance().GetdeltaTime() );
}

void Controller::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	if (window) {
		glViewport(0, 0, width, height);// Viewport and window are different.
	}
}

void Controller::Update()
{
	processInput(my_Scene->Window());
	my_camera.Update();
	my_Scene->SetView(my_camera.view);
}
