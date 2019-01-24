#pragma once
#include "InterfaceComponent.h"
namespace GStar {
	class PhysicComponent;
class SimpleForce:public InterfaceComponent{
	public:
		SimpleForce(GStar::PhysicComponent* transform,float force) :InterfaceComponent(), my_transform(transform),_force(force) {}
		virtual void Initialize() override {}
		virtual void Update() override;
		virtual void Terminate() override {}
		~SimpleForce() {}
		GStar::PhysicComponent* my_transform;
	private:
		float _force;
	};
}