#pragma once
#include "Coordinate.h"
#include "Component.h"
#include "View.h"
#include "Object.h"
namespace GStar {
	//Version 2.0 Check OLDCODE Folder for previous version
	struct TransformData
	{
		Vector3 f;//forward vector
		Vector3 u;//upward vector
		Vector3 r;//right vector
		Vector3 c;//position
		Vector3 s;//scale
		inline void Initialize() {
			f = Vector3(0, 0, 1);
			u = Vector3(0, 1, 0);
			r = Vector3(1, 0, 0);
			c = Vector3(0, 0, 0);
			s = Vector3(1, 1, 1);
		}
	};
	class TransformComponent:public Component {
	public:
		inline void Update() {};
		inline void WorldUpdate() {
			my_Object->Update();
			my_children.Resetcurrent();
			while (my_children.HasNext()) {
				my_children.GetNext()->ParentSetModel(my_model);
				my_children.GetNext()->WorldUpdate();
				my_children.Move();
			} 
		}
		inline void AddChildren(TransformComponent* component) {
			my_children.Push(component);
			component->SetParent(this);
		}
		TransformComponent(Object* object) :
			Component(TRANSFORM_WORD),
			my_parent(nullptr),
			my_Object(object) { }

		inline void SetTransform(const GStar::Vector3& Tranform) {
		}
		inline void Translate(const GStar::Vector3& translate) {
		}
		inline const GStar::Vector3 GetTransform() const { 
		}
		inline void SetScale(const GStar::Vector3& Scale) {
		}
		inline const GStar::Vector3 getScale() const {
		}
		inline void SetRotation(const GStar::Vector3& Scale) {
		}
		inline const GStar::Vector3 GetRoatation() {
		}
		inline TransformData getModel() {
			return my_model;
		}
		inline GStar::Matrix4 getModelI() {
		}
		inline void SetParent(TransformComponent* component) {
			my_parent = component;
		}
		inline void ParentSetModel( const TransformData& data) {
			my_model = data;
		}
	private:
		SingleLinkedList<GStar::TransformComponent*> my_children;
		GStar::TransformComponent* my_parent;
		Object* my_Object;
		TransformData my_model;
	};
}