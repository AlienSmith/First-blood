#pragma once
#include "InterfaceComponent.h"
class SimpleRotationCopy : public GStar::InterfaceComponent {
public:
	virtual void Initialize() override {}
	virtual void Update() override;
	virtual void Terminate() override {}
};