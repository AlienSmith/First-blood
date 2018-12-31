#pragma once
#include"InterfaceComponent.h"
#include"GLFW/glfw3.h"
#include"KeyInputEvent.h"
#include"EventManager.h"
#include"TransformComponent.h"
//TODO add delatetime to each update function
class KeyControlCompoenent : public GStar::InterfaceComponent {
public:
	//the hock up the call back event
	KeyControlCompoenent(GStar::TransformComponent* transform, float movespeed) :InterfaceComponent(), my_transform(transform), speed(movespeed) { Initialize(); }
	virtual void Initialize() override {
		//This is how to use a Class specified function
		GStar::EventManager::Instance()->GetEventUnite("KeyBoardInput").Bind<KeyControlCompoenent,&KeyControlCompoenent::OnKeyControl>(this);
	}
	virtual void Update() override {}
	void OnKeyControl(GStar::Event* input) {
		GStar::KeyInputEvent* event = static_cast<GStar::KeyInputEvent*>(input);
		if (event->SingleKey == GLFW_KEY_T && event->action == GLFW_PRESS) {
			my_transform->Translate(GStar::Vector3(0.0f,0.0f,speed), GStar::Base::SELF);
		}else if (event->SingleKey == GLFW_KEY_F && event->action == GLFW_PRESS) {
			my_transform->Translate(GStar::Vector3(-speed, 0.0f, 0.0f), GStar::Base::SELF);
		}else if (event->SingleKey == GLFW_KEY_G && event->action == GLFW_PRESS) {
			my_transform->Translate(GStar::Vector3(0.0f, 0.0f, -speed), GStar::Base::SELF);
		}else if (event->SingleKey == GLFW_KEY_H && event->action == GLFW_PRESS) {
			my_transform->Translate(GStar::Vector3(speed, 0.0f, 0.0f), GStar::Base::SELF);
		}
	}
	virtual void Terminate() override {}
	~KeyControlCompoenent() {}
private:
	GStar::TransformComponent* my_transform;
	const float speed;
};