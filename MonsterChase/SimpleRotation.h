#pragma once
#include"InterfaceComponent.h"
#include"UpdateObject.h"
class SimpleRotation : public GStar::InterfaceComponent {
public:
	SimpleRotation() :InterfaceComponent() {}
	virtual void Initialize() override {}
	virtual void Update() override {
		UpdateObject::OUT_Instance->GetTransformComponent()->SetRotation(GStar::Vector3(Scene::Create()->TotalTime() * 100, 0.0f, 0.0f));
	}
	virtual void Terminate() override {}
	~SimpleRotation() {}
	float a;
};