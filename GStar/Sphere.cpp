#include "Sphere.h"
#include"Ray.h"

GStar::Sphere::Sphere(const Sphere & other):
	m_center(other.m_center),
	m_r(other.m_r),
	m_material(other.m_material){}

GStar::Sphere & GStar::Sphere::operator=(const Sphere & other)
{
	m_center = other.m_center;
	m_r = other.m_r;
	m_material = other.m_material;
	return *this;
}

bool GStar::Sphere::hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const
{
	RayData r = ray.getValue();
	Vector3 oc = r.origin - m_center;
	float a = r.direction.Dot(r.direction);
	float b = oc.Dot(r.direction);
	float c = oc.Dot(oc) - m_r * m_r;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (float)((-b - sqrt(discriminant)) / a);
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.n = (rec.p - m_center) / m_r;
			rec.mat_ptr = m_material;
			return true;
		}
		temp = (float)((-b + sqrt(discriminant)) / a);
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.n = (rec.p - m_center) / m_r;
			rec.mat_ptr = m_material;
			return true;
		}
	}
	return false;
}
