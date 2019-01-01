#pragma once
#include"InterfaceComponent.h"
#include"UpdateObject.h"
class SimpleRotationCopy : public GStar::InterfaceComponent {
public:
	virtual void Initialize() override {}
	virtual void Update(float deltatime) override {
		UpdateObject::OUT_Instance->GetTransformComponent()->SetRotation(GStar::Vector3(Scene::Create()->TotalTime() * 100, 0.0f, 0.0f));
	}
	virtual void Terminate() override {}
};