#pragma once
#include"Component.h"
namespace GStar {
	class TransformComponent;
	//This class is used to replace the old camera system
	//
	class CameraComponent:public Component {
	public:
		const static char TypeWord() {
			return CAMERA_WORD;
		}
		bool Initialize();
		bool Update();
		bool Terminate;
		CameraComponent(TransformComponent* transform ) 
			:Component(CAMERA_WORD)
			,my_transform(transform) {}

	private:
		TransformComponent* my_transform;
	};
}