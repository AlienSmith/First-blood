#include "Camera.h"

void GStar::Camera::Set_Target(GStar::Vector3 Target)
{
	cameraTarget = Target;
}

void GStar::Camera::Set_Pos(GStar::Vector3 Target)
{
	cameraPos = Target;
}

void GStar::Camera::Set_Up(GStar::Vector3 Target)
{
	cameraUp = Target;
}

void GStar::Camera::Update()
{
	view = Lookat(cameraRight, cameraUp, cameraDirection, cameraPos);
}

GStar::Camera::Camera(GStar::Vector3 camPos, GStar::Vector3 camTarget):cameraPos(camPos),cameraTarget(camTarget)
{
	cameraDirection = camPos - camTarget;
	cameraDirection.Normalize();
	cameraRight = GStar::Vector3::Cross(up, cameraDirection);
	cameraUp = GStar::Vector3::Cross(cameraDirection, cameraRight);
	Update();
}

GStar::Camera::Camera()
{
	cameraDirection = cameraPos- cameraTarget;
	cameraDirection.Normalize();
	cameraRight = GStar::Vector3::Cross(up, cameraDirection);
	cameraUp = GStar::Vector3::Cross(cameraDirection, cameraRight);
	Update();
}

GStar::Matrix4 GStar::Camera::Lookat(GStar::Vector3 right, GStar::Vector3 up, GStar::Vector3 direction, GStar::Vector3 position)
{
	array_ff templ = IDENTICAL_MATRIX;
	array_ff tempr = IDENTICAL_MATRIX;
	templ[0][0] = right.x();
	templ[0][1] = right.y();
	templ[0][2] = right.z();
	templ[1][0] = up.x();
	templ[1][1] = up.y();
	templ[1][2] = up.z();
	templ[2][0] = direction.x();
	templ[2][1] = direction.y();
	templ[2][2] = direction.z();
	tempr[0][3] = -position.x();
	tempr[1][3] = -position.y();
	tempr[2][3] = -position.z();
	GStar::Matrix4 tempmatrxl = GStar::Matrix4(templ);
	GStar::Matrix4 tempmatrxr = GStar::Matrix4(tempr);
	tempmatrxl = tempmatrxl * tempmatrxr;
	return tempmatrxl;
}


