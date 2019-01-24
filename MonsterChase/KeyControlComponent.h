#pragma once
#include"InterfaceComponent.h"
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
	virtual void Update() override;
	void OnMouseControl(GStar::Event* input) {
		GStar::MouseInputEvent* event = static_cast<GStar::MouseInputEvent*>(input);
		GStar::Vector3 rotation = GStar::Vector3();
		rotation[1] = (float)-event->xpos;
		rotation[0] = (float)-event->ypos;
		rotation[2] = 0;
		my_transform->Rotate(rotation);
	}
	void OnKeyControl(GStar::Event* input);
	virtual void Terminate() override {}
	~KeyControlCompoenent() {}
private:
	GStar::Vector3 delta;
	GStar::TransformComponent* my_transform;
	const float speed;
};