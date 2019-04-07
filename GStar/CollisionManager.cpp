#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "PhysicComponent.h"
#include "Vector3.h"
#include <iterator>
#include "GSTime.h"
GStar::CollisionManager* GStar::CollisionManager::instance = nullptr;
GStar::CollisionComponent * GStar::CollisionManager::AddCollision(PhysicComponent * my_physic, const Vector3 & offset)
{
	CollisionComponent* temp = new CollisionComponent(my_physic, offset);
	my_physic->UseCollision();
	instance->CollisionComponents.push_back(temp);
	return temp;
}
void GStar::CollisionManager::Update()
{
	float smallest_close = 100.0f;
	GStar::Vector3 normal;
	CollisionComponent* A;
	CollisionComponent* B;
	for (std::vector<CollisionComponent*>::iterator it = CollisionComponents.begin(); it != CollisionComponents.end(); it++) {
		for (std::vector<CollisionComponent*>::iterator is = ++it; is != CollisionComponents.end(); is++) {
			float temp_time;
			GStar::Vector3 temp_normal;
			Collided(**it, **is, temp_normal, temp_normal, GSTime::Instance().GetdeltaTime(), temp_time);
			if (temp_time < smallest_close) {
				smallest_close = temp_time;
				normal = temp_normal;
				A = *it;
				B = *is;
			}
		}
	}
}
