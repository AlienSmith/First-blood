#pragma once
#include"Ray.h"
#include <math.h>
namespace GStar {
	class Sphere {
	public:
		Sphere(const Vector3& center, float r): m_center(center),m_r(r){}
		inline float Collision(const Ray& ray, bool& collided) const{
			RayData temp = ray.getValue();
			Vector3 l = m_center - temp.origin;
			float m_2;
			float s;
			float q;
			if (l.Dot(l) < m_r*m_r) {
				collided = true;
				s = l.Dot(temp.direction);
				m_2 = l.Dot(l) - (s * s);
				q = sqrt(m_r*m_r - m_2);
				return s+q;
			}
			s = l.Dot(temp.direction);
			if (s <= 0) {
				collided = false;
				return 0.0f;
			}
			m_2 = l.Dot(l) - (s * s);
			if (m_2 > m_r*m_r) {
				collided = false;
				return 0.0f;
			}
			else {
				collided = true;
				q = sqrt(m_r*m_r - m_2);
				return s-q;
			}

		}
	private:
		Vector3 m_center;
		float m_r;
	};
}