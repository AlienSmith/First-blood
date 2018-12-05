#pragma once
#include "Coordinate.h"
#include "Component.h"
#include "View.h"
namespace GStar {
	class TransformComponent:public Component {
	public:
		TransformComponent() :Component(TRANSFORM_WORD),model(IDENTICAL_MATRIX) { data = model.GetReference(); }
		inline void SetTransform(const GStar::Vector3& Tranform) {
				*data[0][3] = Tranform.x();
				*data[1][3] = Tranform.y();
				*data[2][3] = Tranform.z();
		}
		inline void Translate(const GStar::Vector3& translate) {
				*data[0][3] += translate.x();
				*data[1][3] += translate.y();
				*data[2][3] += translate.z();
		}
		inline const GStar::Vector3 GetTransform() const { 
				return GStar::Vector3(*data[0][3]
					, *data[1][3]
					, *data[2][3]);
		}
		inline void SetScale(const GStar::Vector3& Scale) {
				*data[0][0] += Scale.x();
				*data[1][1] += Scale.y();
				*data[2][2] += Scale.z();
		}
		inline const GStar::Vector3 getScale() const {
				return GStar::Vector3(*data[0][0],
					*data[1][1],
					*data[2][2]);
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
		array_ff* data;
		GStar::Matrix4 result;
		float rotate_X;
		float rotate_Y;
		float rotate_Z;
	};
}