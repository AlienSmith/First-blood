#pragma once
#include"InterfaceComponent.h"
#include"TransformComponent.h"
class SimpleRotation : public GStar::InterfaceComponent {
public:
	SimpleRotation(GStar::TransformComponent* transform) :InterfaceComponent(),my_transform(transform) {}
	virtual void Initialize() override {}
	virtual void Update(float deltatime) override {
		//my_transform->Rotate(GStar::Vector3(1.0f, 0.0f, 0.0f));
		deltatime;
		my_transform->Translate(GStar::Vector3(0.0f, 0.0f, -1.0f*deltatime),GStar::Base::SELF);
	}
	virtual void Terminate() override {}
	~SimpleRotation() {}
	GStar::TransformComponent* my_transform;
	float a;
};