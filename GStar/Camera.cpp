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
	up = Target;
}

void GStar::Camera::Update()
{
	view = Lookat(up, cameraTarget,cameraPos);
}

GStar::Camera::Camera(GStar::Vector3 camPos, GStar::Vector3 camTarget):cameraPos(camPos),cameraTarget(camTarget)
{
	Update();
}

GStar::Camera::Camera()
{
	Update();
}

GStar::Matrix4 GStar::Camera::Lookat( GStar::Vector3 worldup, GStar::Vector3 target, GStar::Vector3 position)
{
	GStar::Vector3 reverseDirection =  position-target;
	reverseDirection.Normalize();
	worldup.Normalize();
	GStar::Vector3 right = GStar::Vector3::Cross(worldup, reverseDirection);
	GStar::Vector3 up = GStar::Vector3::Cross(reverseDirection, right);
	array_ff templ = IDENTICAL_MATRIX;
	templ[0][0] = right.x();
	templ[0][1] = right.y();
	templ[0][2] = right.z();
	templ[1][0] = up.x();
	templ[1][1] = up.y();
	templ[1][2] = up.z();
	templ[2][0] = reverseDirection.x();
	templ[2][1] = reverseDirection.y();
	templ[2][2] = reverseDirection.z();

	templ[3][0] = -right.Dot(position);
	templ[3][1] = -up.Dot(position);
	templ[3][2] = -reverseDirection.Dot(position);
	GStar::Matrix4 tempmatrxl = GStar::Matrix4(templ);
	return tempmatrxl;
}


