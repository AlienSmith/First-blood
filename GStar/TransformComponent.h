#pragma once
#include "Coordinate.h"
#include "Component.h"
#include "View.h"
#include "Object.h"
namespace GStar {
	//Version 2.0 Check OLDCODE Folder for previous version
	//Support default transform based on world, parent and self coordinate
	struct TransformData
	{
		Vector3 r;//rotation x
		Vector3 c;//total offset
		Vector3 cp;//offset based on parent 
		Vector3 cs;//offset based on self
		Vector3 cw;//offset based on world
		Vector3 s;//scale z
	};
	enum Base { WORLD = 0, PARENT = 1, SELF=2 };
	class TransformComponent:public Component {
	public:
		inline void Update(float deltatime) {}
		inline void WorldUpdate(float deltatime) {
			my_Object->Update( deltatime);
			my_children.Resetcurrent();
			while (my_children.HasNext()) {
				//my_children.GetNext()->ParentSetModel(my_model);
				my_children.GetNext()->WorldUpdate(deltatime);
				my_children.Move();
			} 
		}
		inline void AddChildren(TransformComponent* component) {
			my_children.Push(component);
			component->SetParent(this);
		}
		//TODO do initialize in initialize list
		TransformComponent(Object* object) :
			my_model{ Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0),Vector3(0, 0, 0), Vector3(0, 0, 0),Vector3(1, 1, 1) },
			Component(TRANSFORM_WORD),
			my_parent(nullptr),
			my_Object(object) {
			
		}
		inline void SetTransform(const GStar::Vector3& transform,Base base) {
			if (my_parent&& base == Base::PARENT) {
				my_model.cp = transform;
			}
			else if (base == Base::SELF) {
				my_model.cs = transform;
			}
			my_model.cw = transform;

		}
		inline void Translate(const GStar::Vector3& translate, Base base) {
			if (my_parent&& base == Base::PARENT) {
				my_model.cp += translate;
			}
			else if (base == Base::SELF) {
				my_model.cs += translate;
			}
			my_model.cw += translate;
		}
		inline const GStar::Vector3 GetTransform() const { 
			return my_model.c;
		}
		inline void SetScale(const GStar::Vector3& Scale) {
			my_model.s = Scale;
		}
		inline const GStar::Vector3 getScale() const {
			return my_model.s;
		}
		inline void SetRotation(const GStar::Vector3& Scale) {
			my_model.r = Scale;
		}
		inline const GStar::Vector3 GetRoatation() {
			return my_model.r;
		}
		inline GStar::Matrix4 GetBaseMatrix() {
			//Apply parent rotation to it
			GStar::Vector3 temprotation = my_model.r;
			if (my_parent) {
				temprotation += my_parent->GetRoatation();
			}
			array_ff temp = IDENTICAL_MATRIX;
			float sx = sin(temprotation.x()*PI / 180);
			float sy = sin(temprotation.y()*PI / 180);
			float sz = sin(temprotation.z()*PI / 180);
			float cx = cos(temprotation.x()*PI / 180);
			float cy = cos(temprotation.y()*PI / 180);
			float cz = cos(temprotation.z()*PI / 180);
			//Rotate z x y
			temp[0][0] = cz * cy - sz * sx*sy;
			temp[0][1] = -sz * cx;
			temp[0][2] = sy * cz + sz * sx*cy;
			temp[1][0] = sz * cy + cz * sx*sy;
			temp[1][1] = cz * cx;
			temp[1][2] = sz * sy - cz * sx*cy;
			temp[2][0] = -cx * sy;
			temp[2][1] = sx;
			temp[2][2] = cx * cy;
			return GStar::Matrix4(temp);
		}
		inline GStar::Matrix4 getModel() {
			// Pw = M*Pc, Pw = E*Pc + T, Pw = R*S*Pc + T
			GStar::Matrix4 temp = GetBaseMatrix();
			GStar::Vector3 tempPosition = my_model.cw;
			GStar::Vector3 tempScale = my_model.s;
			if (my_parent) {
				tempPosition += my_parent->GetTransform();
				tempPosition += my_parent->GetBaseMatrix() *my_model.cp;
				tempScale *= my_parent->getScale();
			}
			tempPosition += temp *my_model.cs;
			my_model.c = tempPosition;
			//Scaling multiply by a diagnal matrix 
			temp.Getreference(0, 0) *= tempScale.x();// multiply by a diagnal matrix inverse scaling
			temp.Getreference(1, 0) *= tempScale.x();
			temp.Getreference(2, 0) *= tempScale.x();

			temp.Getreference(0, 1) *= tempScale.y();
			temp.Getreference(1, 1) *= tempScale.y();
			temp.Getreference(2, 1) *= tempScale.y();

			temp.Getreference(0, 2) *= tempScale.z();
			temp.Getreference(1, 2) *= tempScale.z();
			temp.Getreference(2, 2) *= tempScale.z();
			//Transform
			temp.Getreference(0, 3) = tempPosition.x();
			temp.Getreference(1, 3) = tempPosition.y();
			temp.Getreference(2, 3) = tempPosition.z();
			return GStar::Matrix4(temp);
		}
		//Take Advantages of the calculation process make calculating inverse faster.
		//TODO setting my_model.c before calling this function could reduce calculation.
		inline GStar::Matrix4 getInverseModel() {
			// Pc = Mi*Pw, Pc = Ei*P - Ei*T, Pc = Si*Rt*Pw - Si*Rt*T: Mi for inverse of M, Rt for transpose of R
			GStar::Matrix4 temp = GetBaseMatrix();
			GStar::Vector3 tempPosition = my_model.cw;
			GStar::Vector3 tempScale = my_model.s;
			if (my_parent) {
				tempPosition += my_parent->GetTransform();
				tempPosition += my_parent->GetBaseMatrix() *my_model.cp;
				tempScale *= my_parent->getScale();
			}
			tempPosition += temp * my_model.cs;
			my_model.c = tempPosition;
			// Calculate the inverse matrix temp = R my_model.s = S my_model.c = T
			temp = temp.T(); // get inverse of rotation matrix
			temp.Getreference(0, 0) /= tempScale.x();
			temp.Getreference(0, 1) /= tempScale.x();
			temp.Getreference(0, 2) /= tempScale.x();

			temp.Getreference(1, 0) /= tempScale.y();
			temp.Getreference(1, 1) /= tempScale.y();
			temp.Getreference(1, 2) /= tempScale.y();

			temp.Getreference(2, 0) /= tempScale.z();
			temp.Getreference(2, 1) /= tempScale.z();
			temp.Getreference(2, 2) /= tempScale.z();


			tempPosition = -1* temp * tempPosition;// Inverse of the position matrix
			temp.Getreference(0, 3) = tempPosition.x();// apply position changes to the matrix
			temp.Getreference(1, 3) = tempPosition.y();
			temp.Getreference(2, 3) = tempPosition.z();	
			return temp;
		}
		inline GStar::Matrix4 getModelI() {
			return GStar::Matrix4(IDENTICAL_MATRIX);
		}
		inline void SetParent(TransformComponent* component) {
			my_parent = component;
		}
	private:
		TransformData my_model;
		SingleLinkedList<GStar::TransformComponent*> my_children;
		GStar::TransformComponent* my_parent;
		Object* my_Object;
	};
}