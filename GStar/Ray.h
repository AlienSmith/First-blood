#pragma once
#include "Vector3.h"
namespace GStar {
	struct RayData {
		Vector3 origin;
		Vector3 direction;
	};
	class Ray {
	public:
		Ray() {}
		Ray(const Vector3& o, const Vector3& d) :m_data({ o,d }) {
			m_data.direction.Normalize();
		}
		RayData getValue() const{
			return m_data;
		}
		RayData* getReference(){
			return &m_data;
		}
		Vector3 point_at_parameter(float t) const{
			return m_data.origin + m_data.direction*t;
		}
	private:
		RayData m_data;
	};
}