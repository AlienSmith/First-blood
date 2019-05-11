#pragma once
#include"InterfaceComponent.h"
#include"KeyInputEvent.h"
#include"MouseInputEvent.h"
#include"EventManager.h"
#include"PhysicComponent.h"
#include "CollisionComponent.h"
namespace GStar {
	class PongController : public InterfaceComponent {
	public:
		PongController(GStar::PhysicComponent* component, float speed, int key1, int key2);
		virtual void Initialize() override;
		virtual void Update() override;
		void OnKeyControl(GStar::Event* input);
		virtual void Terminate() override{}
		virtual void OnCollision(CollisionComponent* other_collider, const Vector3& Collision_Point) override;
		~PongController(){}
	private:
		GStar::Vector3 delta;
		GStar::PhysicComponent* my_component;
		float my_speed;
		int positive_key;
		int negative_key;
	};
}