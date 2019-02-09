#pragma once
#include"Component.h"
#include"SmartPointer.h"
namespace GStar {
	class TransformComponent;
	class CameraComponent {
	public:
		CameraComponent(const SmartPointer<TransformComponent>& transform ) :my_transform(transform) {}
	private:
		SmartPointer<TransformComponent> my_transform;
	};
}