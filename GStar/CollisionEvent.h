#pragma once
#include"Event.h"
#include"CollisionComponent.h"
namespace GStar {
	class CollisionEvent: public Event{
	public:
		Vector3 Point;
		CollisionComponent* ColliderA;
		CollisionComponent* ColliderB;
		CollisionEvent(CollisionComponent* Collider1, CollisionComponent* collider2, const Vector3& CollisionPoint):
			Point(CollisionPoint),
			ColliderA(Collider1),
			ColliderB(collider2){}
	};
}