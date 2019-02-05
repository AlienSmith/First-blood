#pragma once
#include "TransformComponent.h"
namespace GStar {
	class InterfaceComponent{
	public:
		virtual void Initialize() = 0;
		//This will work on the updateobject instead of the Object.
		virtual void Update() = 0;
		virtual void Terminate() = 0;
		InterfaceComponent(TransformComponent* object):my_transform(object){}
		virtual ~InterfaceComponent() {}
	protected:
		TransformComponent* my_transform;
	};
}