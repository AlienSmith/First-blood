#pragma once
#include "Coordinate.h"
#include "Component.h"
#include "View.h"
namespace GStar {
	class TransformComponent:public Component {
	public:
		TransformComponent() :Component(TRANSFORM_WORD),model(IDENTICAL_MATRIX) { }
		inline void SetTransform(const GStar::Vector3& Tranform) {
				model.Getreference(0,3) = Tranform.x();
				model.Getreference(1, 3) = Tranform.y();
				model.Getreference(2, 3) = Tranform.z();
				result = model;
		}
		inline void Translate(const GStar::Vector3& translate) {
			model.Getreference(0, 3) += translate.x();
			model.Getreference(1, 3) += translate.y();
			model.Getreference(2, 3) += translate.z();
				result = model;
		}
		inline const GStar::Vector3 GetTransform() const { 
				return GStar::Vector3(model.GetData(0,3)
					, model.GetData(1, 3)
					, model.GetData(2, 3));
		}
		inline void SetScale(const GStar::Vector3& Scale) {
			model.Getreference(0, 0) = Scale.x();
			model.Getreference(1, 1)= Scale.y();
			model.Getreference(2, 2) += Scale.z();
				result = model;
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
			result = GStar::Rotate(model, rotate_X, rotate_Y, rotate_Z);
		}
		inline const GStar::Vector3 GetRoatation() {
			return GStar::Vector3(rotate_X, rotate_Y, rotate_Z);
		}
		inline GStar::Matrix4 getModel() {
			return result;
		}
	private:
		GStar::Matrix4 model;
		GStar::Matrix4 result;
		float rotate_X;
		float rotate_Y;
		float rotate_Z;
	};
}