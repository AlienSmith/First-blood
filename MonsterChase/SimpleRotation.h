#pragma once
#include"InterfaceComponent.h"
namespace GStar {
	class TransformComponent;
}
class SimpleRotation : public GStar::InterfaceComponent {
public:
	SimpleRotation(GStar::TransformComponent* transform) :InterfaceComponent(transform) {}
	virtual void Initialize() override {}
	virtual void Update() override;
	virtual void Terminate() override {}
	~SimpleRotation() {}
	float a;
};