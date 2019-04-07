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
	CollisionManager::Instance()->CollisionComponents.push_back(temp);
	return temp;
}
void GStar::CollisionManager::Update()
{
	float smallest_close = 100.0f;
	GStar::Vector3 normal(0.0f,0.0f,0.0f);
	CollisionComponent* A = nullptr;
	CollisionComponent* B = nullptr;
	float lefttime = GSTime::Instance().GetdeltaTime();
	bool collisionflag = false;
	do {
		smallest_close = 100.0f;
		collisionflag = false;
		float temp_time = 200.0f;
		GStar::Vector3 temp_normal;
		for (std::vector<CollisionComponent*>::iterator it = CollisionComponents.begin(); it != CollisionComponents.end(); it++) {
			for (std::vector<CollisionComponent*>::iterator is = it + 1; is != CollisionComponents.end(); is++) {
				float temp_time = 200.0f;
				GStar::Vector3 temp_normal;
				Collided(**it, **is, temp_normal, temp_normal, lefttime, temp_time);
				if (temp_time < smallest_close) {
					smallest_close = temp_time;
					normal = temp_normal;
					A = *it;
					B = *is;
					collisionflag = true;
				}
			}
		}
		if (collisionflag) {
			lefttime -= smallest_close;
			UpdatePhysic(smallest_close);
			ApplyCollisionResults(A, B, normal);
		}
	} while (collisionflag);
	UpdatePhysic(lefttime);
}

void GStar::CollisionManager::UpdatePhysic(float deltatime)
{
	for (std::vector<CollisionComponent*>::iterator it = CollisionComponents.begin(); it != CollisionComponents.end(); it++) {
		(*it)->getPhysic()->Update(deltatime);
	}
}
// this is only correct if A and B are of the same weight
void GStar::CollisionManager::ApplyCollisionResults(CollisionComponent * A, CollisionComponent * B, const GStar::Vector3 & NormalForA)
{
	GStar::Vector3 speed_A = A->getPhysic()->GetSpeed();
	GStar::Vector3 speed_B = B->getPhysic()->GetSpeed();
	GStar::Vector3 speed_BtoA = speed_B - speed_A;
	speed_BtoA *= .5f;
	speed_BtoA = speed_BtoA.Dot(NormalForA)*NormalForA;
	A->getPhysic()->SetSpeed(speed_A + speed_BtoA);
	B->getPhysic()->SetSpeed(speed_B - speed_BtoA);

}
