#pragma once
#pragma once
#include"InterfaceComponent.h"
#include"KeyInputEvent.h"
#include"MouseInputEvent.h"
#include"EventManager.h"
#include"PhysicComponent.h"
#include "CollisionComponent.h"
namespace GStar {
	class PongWall : public InterfaceComponent {
	public:
		PongWall(GStar::TransformComponent* component);
		virtual void Initialize() override {}
		virtual void Update() override {}
		virtual void Terminate() override {}
		virtual void OnCollision(CollisionComponent* other_collider, const Vector3& Collision_Point) override;
		~PongWall() {}
	private:
	};
}