#pragma once
#include"Component.h"
namespace GStar {
	class TransformComponent;
	//This class is used to replace the old camera system
	//
	class CameraComponent {
	public:
		CameraComponent(TransformComponent* transform ) :my_transform(transform) {}
	private:
		TransformComponent* my_transform;
	};
}