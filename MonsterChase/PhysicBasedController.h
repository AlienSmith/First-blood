#pragma once
#include"InterfaceComponent.h"
#include"KeyInputEvent.h"
#include"MouseInputEvent.h"
#include"EventManager.h"
#include"PhysicComponent.h"
namespace GStar {
	class PhysicBasedController : public InterfaceComponent
	{
	public:
		PhysicBasedController(GStar::PhysicComponent* component, float forcescale):
			InterfaceComponent(component->GetTransformComponent()),
			delta(Vector3(0.0f,0.0f,0.0f)),
			my_component(component),
			force(forcescale) {
			Initialize();
		}
		virtual void Initialize() override {
			GStar::EventManager::Instance()->GetEventUnite("KeyBoardInput").Bind<PhysicBasedController, &PhysicBasedController::OnKeyControl>(this);
			GStar::EventManager::Instance()->GetEventUnite("MouseInput").Bind<PhysicBasedController, &PhysicBasedController::OnMouseControl>(this);
		}
		virtual void Update() override;
		void OnMouseControl(GStar::Event* input) {
			GStar::MouseInputEvent* event = static_cast<GStar::MouseInputEvent*>(input);
			GStar::Vector3 rotation = GStar::Vector3();
			//rotation[1] = (float)-event->xpos;
			//rotation[0] = (float)-event->ypos;
			//rotation[2] = 0;

			rotation[1] = 0;
			rotation[0] = 0;
			rotation[2] = (float)-event->ypos;
			my_component->GetTransformComponent()->Rotate(rotation);
		}
		void OnKeyControl(GStar::Event* input);
		virtual void Terminate() override {}
		~PhysicBasedController() {}
	private:
		GStar::Vector3 delta;
		GStar::PhysicComponent* my_component;
		const float force;
	};
}