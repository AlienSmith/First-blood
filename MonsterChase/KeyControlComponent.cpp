#include "KeyControlComponent.h"
#include"GSTime.h"
void KeyControlCompoenent::Update()
{
	my_transform->Translate(delta * (float)GStar::GSTime::Instance().GetdeltaTime(), GStar::Base::SELF);
}

void KeyControlCompoenent::OnKeyControl(GStar::Event * input)
{
	GStar::KeyInputEvent* event = static_cast<GStar::KeyInputEvent*>(input);
	if (event->SingleKey == GLFW_KEY_T) {
		if (event->action == GLFW_RELEASE) {
			delta[2] = 0;
		}
		else {
			delta[2] = -speed;
		}
	}
	else if (event->SingleKey == GLFW_KEY_F) {
		if (event->action == GLFW_RELEASE) {
			delta[0] = 0;
		}
		else
		{
			delta[0] = -speed;
		}
	}
	else if (event->SingleKey == GLFW_KEY_G) {
		if (event->action == GLFW_RELEASE) {
			delta[2] = 0;
		}
		else {
			delta[2] = speed;
		}
	}
	else if (event->SingleKey == GLFW_KEY_H) {
		if (event->action == GLFW_RELEASE) {
			delta[0] = 0;
		}
		else
		{
			delta[0] = speed;
		}
	}
}
