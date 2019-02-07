#pragma once
#include "InterfaceComponent.h"
#include "PhysicComponent.h"
namespace GStar {
	class PhysicComponent;
class SimpleForce:public InterfaceComponent{
	public:
		SimpleForce(GStar::PhysicComponent* transform,float force) :InterfaceComponent(transform->GetTransformComponent()), my_component(transform),_force(force) {}
		virtual void Initialize() override {}
		virtual void Update() override;
		virtual void Terminate() override {}
		~SimpleForce() {}
		GStar::PhysicComponent* my_component;
	private:
		float _force;
	};
}