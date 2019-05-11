#pragma once
#include"InterfaceComponent.h"
#include"KeyInputEvent.h"
#include"MouseInputEvent.h"
#include"EventManager.h"
#include"PhysicComponent.h"
namespace GStar {
	class PongBallController:public InterfaceComponent {
	public:
		PongBallController(GStar::PhysicComponent* component, float max_speed, float enhance_Scale);
		virtual void Initialize() override;
		virtual void Update() override{}
		virtual void OnCollision(CollisionComponent* other_collider, const Vector3& Collision_Point) override;
		virtual void Terminate() override {}
		~PongBallController(){}
	private:
		float maxspeed;
		float enhancement;
		GStar::PhysicComponent* my_component;
	};
}