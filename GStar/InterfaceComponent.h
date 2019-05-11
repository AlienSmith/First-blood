#pragma once
#include "TransformComponent.h"
namespace GStar {
	class CollisionComponent;
	class Vector3;
	class InterfaceComponent{
	public:
		virtual void Initialize() = 0;
		//This will work on the updateobject instead of the Object.
		virtual void Update() = 0;
		virtual void Terminate() = 0;
		virtual void OnCollision(CollisionComponent* other_collider, const Vector3& Collision_Point){}
		InterfaceComponent(TransformComponent* object):my_transform(object){}
		virtual ~InterfaceComponent() {}
		TransformComponent* GetComponent() {
			return my_transform;
		}
	protected:
		TransformComponent* my_transform;
	};
}