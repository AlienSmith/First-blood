#pragma once
#include"Vector3.h"
namespace GStar {
	class TransformComponent;
	//cuboid collider
	class CollisionComponent {
	public:
		explicit CollisionComponent(TransformComponent* trans);
		explicit CollisionComponent(TransformComponent* trans, const Vector3& offset);
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent& operator = (const CollisionComponent& other) = delete;
	private:
		TransformComponent* my_transform;
		Vector3 offsets;
	};
}