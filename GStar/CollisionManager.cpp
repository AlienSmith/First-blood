#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "PhysicComponent.h"
#include "Vector3.h"
#include <iterator>
#include "GSTime.h"
#include <utility>
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
	int iterations = 0;
	float smallest_close = 100.0f;
	GStar::Vector3 normal(0.0f,0.0f,0.0f);
	CollisionComponent* A = nullptr;
	CollisionComponent* B = nullptr;
	float lefttime = GSTime::Instance().GetdeltaTime();
	bool collisionflag = false;
	do {
		iterations++;
		if (iterations > 5) {
			DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Waring, "Collision detection overtimes");
			break;
		}
		//Initialize Collision Info
		for (std::vector<CollisionComponent*>::iterator it = CollisionComponents.begin(); it != CollisionComponents.end(); it++) {
			(*it)->Update();
		}
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
void GStar::CollisionManager::GetCollisionPoint(CollisionComponent * A, CollisionComponent * B, const Vector3& normal, Vector3 & o_RA, Vector3 & o_RB, Vector3 & o_Point, float deltatime) const
{
	Vector3 Center_A = A->my_info.Tr + A->getPhysic()->GetSpeed()*deltatime;
	Vector3 Center_B = B->my_info.Tr + B->getPhysic()->GetSpeed()*deltatime;
	Vector3 temp_A;
	std::vector<Vector3> Vector3_A;
	std::vector<Vector3> Vector3_B;
	Vector3 temp_B;
	int count_A = ContactInfo(A,normal,temp_A,Vector3_A);
	//contact is a point for A, Hence no need for futher computation
	if (count_A == 3) {
		o_RA = temp_A;
		o_Point = Center_A + temp_A;
		o_RB = o_Point - Center_B;
		return;
	}
	int count_B = ContactInfo(B, normal, temp_B, Vector3_B);
	if (count_B == 3) {
		o_RB = temp_B;
		o_Point = temp_B + Center_B;
		o_RA = o_Point - Center_A;
		return;
	}
	// line line
	if (count_A == 2 && count_B == 2) {
		//find if two line is parrellel
		if (Vector3::parallel(Vector3_A[0], Vector3_B[0])) {
			o_Point = .5f*(Center_A + Center_B + temp_A + temp_B);
			o_RB = o_Point - Center_B;
			o_RA = o_Point - Center_A;
			return;
		}
		//find if the middle point is on the other line;
		Vector3 middle_A = Center_A + temp_A;
		Vector3 middle_B = Center_B + temp_B;
		Vector3 Middle_A_to_B = middle_A - middle_B;
		if (Middle_A_to_B == Vector3(.0f, .0f, .0f) || Vector3::parallel(Middle_A_to_B,Vector3_B[0])) {
			o_Point = middle_A;
			o_RA = temp_A;
			o_RB = o_Point - Center_B;
			return;
		}
		else if (Vector3::parallel(Middle_A_to_B, Vector3_A[0])) {
			o_Point = middle_B;
			o_RA = o_Point - Center_A;
			o_RB = temp_B;
			return;
		}
		//Find the intersection point
		
	}
	// Plane Plane
	else if (count_A == 1 && count_B == 1) {
	
	}
	else {

	}
	// Line Plane 
}
int GStar::CollisionManager::ContactInfo(CollisionComponent* A, const Vector3& normal,Vector3 & o_offset, std::vector<Vector3>& o_Vector) const
{
	Vector3 temp_A = Vector3(.0f, .0f, .0f);
	int count_A = 0;
	for (int i = 0; i < 3; i++) {
		Vector3 temp = A->my_info.Axies[0];
		float flag = normal.Dot(temp);
		if (Equals(flag, 0.0f)) {
			o_Vector.push_back(temp);
			continue;
		}
		temp_A += (flag > 0 ? temp : -1.0f*temp);
		count_A++;
	}
	o_offset = temp_A;
	return count_A;
}
// this is only correct if A and B are of the same weight
void GStar::CollisionManager::ApplyCollisionResults(CollisionComponent * A, CollisionComponent * B, const GStar::Vector3 & NormalForA)
{
	float speed_A = (A->getPhysic()->GetSpeed()).Dot(NormalForA);
	float speed_B = (B->getPhysic()->GetSpeed()).Dot(NormalForA);
	float mass_A = A->getPhysic()->getMass();
	float mass_B = B->getPhysic()->getMass();
	float mass_AmB = mass_A - mass_B;
	float mass_ApB = mass_A + mass_B;
	float speed_delta_A = (mass_AmB / mass_ApB - 1.0f)*speed_A + (2.0f*mass_B / mass_ApB)*speed_B;
	float speed_delta_B = (mass_AmB / mass_ApB - 1.0f)*speed_B + (2.0f*mass_A / mass_ApB)*speed_A;
	A->getPhysic()->SetSpeed(A->getPhysic()->GetSpeed()+(NormalForA*speed_delta_A));
	B->getPhysic()->SetSpeed(B->getPhysic()->GetSpeed() + (NormalForA*speed_delta_B));
	A->getPhysic()->SetForce(GStar::Vector3(0.0f, 0.0f, 0.0f));
	B->getPhysic()->SetForce(GStar::Vector3(0.0f, 0.0f, 0.0f));
#if defined(_DEBUG)
	int idA = A->getPhysic()->GetTransformComponent()->GetName();
	GStar::Vector3 SpeedA = A->getPhysic()->GetSpeed();
	int idB = B->getPhysic()->GetTransformComponent()->GetName();
	GStar::Vector3 SpeedB = B->getPhysic()->GetSpeed();
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "After Collision Object %i with speed %f,%f,%f", idA, SpeedA[0], SpeedA[1], SpeedA[2]);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "After Collision Object %i with speed %f,%f,%f", idB, SpeedB[0], SpeedB[1], SpeedB[2]);
#endif
}
