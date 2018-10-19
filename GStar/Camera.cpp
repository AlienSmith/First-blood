#include "Camera.h"
#include"GLFW/glfw3.h"
#include "Coordinate.h"
void GStar::Camera::Set_Target(GStar::Vector3 Target)
{
	cameraTarget = Target;
	//TODO Seperate this part as a function
	CameraFront = cameraPos - cameraTarget;
	CameraFront.Normalize();
	NeedUpdate = true;
}

void GStar::Camera::Set_Pos(GStar::Vector3 Target)
{
	cameraPos = Target;
	CameraFront = cameraPos - cameraTarget;
	CameraFront.Normalize();
	NeedUpdate = true;
}


void GStar::Camera::Update()
{
	if (NeedUpdate) {
		view = Lookat(Vector3(0, 1, 0),CameraFront,cameraPos,CameraUp,CameraRight);
		NeedUpdate = false;
	}	
}

void GStar::Camera::RotateUpdate()
{
	float z = cos(GStar::radians(roll)) * cos(GStar::radians(pitch));
	float y = sin(GStar::radians(roll));
	float x = cos(GStar::radians(roll)) * sin(GStar::radians(pitch));
	//TODO add a seter for Vector3
	CameraFront = Vector3(x, y, z);
	CameraFront.Normalize();
	NeedUpdate = true;
}

GStar::Camera::Camera(GStar::Vector3 camPos, GStar::Vector3 camTarget):cameraPos(camPos),cameraTarget(camTarget)
{
	NeedUpdate = true;
	CameraFront = cameraPos - cameraTarget;
	CameraFront.Normalize();
	Update();
}

GStar::Camera::Camera()
{
	RotateUpdate();
	CameraFront = cameraPos - cameraTarget;
	CameraFront.Normalize();
	Update();
}

GStar::Matrix4 GStar::Camera::Lookat(const GStar::Vector3& worldup, const GStar::Vector3& reverseDirection, const GStar::Vector3& position)
{
	GStar::Vector3 right = GStar::Vector3::Cross(worldup, reverseDirection);
	GStar::Vector3 up = GStar::Vector3::Cross(reverseDirection, right);
	array_ff templ = IDENTICAL_MATRIX;
	templ[0][0] = right.x();
	templ[1][0] = right.y();
	templ[2][0] = right.z();
	templ[0][1] = up.x();
	templ[1][1] = up.y();
	templ[2][1] = up.z();
	templ[0][2] = reverseDirection.x();
	templ[1][2] = reverseDirection.y();
	templ[2][2] = reverseDirection.z();

	templ[0][3] = -position.x();
	templ[1][3] = -position.y();
	templ[2][3] = -position.z();
	GStar::Matrix4 tempmatrxl = GStar::Matrix4(templ);
	tempmatrxl = tempmatrxl.I();
	return tempmatrxl;
}

GStar::Matrix4 GStar::Camera::Lookat(const GStar::Vector3& worldup, const GStar::Vector3& reverseDirection, const GStar::Vector3& position, GStar::Vector3& up, GStar::Vector3& right)
{
	right = GStar::Vector3::Cross(worldup, reverseDirection);
	up = GStar::Vector3::Cross(reverseDirection, right);
	array_ff templ = IDENTICAL_MATRIX;
	templ[0][0] = right.x();
	templ[0][1] = right.y();
	templ[0][2] = right.z();
	templ[1][0] = up.x();
	templ[1][1] = up.y();
	templ[1][2] = up.z();
	templ[2][0] = -reverseDirection.x();
	templ[2][1] = -reverseDirection.y();
	templ[2][2] = -reverseDirection.z();

	templ[3][0] = -right.Dot(position);
	templ[3][1] = -up.Dot(position);
	templ[3][2] = -reverseDirection.Dot(position);
	GStar::Matrix4 tempmatrxl = GStar::Matrix4(templ);
	return tempmatrxl;
}

void GStar::Camera::processInput(GLFWwindow * window, float deltatime)
{
	float cameraspeed = CameraMoveSpeed * deltatime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos -= cameraspeed * CameraFront;
		NeedUpdate = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos += cameraspeed * CameraFront;
		NeedUpdate = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= cameraspeed * CameraRight;
		NeedUpdate = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += cameraspeed * CameraRight;
		NeedUpdate = true;
	}
}


