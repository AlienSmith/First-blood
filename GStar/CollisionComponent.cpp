#include "CollisionComponent.h"
#include "PhysicComponent.h"
#include <math.h>
#include "ConsolePrint.h"
const float GStar::CollisionComponent::margin = -0.0001f;
GStar::CollisionComponent::CollisionComponent(PhysicComponent * trans) :my_physic(trans) {}

GStar::CollisionComponent::CollisionComponent(PhysicComponent * trans, const Vector3 & offset) : my_physic(trans), offsets(offset) {}

GStar::PhysicComponent * GStar::CollisionComponent::getPhysic()
{
	return my_physic;
}

const GStar::PhysicComponent * const GStar::CollisionComponent::getPhysic() const {

	return my_physic;
}

GStar::Vector3 GStar::CollisionComponent::getOffset() const
{
	return offsets;
}

void GStar::CollisionComponent::GetCollisionInfo()
{
	my_info = { my_physic->GetTransformComponent()->X(),
			my_physic->GetTransformComponent()->Y(),
			my_physic->GetTransformComponent()->Z(),
			my_physic->GetTransformComponent()->GetTransform(),
			offsets*my_physic->GetTransformComponent()->GetScale() };
}

void GStar::CollisionComponent::Update()
{
	GetCollisionInfo();
}


bool GStar::Collided(const CollisionComponent& ColliderA, const CollisionComponent& ColliderB, Vector3& o_point, Vector3& o_normal, float deltatime, float& collisiontime)
{
	if (ColliderA.getPhysic()->GetSpeed() == ColliderB.getPhysic()->GetSpeed()) {
		return false;
	}
	//X Y Z Tr
	//Assume the speed does not change during this frame
	const GStar::CollisionInfo& InfoA = ColliderA.my_info;
	const GStar::CollisionInfo& InfoB = ColliderB.my_info;

	GStar::Vector3 SpeedAtoB = ColliderA.getPhysic()->GetSpeed() - ColliderB.getPhysic()->GetSpeed();
 	GStar::Vector3 axies(0.0f, 0.0f, 0.0f);
	float smallest_open = deltatime + 1.0f;
	float largest_close = -1.0*smallest_open;
	/*if (!(OverLapAtoB(&InfoA, &InfoB, SpeedAtoB, deltatime, largest_close, smallest_open, axies) &&
		OverLapAtoB(&InfoB, &InfoA, -1.0f*SpeedAtoB, deltatime, largest_close, smallest_open, axies) &&
		OverLapAB(&InfoA, &InfoB, SpeedAtoB, deltatime, largest_close, smallest_open, axies))) {
		return false;
	}*/
	if (OverLapAtoB(&InfoA, &InfoB, SpeedAtoB, deltatime, largest_close, smallest_open, axies)) {
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log , "A to B Close");
	}
	else {
		return false;
	}
	if(OverLapAtoB(&InfoB, &InfoA, -1.0f*SpeedAtoB, deltatime, largest_close, smallest_open, axies)){
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "B to A Close");
	}
	else {
		return false;
	}
	if (OverLapAB(&InfoA, &InfoB, SpeedAtoB, deltatime, largest_close, smallest_open, axies)) {
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Other Close");
	}
	else {
		return false;
	}
	if (largest_close > smallest_open) {
		return false;
	}
	collisiontime = largest_close;
	float temp = SpeedAtoB.SDot(axies);
	o_normal = -1.0f*signum(temp)*axies;

	float speed_on_axies = SpeedAtoB.SDot(o_normal);
	if (Equals(speed_on_axies,0.0f)) {
		return false;
	}
#ifdef _DEBUG
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Collided");
	int idA = ColliderA.getPhysic()->GetTransformComponent()->GetName();
	GStar::Vector3 SpeedA = ColliderA.getPhysic()->GetSpeed();
	int idB = ColliderB.getPhysic()->GetTransformComponent()->GetName();
	GStar::Vector3 SpeedB = ColliderB.getPhysic()->GetSpeed();
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Object %i with speed %f,%f,%f", idA, SpeedA[0], SpeedA[1], SpeedA[2]);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "Object %i with speed %f,%f,%f", idB, SpeedB[0], SpeedB[1], SpeedB[2]);
#endif // !
	//Transfer Center to the world space
	return true;
}

bool GStar::OverLapAtoB(const CollisionInfo * A, const CollisionInfo * B, const Vector3 & speed, float end_time, float & closeTime, float & opentime, Vector3& o_axies)
{
	for (int i = 0; i < 3; i++) {
		GStar::Vector3 normalized_axies = (1.0f / (B->Scale).getValue(i)) *(B->Axies)[i];
		float A_center_on_B_axies = (A->Tr).SDot(normalized_axies);
		float B_center_on_B_axies = (B->Tr).SDot(normalized_axies);
		float A_extends_on_B_axies = .5f*(fabs(((A->Axies)[0]).SDot(normalized_axies)) + fabs(((A->Axies)[1]).SDot(normalized_axies)) + fabs(((A->Axies)[2]).SDot(normalized_axies)));
		float B_extends_on_B_axies = .5f*((B->Scale).getValue(i));
		float speed_on_B_axies = speed.SDot(normalized_axies);
		float distance = B_center_on_B_axies- A_center_on_B_axies;
		float offset = A_extends_on_B_axies + B_extends_on_B_axies;
		float open_time;
		float close_time;
		if (Equals(speed_on_B_axies, 0.0f)) {
			if (BigerThan((fabs(distance) - offset), CollisionComponent::margin)) {
				return false;
			}
			else {
				close_time = 0.0f;
				open_time = 100.0f;
			}
		}
		else {
			distance *= signum(speed_on_B_axies);
			float open_distance = distance + offset;
			float close_distance = distance - offset;
			open_time = open_distance / fabs(speed_on_B_axies);
			close_time = close_distance / fabs(speed_on_B_axies);
			if (BigerThan(close_time, end_time) || SmallerThan(open_time, 0.0f)) {
				return false;
			}
		}
		//if the largest close time is smaller that the smallest opentime then there is a time all axies are closed
		if (BigerThan(close_time, closeTime)) {
			closeTime = close_time;
			o_axies = normalized_axies;
		}if (SmallerThan(open_time, opentime)) {
			opentime = open_time;
		}
		//It will not collide
	}
	return true;
}


bool GStar::OverLapAB(const CollisionInfo* A, const CollisionInfo* B, const Vector3& speed, float end_time, float& closeTime, float& opentime, Vector3& o_axies)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			 GStar::Vector3 temp_axies = ((1.0f / (B->Scale).getValue(j)) *(B->Axies)[j]).SCross((1.0f / (A->Scale).getValue(i)) *(A->Axies)[i]);
			 if (temp_axies.isZero()) {
				 continue; 
			 }
			 float A_center_on_axies = (A->Tr).SDot(temp_axies);
			 float B_center_on_axies = (B->Tr).SDot(temp_axies);
			 float A_extends_on_axies = .5f*(fabs(((A->Axies)[0]).SDot(temp_axies)) + fabs(((A->Axies)[1]).SDot(temp_axies)) + fabs(((A->Axies)[2]).SDot(temp_axies)));
			 float B_extends_on_axies = .5f*(fabs(((B->Axies)[0]).SDot(temp_axies)) + fabs(((B->Axies)[1]).SDot(temp_axies)) + fabs(((B->Axies)[2]).SDot(temp_axies)));
			 float speed_on_axies = speed.SDot(temp_axies);
			 float distance = B_center_on_axies-A_center_on_axies;
			 float offset = A_extends_on_axies + B_extends_on_axies;
			 float open_time;
			 float close_time;
			 if (Equals(speed_on_axies, 0.0f)) {
				 if (BigerThan((fabs(distance) - offset),CollisionComponent::margin)) {
					 return false;
				 }
				 else {
					 close_time = 0.0f;
					 open_time = 100.0f;
				 }
			 }
			 else {
				 distance *= signum(speed_on_axies);
				 float open_distance = distance + offset;
				 float close_distance = distance - offset;
				 open_time = open_distance / fabs(speed_on_axies);
				 close_time = close_distance / fabs(speed_on_axies);
				 if (BigerThan(close_time, end_time) ||SmallerThan(open_time, 0.0f)) {
					 return false;
				 }
			 }
			 //if the largest close time is smaller that the smallest opentime then there is a time all axies are closed
			 if (BigerThan( close_time, closeTime)) {
				 closeTime = close_time;
				 o_axies = temp_axies;
			 }if (SmallerThan( open_time, opentime)) {
				 opentime = open_time;
			 }
			 //It will not collide
		}
	}
	return true;
}
