#pragma once
#include "Vector3.h"
#include <utility>
#include <vector>
namespace GStar {
	class CollisionComponent;
	void CollisionPoolCheck();
	std::pair<CollisionComponent*,CollisionComponent*> FindCollision(float i_dt,std::vector<CollisionComponent*>* collisionobjects);
	Vector3 GenerateRandomVector(const Vector3& min, const Vector3& max);
	float RandomInRange(float min, float max);
}