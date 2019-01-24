#pragma once
#include "InterfaceComponent.h"
namespace GStar {
	class PhysicComponent;
class SimpleForce:public InterfaceComponent{
	public:
		SimpleForce(GStar::PhysicComponent* transform) :InterfaceComponent(), my_transform(transform) {}
		virtual void Initialize() override {}
		virtual void Update() override;
		virtual void Terminate() override {}
		~SimpleForce() {}
		GStar::PhysicComponent* my_transform;
		float a;
	};
}