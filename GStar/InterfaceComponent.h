#pragma once
#include "TransformComponent.h"
#include "SmartPointer.h"
namespace GStar {
	class InterfaceComponent{
	public:
		virtual void Initialize() = 0;
		//This will work on the updateobject instead of the Object.
		virtual void Update() = 0;
		virtual void Terminate() = 0;
		InterfaceComponent(const SmartPointer<TransformComponent>& object):my_transform(object){}
		virtual ~InterfaceComponent() {}
	protected:
		SmartPointer<TransformComponent> my_transform;
	};
}