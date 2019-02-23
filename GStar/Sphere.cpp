#include "Sphere.h"
#include"Ray.h"

bool GStar::Sphere::hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const
{
	RayData temp = ray.getValue();
	Vector3 l = m_center - temp.origin;
	float t;
	float m_2;
	float s;
	float q;
	if (l.Dot(l) < m_r*m_r) {
		s = l.Dot(temp.direction);
		m_2 = l.Dot(l) - (s * s);
		q = sqrt(m_r*m_r - m_2);
		t = s + q;
		if (t > t_min && t < t_max) {
			rec.t = t;
			rec.p = temp.direction*t;
			rec.n = rec.p - m_center;
			rec.n.Normalize();
			return true;
		}
		else {
			return false;
		}
	}
	s = l.Dot(temp.direction);
	if (s <= 0) {
		return false;
	}
	m_2 = l.Dot(l) - (s * s);
	if (m_2 > m_r*m_r) {
		return false;
	}
	else {
		q = sqrt(m_r*m_r - m_2);
		t = s - q;
		if (t > t_min && t < t_max) {
			rec.t = t;
			rec.p = temp.direction*t;
			rec.n = rec.p - m_center;
			rec.n.Normalize();
			return true;
		}
		else {
			return false;
		}
	}
}
