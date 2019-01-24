#pragma once
#include"InterfaceComponent.h"
#include"UpdateObject.h"
#include"Time.h"
class SimpleRotationCopy : public GStar::InterfaceComponent {
public:
	virtual void Initialize() override {}
	virtual void Update() override {
		UpdateObject::OUT_Instance->GetTransformComponent()->Rotate(GStar::Vector3(GStar::Time::Instance().GetTotalTime() * 100, 0.0f, 0.0f));
	}
	virtual void Terminate() override {}
};