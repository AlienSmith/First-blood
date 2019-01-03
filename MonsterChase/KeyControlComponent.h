#pragma once
#include"InterfaceComponent.h"
#include"GLFW/glfw3.h"
#include"KeyInputEvent.h"
#include"MouseInputEvent.h"
#include"EventManager.h"
#include"TransformComponent.h"
//TODO add delatetime to each update function
class KeyControlCompoenent : public GStar::InterfaceComponent {
public:
	//the hock up the call back event
	KeyControlCompoenent(GStar::TransformComponent* transform, float movespeed) :InterfaceComponent(),delta(GStar::Vector3(0,0,0)), my_transform(transform), speed(movespeed) { Initialize(); }
	virtual void Initialize() override {
		//This is how to use a Class specified function
		GStar::EventManager::Instance()->GetEventUnite("KeyBoardInput").Bind<KeyControlCompoenent,&KeyControlCompoenent::OnKeyControl>(this);
		GStar::EventManager::Instance()->GetEventUnite("MouseInput").Bind<KeyControlCompoenent, &KeyControlCompoenent::OnMouseControl>(this);
	}
	virtual void Update(float deltatime) override {
		my_transform->Translate(delta*deltatime, GStar::Base::SELF);
	}
	void OnMouseControl(GStar::Event* input) {
		GStar::MouseInputEvent* event = static_cast<GStar::MouseInputEvent*>(input);
		GStar::Vector3 rotation = GStar::Vector3();
		rotation[1] = -event->xpos;
		rotation[0] = -event->ypos;
		rotation[2] = 0;
		my_transform->Rotate(rotation);
	}
	void OnKeyControl(GStar::Event* input) {
		GStar::KeyInputEvent* event = static_cast<GStar::KeyInputEvent*>(input);
		if (event->SingleKey == GLFW_KEY_T) {
			if (event->action == GLFW_RELEASE) {
				delta[2] = 0;
			}
			else {
				delta[2] = -speed;
			}
		}else if (event->SingleKey == GLFW_KEY_F) {
			if (event->action == GLFW_RELEASE) {
				delta[0] = 0;
			}
			else
			{
				delta[0] = -speed;
			}
		}else if (event->SingleKey == GLFW_KEY_G) {
			if (event->action == GLFW_RELEASE) {
				delta[2] = 0;
			}
			else {
				delta[2] = speed;
			}
		}else if (event->SingleKey == GLFW_KEY_H ) {
			if (event->action == GLFW_RELEASE) {
				delta[0] = 0;
			}
			else
			{
				delta[0] = speed;
			}
		}
	}
	virtual void Terminate() override {}
	~KeyControlCompoenent() {}
private:
	GStar::Vector3 delta;
	GStar::TransformComponent* my_transform;
	const float speed;
};