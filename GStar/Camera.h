#pragma once
#include "Vector3.h"
#include "Matrix4.h"
class GLFWwindow;
namespace GStar {
	class Camera {
	public:
		void Set_Target(GStar::Vector3 Target);
		void Set_Pos(GStar::Vector3 Target);
		void Set_Up(GStar::Vector3 Target);
		void Update();
		Camera(GStar::Vector3 cameraPos, GStar::Vector3 cameraTarget);
		Camera();
		static GStar::Matrix4 Lookat( const GStar::Vector3& worldup, const GStar::Vector3& target, const GStar::Vector3& position);
		static GStar::Matrix4 Lookat(const GStar::Vector3& worldup, const GStar::Vector3& target, const GStar::Vector3& position, GStar::Vector3& front, GStar::Vector3& Up, GStar::Vector3& Right);
		GStar::Matrix4 view;
		void processInput(GLFWwindow * window, float deltatime);
	private:
		GStar::Vector3 cameraTarget = GStar::Vector3(0.0f, 0.0f, 0.0f);
		GStar::Vector3 cameraPos = GStar::Vector3(0.0f, 0.0f, 10.0f);
		GStar::Vector3 CameraUp = GStar::Vector3(0.0f, 0.0f, 0.0f);
		GStar::Vector3 CameraFront = GStar::Vector3(0.0f, 0.0f, 0.0f);
		GStar::Vector3 CameraRight = GStar::Vector3(0.0f, 0.0f, 0.0f);
	};
}