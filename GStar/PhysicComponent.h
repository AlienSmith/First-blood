#pragma once
#include"TransformComponent.h"
#include"GSTime.h"
#include"Matrix3.h"
//Another Component that would not be attached to the gameobject
namespace GStar {
	//Since it is a diagonal matrix
	inline Matrix4 LocalSpceInverInertia_Cube(float mass, float width, float height, float depth) {
		array_ff temp = IDENTICAL_MATRIX;
		temp[0][0] = (1.0f / mass * (height*height + depth * depth))*12.0f;
		temp[1][1] = (1.0f / mass * (width*width + depth * depth))*12.0f;
		temp[2][2] = (1.0f / mass * (width*width + height * height))*12.0f;
		return temp;
 	}
	class PhysicComponent
	{
	public:
		 PhysicComponent(TransformComponent* const transform);
		 PhysicComponent(TransformComponent* const transform, bool use_gravity, float mass, float roughness);
		 PhysicComponent(TransformComponent* const transform, bool use_gravity, float mass, float roughness,Vector3 angular_momentum);
		 PhysicComponent(const PhysicComponent&) = delete;
		~ PhysicComponent();
		inline void AddForce(const Vector3& Force);
		inline void AddForce(const Vector3 & Force, const Vector3 & Point);
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
		inline Vector3 Applyintertia(const Vector3& vector) const {
			return _inertia_inverse * vector;
		}
		inline Vector3 GetAngularMomentum() const {
			return _angular_momentum;
		}inline void SetAngularMomentum(const Vector3& vector) {
			_angular_momentum = vector;
			return;
		}inline Vector3 GetAngularSpeed()const{
			return _angular_speed;
		}inline void UpdateAngularSpeed(float deltatime) {
			GenerateAngularSpeed();
			if (_angular_speed != Vector3(0.0f, 0.0f, 0.0f)) {
				my_transform->_Rotate(_angular_speed*deltatime);
			}
			_angular_momentum += deltatime * _totaltorque;
		}inline void UpdateLinearSpeed(float deltatime) {
			GStar::Vector3 resistance = GetCurrentResistance();
			_delta = _speed * deltatime;
			_speed += (_totalforce + resistance)*deltatime;
			my_transform->Translate(_delta, GStar::Base::WORLD);
		}
	private:
		inline void ResetValues();
		inline Vector3 GetCurrentResistance() const;
		//rotation components
		Matrix4 _inertia_inverse;
		Vector3 _angular_momentum;
		//derived from momentum should not be given a value
		Vector3 _angular_speed;
		Vector3 _totalforce;
		Vector3 _totaltorque;
		Vector3 _speed;
		Vector3 _delta;//The movement within this frame
		TransformComponent* my_transform;
		bool _usegravity;
		float _mass;//kg
		float _roughness;
		bool _update_in_physicsmanager;
		inline void GenerateAngularSpeed();
	};
	inline PhysicComponent::PhysicComponent(TransformComponent* const transform) :
	_inertia_inverse(),
	_angular_momentum(0.0f, 0.0f, 0.0f),
	_angular_speed(0.0f, 0.0f, 0.0f),
	_totalforce(0.0f,0.0f,0.0f),
	_totaltorque(0.0f,0.0f,0.0f),
	_speed(0.0f, 0.0f, 0.0f),
	_delta(0.0f, 0.0f, 0.0f),
	my_transform(transform),
	_usegravity(false),
	_mass(1.0f),
	_roughness(0.1f),
	_update_in_physicsmanager(true){
		GStar::Vector3 Scale = my_transform->GetScale();
		_inertia_inverse = LocalSpceInverInertia_Cube(_mass, Scale[0],Scale[1],Scale[2]);
	}
	inline PhysicComponent::PhysicComponent(TransformComponent * const transform, bool use_gravity, float mass, float roughness):
	_inertia_inverse(),
	_angular_momentum(0.0f, 0.0f, 0.0f),
	_angular_speed(0.0f, 0.0f, 0.0f),
	_totalforce(0.0f, 0.0f, 0.0f),
	_totaltorque(0.0f, 0.0f, 0.0f),
	_speed(0.0f, 0.0f, 0.0f),
	_delta(0.0f, 0.0f, 0.0f),
	my_transform(transform),
	_usegravity(use_gravity),
	_mass(mass),
	_roughness(roughness),
	_update_in_physicsmanager(true) {
		GStar::Vector3 Scale = my_transform->GetScale();
		_inertia_inverse = LocalSpceInverInertia_Cube(_mass, Scale[0], Scale[1], Scale[2]);
	}
	inline PhysicComponent::PhysicComponent(TransformComponent * const transform, bool use_gravity, float mass, float roughness, Vector3 angular_momentum) :
		_inertia_inverse(),
		_angular_momentum(angular_momentum),
		_angular_speed(0.0f, 0.0f, 0.0f),
		_totalforce(0.0f, 0.0f, 0.0f),
		_totaltorque(0.0f, 0.0f, 0.0f),
		_speed(0.0f, 0.0f, 0.0f),
		_delta(0.0f, 0.0f, 0.0f),
		my_transform(transform),
		_usegravity(use_gravity),
		_mass(mass),
		_roughness(roughness),
		_update_in_physicsmanager(true) {
		GStar::Vector3 Scale = my_transform->GetScale();
		_inertia_inverse = LocalSpceInverInertia_Cube(_mass, Scale[0], Scale[1], Scale[2]);
	}
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
		return (-1.0f* _speed * _speed* _roughness);
		//return GStar::Vector3(.0f, .0f, .0f);
	 }

	 //These used to do angular movment, could cause cache miss,considered move those info here
	 inline void PhysicComponent::GenerateAngularSpeed()
	 {
		 Matrix4 TempInverInertiainWorld = my_transform->GetBaseMatrix()*_inertia_inverse*my_transform->GetBaseMatrix().I();
		 _angular_speed = TempInverInertiainWorld * _angular_momentum;
	 }
	 inline void PhysicComponent::AddForce(const Vector3 & Force,const Vector3 & Point)
	 {
		 AddForce(Force);
		 _totaltorque += GStar::Vector3::Cross((Point - my_transform->GetTransform()), Force);
	 }
	 inline void PhysicComponent::Update(float deltatime)
	 {
		 GenerateAngularSpeed();
		 //Linear
		 GStar::Vector3 resistance = GetCurrentResistance();
		 _delta = _speed * deltatime;
		 _speed += (_totalforce + resistance)*deltatime;
		 my_transform->Translate(_delta, GStar::Base::WORLD);
		 //Angular
		 if (_angular_speed != Vector3(0.0f, 0.0f, 0.0f)) {
			 my_transform->_Rotate(_angular_speed*deltatime);
		 }
		 _angular_momentum += deltatime * _totaltorque;
		 this->ResetValues();
	 }
}