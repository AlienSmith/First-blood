#pragma once
#include "Coordinate.h"
#include "Component.h"
#include "View.h"
#include "Object.h"
namespace GStar {
	class TransformComponent:public Component {
	public:
		inline void Update() {};
		inline void WorldUpdate() {
			my_Object->Update();
			my_children.Resetcurrent();
			while (my_children.HasNext()) {
				my_children.GetNext()->ParentSetModel(getModel());
				my_children.GetNext()->WorldUpdate();
				my_children.Move();
			} 
		}
		inline void AddChildren(TransformComponent* component) {
			my_children.Push(component);
		}
		TransformComponent(Object* object) :Component(TRANSFORM_WORD),model(IDENTICAL_MATRIX),my_Object(object),parent(IDENTICAL_MATRIX) { }
		inline void SetTransform(const GStar::Vector3& Tranform) {
				model.Getreference(0,3) = Tranform.x();
				model.Getreference(1, 3) = Tranform.y();
				model.Getreference(2, 3) = Tranform.z();
		}
		inline void Translate(const GStar::Vector3& translate) {
			model.Getreference(0, 3) += translate.x();
			model.Getreference(1, 3) += translate.y();
			model.Getreference(2, 3) += translate.z();
		}
		inline const GStar::Vector3 GetTransform() const { 
				return GStar::Vector3(model.GetData(0,3)
					, model.GetData(1, 3)
					, model.GetData(2, 3));
		}
		inline void SetScale(const GStar::Vector3& Scale) {
			model.Getreference(0, 0) = Scale.x();
			model.Getreference(1, 1) = Scale.y();
			model.Getreference(2, 2) += Scale.z();
		}
		inline const GStar::Vector3 getScale() const {
				return GStar::Vector3(model.GetData(0, 0),
					model.GetData(1, 1),
					model.GetData(2, 2));
		}
		inline void SetRotation(const GStar::Vector3& Scale) {
			rotate_X = Scale.x();
			rotate_Y = Scale.y();
			rotate_Z = Scale.z();
		}
		inline const GStar::Vector3 GetRoatation() {
			return GStar::Vector3(rotate_X, rotate_Y, rotate_Z);
		}
		inline GStar::Matrix4 getModel() {
			//TODO figure out why. this should be model * parent * vector Probably because OpenGl use Roll matrix
			return GStar::Rotate(parent.Dot(model), rotate_X, rotate_Y, rotate_Z);
		}
		inline GStar::Matrix4 getModelI() {
			return GStar::Rotate(parent.Dot(model), rotate_X, rotate_Y, rotate_Z).I();
		}
		inline void ParentSetModel( const GStar::Matrix4& input) {
			parent = input;
		}
	private:
		SingleLinkedList<GStar::TransformComponent*> my_children;
		Object* my_Object;
		GStar::Matrix4 model;
		GStar::Matrix4 parent;
		float rotate_X;
		float rotate_Y;
		float rotate_Z;
	};
}