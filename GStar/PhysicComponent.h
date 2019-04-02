#pragma once
#include"TransformComponent.h"
#include"GSTime.h"
//Another Component that would not be attached to the gameobject
namespace GStar {
	class PhysicComponent
	{
	public:
		 PhysicComponent(TransformComponent* const transform);
		 PhysicComponent(TransformComponent* const transform, bool use_gravity, float mass, float roughness);
		 PhysicComponent(const PhysicComponent&) = delete;
		~ PhysicComponent();
		inline void AddFource(const Vector3& Force);
		inline TransformComponent* GetTransformComponent() {
			return my_transform;
		}
		inline float getMass() const {
			return _mass;
		}
		inline bool useGravity() const{
			return _usegravity;
		}inline float getroughness() {
			return _roughness;
		}
		inline void Update();
	private:
		inline void ResetValues();
		inline Vector3 GetCurrentResistance() const;
		Vector3 _totalforce;
		Vector3 _speed;
		Vector3 _delta;//The movement within this frame
		TransformComponent* my_transform;
		bool _usegravity;
		float _mass;//kg
		float _roughness;
	};
	inline PhysicComponent:: PhysicComponent(TransformComponent* const transform):
	_totalforce(0.0f,0.0f,0.0f),
	_speed(0.0f, 0.0f, 0.0f),
	_delta(0.0f, 0.0f, 0.0f),
	my_transform(transform),
	_usegravity(false),
	_mass(1.0f),
	_roughness(0.1f){}
	inline PhysicComponent::PhysicComponent(TransformComponent * const transform, bool use_gravity, float mass, float roughness):
	_totalforce(0.0f, 0.0f, 0.0f),
	_speed(0.0f, 0.0f, 0.0f),
	_delta(0.0f, 0.0f, 0.0f),
	my_transform(transform),
	_usegravity(use_gravity),
	_mass(mass),
	_roughness(roughness) {}
	inline PhysicComponent::~ PhysicComponent(){}
	 //Mid value method
	 //Update The delta
	 inline void PhysicComponent::AddFource(const Vector3 & Force)
	 {
		 _totalforce += Force;
	 }
	 inline void PhysicComponent::ResetValues()
	 {
		 for (int i = 0; i < 3; i++) {
			 _totalforce.getReference(i) = 0.0f;
			 _delta.getReference(i) = 0.0f;
		 }

	 }
	 //return the value for the current speed
	 inline Vector3 PhysicComponent::GetCurrentResistance() const
	 {
		// return (-1.0f * _speed * _speed* _roughness);
		 return GStar::Vector3(.0f, .0f, .0f);
	 }
	 inline void PhysicComponent::Update()
	 {
		 GStar::Vector3 resistance = GetCurrentResistance();
		 if (_totalforce == ((-1.0f) *resistance)) {
			 _delta = _speed * GSTime::Instance().GetdeltaTime();
		 }
		 else {
			 GStar::Vector3 lastspeed = _speed;
			 _speed += (_totalforce + resistance)*GSTime::Instance().GetdeltaTime();
			 _delta = .5f*(_speed + lastspeed)*GSTime::Instance().GetdeltaTime();
		 }
		 my_transform->Translate(_delta/100.0f,GStar::Base::WORLD);
		 this->ResetValues();
	 }
}