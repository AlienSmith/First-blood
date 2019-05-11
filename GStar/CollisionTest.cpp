#include "CollisionTest.hpp"
#include <random>
#include"CollisionComponent.h"
#include"TransformComponent.h"
#include"PhysicComponent.h"
void GStar::CollisionPoolCheck()
{
	static std::vector<GStar::CollisionComponent*> collisionobjects;
	using namespace GStar;
	const static float AreaExtent = 10.0f;
	Vector3 PositionMin(-AreaExtent, -AreaExtent, -AreaExtent);
	Vector3 PositionMax(AreaExtent, AreaExtent, AreaExtent);

	Vector3 VelocityMin(-1.0f, -1.0f, -1.0f);
	Vector3 VelocityMax(1.0f, 1.0f, 1.0f);
	const static size_t numOjbect = 100;
	for (size_t i = 0; i < numOjbect; i++) {
		TransformComponent* temp_trans = new TransformComponent("name");
		temp_trans->SetTransform(GenerateRandomVector(PositionMin, PositionMax), Base::WORLD);
		switch (rand() & 0x03)
		{
		case 01:
			temp_trans->Rotate(RandomInRange(0.0f, 90.0f), RandomInRange(0.0f, 90.0f), RandomInRange(0.0f, 90.0f));
			break;
		default:
			break;
		}
		temp_trans->SetScale(1, 1, 1);
		PhysicComponent* temp_Physic = new PhysicComponent(temp_trans);
		temp_Physic->SetSpeed(GenerateRandomVector(VelocityMin, VelocityMax));
		CollisionComponent* temp_collis = new CollisionComponent(temp_Physic);
		collisionobjects.push_back(temp_collis);
	}
	while(true){
		std::pair<GStar::CollisionComponent*, GStar::CollisionComponent*> CollisionPair = FindCollision(RandomInRange(.1f, 1.0f),(&collisionobjects));
	}
}

std::pair<GStar::CollisionComponent*, GStar::CollisionComponent*> GStar::FindCollision(float i_dt, std::vector<CollisionComponent*>* collisionobjects)
{
	for (std::vector<CollisionComponent*>::iterator it = collisionobjects->begin(); it != collisionobjects->end(); it++) {
		for (std::vector<CollisionComponent*>::iterator is = it + 1; is != collisionobjects->end(); is++) {
			float temp_time = 200.0f;
			GStar::Vector3 temp_normal;
			if (Collided(**it, **is, temp_normal, temp_normal, i_dt, temp_time)) {
				return { (*it),(*is) };
			}
		}
	}
	return {nullptr,nullptr};
 } 

GStar::Vector3 GStar::GenerateRandomVector(const Vector3 & min, const Vector3 & max)
{
	return Vector3(0, 0, 0);
}

float GStar::RandomInRange(float min, float max)
{
	return min + (max-min)*((double)rand() / (RAND_MAX));
}

