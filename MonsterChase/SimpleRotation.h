#pragma once
#include"InterfaceComponent.h"
#include"TransformComponent.h"
#include"Scene.h"
class SimpleRotation : public GStar::InterfaceComponent {
public:
	SimpleRotation(GStar::TransformComponent* transform) :InterfaceComponent(),my_transform(transform) {}
	virtual void Initialize() override {}
	virtual void Update() override {
		my_transform->Rotate(GStar::Vector3(10.0f, 0.0f, 0.0f));
		//my_transform->Translate(GStar::Vector3(0.0f, 0.0f, -0.01f),GStar::Base::SELF);
	}
	virtual void Terminate() override {}
	~SimpleRotation() {}
	GStar::TransformComponent* my_transform;
	float a;
};