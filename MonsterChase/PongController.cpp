#include "PongController.h"

GStar::PongController::PongController(GStar::PhysicComponent * component, float speed, int key1, int key2):
	InterfaceComponent(component->GetTransformComponent()),
	delta(Vector3(0,0,0)),
	my_component(component),
	my_speed(speed),
	positive_key(key1),
	negative_key(key2)
{
	Initialize();
}

void GStar::PongController::Initialize()
{
	GStar::EventManager::Instance()->GetEventUnite("KeyBoardInput").Bind<PongController, &PongController::OnKeyControl>(this);
}

void GStar::PongController::Update()
{
	my_component->AddForce(delta);
}

void GStar::PongController::OnKeyControl(GStar::Event * input)
{
	GStar::KeyInputEvent* event = static_cast<GStar::KeyInputEvent*>(input);
	if (event->SingleKey == positive_key) {
		if (event->action == GLFW_RELEASE) {
			delta[1] = 0;
		}
		else {
			delta[1] =my_speed;
		}
	}
	if (event->SingleKey == negative_key) {
		if (event->action == GLFW_RELEASE) {
			delta[1] = 0;
		}
		else {
			delta[1] = -my_speed;
		}
	}
}
