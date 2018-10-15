#pragma once
#include "Vector3.h"
#include "Matrix4.h"
namespace GStar {
	class Camera {
	public:
		void Set_Target(GStar::Vector3 Target);
		void Set_Pos(GStar::Vector3 Target);
		void Set_Up(GStar::Vector3 Target);
		void Update();
		Camera(GStar::Vector3 cameraPos, GStar::Vector3 cameraTarget);
		Camera();
		static GStar::Matrix4 Lookat(GStar::Vector3 right, GStar::Vector3 up, GStar::Vector3 direction, GStar::Vector3 position);
		GStar::Matrix4 view;
	private:
		GStar::Vector3 cameraTarget = GStar::Vector3(0.0f, 0.0f, 0.0f);
		GStar::Vector3 cameraPos = GStar::Vector3(0.0f, 0.0f, 3.0f);
		GStar::Vector3 cameraDirection = GStar::Vector3(0.0f, 0.0f, 0.0f);
		GStar::Vector3 up = GStar::Vector3(0.0f, 1.0f, 0.0f);
		GStar::Vector3 cameraRight = GStar::Vector3(0.0f, 0.0f, 0.0f);
		GStar::Vector3 cameraUp = GStar::Vector3(0.0f, 0.0f, 0.0f);
	};
}