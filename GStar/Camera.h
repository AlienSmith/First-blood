#pragma once
#include "Vector3.h"
#include "Matrix4.h"
class GLFWwindow;
namespace GStar {
	static const float CameraMoveSpeed = 25;
	class Camera {
	public:
		void Set_Target(GStar::Vector3 Target);
		void Set_Pos(GStar::Vector3 Target);
		void Update();
		void RotateUpdate();
		Camera(GStar::Vector3 cameraPos, GStar::Vector3 cameraTarget);
		Camera();
		static GStar::Matrix4 Lookat(const GStar::Vector3& worldup, const GStar::Vector3& reverseDirection, const GStar::Vector3& position);
		static GStar::Matrix4 Lookat(const GStar::Vector3& worldup, const GStar::Vector3& reverseDirection, const GStar::Vector3& position, GStar::Vector3& up, GStar::Vector3& right);
		GStar::Matrix4 view;
		void processInput(GLFWwindow * window, float deltatime);
		bool NeedUpdate = false;
		inline float  getpitch() const { return pitch; };
		inline float getyaw() const { return yaw; };
		inline void setpitch(float pit) { pitch = pit; if (pit > 89.0f)pitch = 89.0f; if (pit < -89.0f)pitch = -89.0f; };
		inline void setyaw(float yaw) { yaw = yaw; };
	private:
		GStar::Vector3 cameraTarget = GStar::Vector3(0.0f, 0.0f, 0.0f);
		GStar::Vector3 cameraPos = GStar::Vector3(0.0f, 0.0f, 10.0f);
		GStar::Vector3 CameraUp = GStar::Vector3(0.0f, 0.0f, 0.0f);
		GStar::Vector3 CameraFront = GStar::Vector3(0.0f, 0.0f, 0.0f);
		GStar::Vector3 CameraRight = GStar::Vector3(0.0f, 0.0f, 0.0f);
		float pitch = 0;
		float yaw = 0;
	};
}