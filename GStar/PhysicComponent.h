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
		inline void AddForce(const Vector3& Force);
		inline void SetForce(const Vector3& Force);
		inline const TransformComponent* const GetTransformComponent() const {
			return my_transform;
		}
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
		inline void Update(float deltatime);
		inline GStar::Vector3 GetSpeed() const {
			return _speed;
		}
		inline void UseCollision() {
			_update_in_physicsmanager = false;
		}
		inline bool UpdateInPhysics() {
			return _update_in_physicsmanager;
		}
		inline void SetSpeed(const GStar::Vector3 & speed) {
			_speed = speed;
		}
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
		bool _update_in_physicsmanager;
	};
	inline PhysicComponent:: PhysicComponent(TransformComponent* const transform):
	_totalforce(0.0f,0.0f,0.0f),
	_speed(0.0f, 0.0f, 0.0f),
	_delta(0.0f, 0.0f, 0.0f),
	my_transform(transform),
	_usegravity(false),
	_mass(1.0f),
	_roughness(0.1f),
	_update_in_physicsmanager(true){}
	inline PhysicComponent::PhysicComponent(TransformComponent * const transform, bool use_gravity, float mass, float roughness):
	_totalforce(0.0f, 0.0f, 0.0f),
	_speed(0.0f, 0.0f, 0.0f),
	_delta(0.0f, 0.0f, 0.0f),
	my_transform(transform),
	_usegravity(use_gravity),
	_mass(mass),
	_roughness(roughness),
	_update_in_physicsmanager(true) {}
	inline PhysicComponent::~ PhysicComponent(){}
	 //Mid value method
	 //Update The delta
	inline void PhysicComponent::AddForce(const Vector3 & Force)
	{
		_totalforce += Force;
	}
	inline void PhysicComponent::SetForce(const Vector3 & Force)
	{
		_totalforce = Force;
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
		//return (-1.0f* _speed * _speed* _roughness);
		return GStar::Vector3(.0f, .0f, .0f);
	 }
	 inline void PhysicComponent::Update(float deltatime)
	 {
		 GStar::Vector3 resistance = GetCurrentResistance();
		 if (_totalforce == ((-1.0f) *resistance)) {
			 _delta = _speed * deltatime;
		 }
		 else {
			 GStar::Vector3 lastspeed = _speed;
			 _speed += (_totalforce + resistance)*deltatime;
			 _delta = .5f*(_speed + lastspeed)*deltatime;
		 }
		 my_transform->Translate(_delta,GStar::Base::WORLD);
		 this->ResetValues();
	 }
}