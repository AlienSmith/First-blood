#include "PhysicBasedController.h"

void GStar::PhysicBasedController::Update()
{
	my_component->AddForce( delta, my_transform->GetTransform() + 0.5f*my_transform->GetRightVector());
	for (int i = 0; i < 3; i++) {
		delta.getReference(i) = 0.0f;
	}
}

void GStar::PhysicBasedController::OnKeyControl(GStar::Event * input)
{
	GStar::KeyInputEvent* event = static_cast<GStar::KeyInputEvent*>(input);
	if (event->SingleKey == GLFW_KEY_T) {
		if (event->action == GLFW_RELEASE) {
			delta[1] = 0;
		}
		else {
			delta[1] = force;
		}
	}
	else if (event->SingleKey == GLFW_KEY_F) {
		if (event->action == GLFW_RELEASE) {
			delta[0] = 0;
		}
		else
		{
			delta[0] = -force;
		}
	}
	else if (event->SingleKey == GLFW_KEY_G) {
		if (event->action == GLFW_RELEASE) {
			delta[1] = 0;
		}
		else {
			delta[1] = -force;
		}
	}
	else if (event->SingleKey == GLFW_KEY_H) {
		if (event->action == GLFW_RELEASE) {
			delta[0] = 0;
		}
		else
		{
			delta[0] = force;
		}
	}
}
