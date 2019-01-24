#pragma once
#include"InterfaceComponent.h"
namespace GStar {
	class TransformComponent;
}
class SimpleRotation : public GStar::InterfaceComponent {
public:
	SimpleRotation(GStar::TransformComponent* transform) :InterfaceComponent(),my_transform(transform) {}
	virtual void Initialize() override {}
	virtual void Update() override;
	virtual void Terminate() override {}
	~SimpleRotation() {}
	GStar::TransformComponent* my_transform;
	float a;
};